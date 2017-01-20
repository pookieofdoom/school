/*
 * Program 1: Trace
 * Luke Gnos
 * 1/12/16
 */

//TODO
//fix checksum for IP
//headers for UDP and TCP
//sniff 2 things on wireshark and test

#include <stdio.h>
#include <stdlib.h>
#include <pcap.h>
#include "checksum.h"
#include "trace.h"
#include <netinet/in.h>
#include <string.h>


/* Function Prototypes */
void getPackets(pcap_t *handle);
void getHeaders(struct pcap_pkthdr *header, const u_char *packet);
void printTCP(tcpHeader *tcp, ipHeader *ip);
int getTCPChecksum(tcpHeader *tcp, ipHeader *ip);
void printUDP(udpHeader *udp);
void printARP(arpHeader *arp);
void printIP(ipHeader *ip);
int getIPChecksum(ipHeader *ip);
void printEthernet(ethHeader *eh);
char *getEthType(ethHeader *eh);
FILE * manageInputs(int argc, char *argv[]);
pcap_t * getHandle(FILE *inputfile);
void printICMP(icmpHeader *icmp);


int main (int argc, char *argv[]) {
  FILE *inputfile;
  pcap_t *handle;

  inputfile = manageInputs(argc, argv);
  if (inputfile == NULL) {
    perror("input fopen");
    exit(0);
  }

  handle = getHandle(inputfile);

  getPackets(handle);
  
  pcap_close(handle);

  return 0;
}

/*
 * Function that controls looping through the packets
 */
void getPackets(pcap_t *handle) {
  const u_char *packet;
  struct pcap_pkthdr *header;
  int status, count = 1, done = 0;
  ethHeader *eh;

  //printf("%d", sizeof(udpHeader));
  printf("\n"); // Courtesy new line

  while (!done) {
    status = pcap_next_ex(handle, &header, &packet);
    
    switch (status) {
    case 1: //no problems
      printf("Packet number: %d  Packet Len: %d\n\n", count, header->len);

      getHeaders(header, packet);
      break;
    case -1: //Error occured while reading a packet
      fprintf(stderr, "Error occured while reading a packet\n");
      pcap_perror(handle, "Reading packet Error");
      exit(0);
      break;
    case -2: //No more packets
      done = 1;
      break;
    }

    //break;
    count++;
  }

}

/*
 * Detect what headers are in the packet, then call the respective
 *  printing function
 */
void getHeaders(struct pcap_pkthdr *header, const u_char *packet) {
  //struct for each type
  //call function to print each header out with the struct as arg
  ethHeader *eh;
  ipHeader *ip;
  icmpHeader *icmp;
  arpHeader *arp;
  udpHeader *udp;
  tcpHeader *tcp;
  u_int ipOffset = 0;
  
  eh = (ethHeader *)packet;
  printEthernet(eh);

  if (eh->type == ETH_IP_TYPE) {
    //get IP header
    ip = (ipHeader *)(packet + ETH_HEAD_SIZE);
    printIP(ip);

    ipOffset = 4*(ip->type & 0x0F);

    if (ip->protocol == IP_ICMP_PROTO) {
      icmp = (icmpHeader *)(packet + ETH_HEAD_SIZE + ipOffset);
      printICMP(icmp);
      
    } else if (ip->protocol == IP_UDP_PROTO) {
      udp = (udpHeader *)(packet + ETH_HEAD_SIZE + ipOffset);
      printUDP(udp);
      
    } else if (ip->protocol == IP_TCP_PROTO) {
      tcp = (tcpHeader *)(packet + ETH_HEAD_SIZE + ipOffset);
      printTCP(tcp, ip);
    } //else { //Otherwise, Unknown Type
      //printf(">>> %d <<< \n", ip->protocol);
      //printf("Unknown PDU\n");
    //}
    
  } else if (eh->type == ETH_ARP_TYPE) {
    //Get ARP header
    arp = (arpHeader *)(packet + ETH_HEAD_SIZE);
    printARP(arp);

  } else { //Otherwise unkown type
    printf("Unknown PDU\n");
  }
}

/*
 * Given a TCP header, prints out its info
 */
void printTCP(tcpHeader *tcp, ipHeader *ip) {
    
  printf("\tTCP Header\n");
  printf("\t\tSource Port: %u\n", ntohs(tcp->srcport));
  printf("\t\tDest Port: %u\n", ntohs(tcp->destport));
  printf("\t\tSequence Number: %u\n", ntohl(tcp->seq));
  printf("\t\tACK Number: %u\n", ntohl(tcp->acknum));
  printf("\t\tData Offset (bytes): %u\n", 4*(tcp->offset >> 4));

  printf("\t\tSYN Flag: ");
  if (tcp->flags & TCP_SYN_MASK)
    printf("Yes\n");
  else
    printf("No\n");

  printf("\t\tRST Flag: ");
  if (tcp->flags & TCP_RST_MASK)
    printf("Yes\n");
  else
    printf("No\n");

  printf("\t\tFIN Flag: ");
  if (tcp->flags & TCP_FIN_MASK)
    printf("Yes\n");
  else
    printf("No\n");

  printf("\t\tACK Flag: ");
  if (tcp->flags & TCP_ACK_MASK)
    printf("Yes\n");
  else
    printf("No\n");

  printf("\t\tWindow Size: %d\n", ntohs(tcp->winsize));

  if (getTCPChecksum(tcp, ip) == 0)
    printf("\t\tChecksum: Correct ");
  else
    printf("\t\tChecksum: Incorrect ");

  printf("(0x%02x%02x)\n", tcp->cs_one, tcp->cs_two);

  printf("\n");
}

int getTCPChecksum(tcpHeader *tcp, ipHeader *ip) {
  tcpPseudo pseudo;
  u_short checkret;
  pseudo.srcip[0] = ip->srcip[0];
  pseudo.srcip[1] = ip->srcip[1];
  pseudo.srcip[2] = ip->srcip[2];
  pseudo.srcip[3] = ip->srcip[3];
  
  pseudo.destip[0] = ip->destip[0];
  pseudo.destip[1] = ip->destip[1];
  pseudo.destip[2] = ip->destip[2];
  pseudo.destip[3] = ip->destip[3];
  
  pseudo.zeroes = 0;
  pseudo.proto = IP_TCP_PROTO;
  pseudo.tcplen = htons(ntohs(ip->length)-(4*(ip->type & 0x0F)));


  int length = sizeof(tcpPseudo) + pseudo.tcplen;

  u_char check[length];
  

  memcpy(check, &pseudo, sizeof(tcpPseudo));
  memcpy(check + sizeof(tcpPseudo), tcp, ntohs(pseudo.tcplen));
  checkret = in_cksum((u_short *)check, ntohs(pseudo.tcplen)+ sizeof(tcpPseudo) );

  return checkret;
  
}

/*
 * Given an UDP header, prints out its info
 */
void printUDP(udpHeader *udp) {
  printf("\tUDP Header\n");

  u_short src = (udp->srcport >> 8) | (udp->srcport << 8);
  u_short dest = (udp->destport >> 8) | (udp->destport << 8);
  
  if (src == UDP_DNS_PORT)
    printf("\t\tSource Port: DNS\n");
  else
    printf("\t\tSource Port: %u\n", src);

  if (dest == UDP_DNS_PORT)
    printf("\t\tDest Port: DNS\n");
  else
    printf("\t\tDest Port: %u\n", dest);
  
  printf("\n");
}

/*
 * Given an ARP header, prints out its info
 */
void printARP(arpHeader *arp) {

  printf("\tARP header\n");
  if (arp->opcode == ARP_REQUEST)
    printf("\t\tOpcode: Request\n");
  else if (arp->opcode == ARP_REPLY)
    printf("\t\tOpcode: Reply\n");

  printf("\t\tSender MAC: %x:%x:%x:%x:%x:%x\n", arp->sendmac[0],
	 arp->sendmac[1], arp->sendmac[2], arp->sendmac[3], arp->sendmac[4],
	 arp->sendmac[5]);
  printf("\t\tSender IP: %d.%d.%d.%d\n", arp->sendip[0], arp->sendip[1],
	 arp->sendip[2], arp->sendip[3]);
  printf("\t\tTarget MAC: %x:%x:%x:%x:%x:%x\n", arp->targmac[0],
	 arp->targmac[1], arp->targmac[2], arp->targmac[3], arp->targmac[4],
	 arp->targmac[5]);
  printf("\t\tTarget IP: %d.%d.%d.%d\n", arp->targip[0], arp->targip[1],
	 arp->targip[2], arp->targip[3]);
  printf("\n");
  
}

/*
 * Given an ICMP header, prints out its info
 */
void printICMP(icmpHeader *icmp) {
  printf("\tICMP Header\n");

  //printf(">>> %d\n", icmp->type);

  if (icmp->type == ICMP_REQUEST) {
    printf("\t\tType: Request\n");
  } else if (icmp->type == ICMP_REPLY) {
    printf("\t\tType: Reply\n");
  } else {
    printf("\t\tType: %d\n", icmp->type);
  }
  
  printf("\n");
}

/*
 * Given an IP header, prints out its info
 */
void printIP(ipHeader *ip) {

  printf("\tIP Header\n");
  printf("\t\tIP Version: %d\n", ip->type >> IP_VERS_SHIFT);
  printf("\t\tHeader Len (bytes): %u\n", 4 * (ip->type & 0x0F));
  printf("\t\tTOS subfields:\n");
  printf("\t\t   Diffserv bits: %d\n", ip->tos >> IP_DFSRV_SHIFT);
  printf("\t\t   ECN bits: %d\n", ip->tos & IP_ECN_MASK);
  printf("\t\tTTL: %d\n", ip->ttl);
  
  if (ip->protocol == IP_ICMP_PROTO)
    printf("\t\tProtocol: %s\n", "ICMP");
  else if (ip->protocol == IP_TCP_PROTO) 
    printf("\t\tProtocol: %s\n", "TCP");
  else if (ip->protocol == IP_UDP_PROTO)
    printf("\t\tProtocol: UDP\n");
  else
    printf("\t\tProtocol: Unknown\n");

  if (getIPChecksum(ip))
    printf("\t\tChecksum: Correct ");
  else
    printf("\t\tChecksum: Incorrect ");
  
  printf("(0x%02x%02x)\n", ip->cs_one, ip->cs_two);
  printf("\t\tSender IP: %d.%d.%d.%d\n", ip->srcip[0], ip->srcip[1],
	 ip->srcip[2], ip->srcip[3]);
  printf("\t\tDest IP: %d.%d.%d.%d\n", ip->destip[0], ip->destip[1],
	 ip->destip[2], ip->destip[3]);
  printf("\n");
}

/*
 * Function that determines if an error occured via the IP checksum
 * returns >=1 for correct, 0 for error
 */
int getIPChecksum(ipHeader *ip) {
  u_short length = 4*(ip->type & 0x0F);
  unsigned short res;

  res = in_cksum((u_short *)ip, length);

  return !res;
}

/*
 * Given an ethernet header, print out its info
 */
void printEthernet(ethHeader *eh) {
  int i;

  printf("\tEthernet Header\n");
  printf("\t\tDest MAC: ");
 
  for (i = 0; i < ETH_ADDR_LEN; i++) {
    printf("%x", eh->desthost[i]);
    if (i != ETH_ADDR_LEN - 1)
      printf(":");
  }
  
  printf("\n");
  printf("\t\tSource MAC: ");

  for (i = 0; i < ETH_ADDR_LEN; i++) {
    printf("%x", eh->srchost[i]);
    if (i != ETH_ADDR_LEN - 1)
      printf(":");
  }

  printf("\n");
  printf("\t\tType: %s\n", getEthType(eh));
  printf("\n");
}

/*
 * Function that determines the ethernet type given its header
 */
char *getEthType(ethHeader *eh) {

  if (eh->type == ETH_IP_TYPE)
    return "IP";
  else if (eh->type == ETH_ARP_TYPE) 
    return "ARP";
}

/*
 * Function that checks for the correct inputs and returns the
 *  result of the fopen call on the passed in filename
 */
FILE * manageInputs(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Incorrect arguments, please input in the form: "
	    "trace [filename]\n");
    exit(0);
  }

  return fopen(argv[1], "r");
}

/*
 * Function that sets the device for pcap, exits on error
 */
pcap_t * getHandle(FILE *inputfile) {
  char error[PCAP_ERRBUF_SIZE];
  pcap_t *res;
 
  res = pcap_fopen_offline(inputfile, error);
  if (res == NULL) {
    fprintf(stderr, "Failed to open offline handle: %s\n", error);
    exit(0);
  }

  return res;
}
