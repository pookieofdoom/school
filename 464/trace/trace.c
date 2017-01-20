#include <stdio.h>
#include <stdlib.h>
#include <pcap.h>
#include <string.h>
#include <netinet/in.h> //htonl, ntohs, etc
#include "checksum.h"

#define ETHER_TYPE_ARP 0x806
#define ETHER_TYPE_IP 0x800
#define ARP_REQUEST 1
#define ARP_REPLY 2
#define ICMP_REPLY 0
#define ICMP_REQUEST 8
#define PROTOCOL_ICMP 1
#define PROTOCOL_TCP 6
#define PROTOCOL_UDP 17
#define FIN_FLAG_SHIFT 0
#define SYN_FLAG_SHIFT 1
#define RST_FLAG_SHIFT 2
#define ACK_FLAG_SHIFT 4
#define PORT_NUMBER_FTP 21
#define PORT_NUMBER_TELNET 23
#define PORT_NUMBER_SMTP 25
#define PORT_NUMBER_DNS 53
#define PORT_NUMBER_HTTP 80
#define PORT_NUMBER_POP3 110
#define ET_LEN 14
#define IP_SIZE 4
#define MAC_SIZE 6

typedef struct __attribute__((packed)) {
   u_char destMac[6];
   u_char sourceMac[6];
   u_short etherType; //IP, ARP, RARP, etc
} EthernetStruct;

typedef struct __attribute__((packed)) {
   short int opcode;
   u_char senderMac[MAC_SIZE];
   u_char senderIp[IP_SIZE];
   u_char targetMac[MAC_SIZE];
   u_char targetIp[IP_SIZE];
}ArpStruct;

typedef struct __attribute__((packed)) {
   u_char verHdrLen; //version (4bits) and header length (4bits)
   u_char tos; //type of service (1 octet)
   u_short totalLength;
   u_char unused[4]; //4 bytes that aren't used so is skipped
   u_char ttl; //time to live
   u_char protocol;
   u_short checksum;
   u_char senderIp[IP_SIZE];
   u_char destIp[IP_SIZE];
}IpStruct;

typedef struct __attribute__((packed)) {
   u_short sourcePort;
   u_short destPort;
   u_int sequenceNumber;
   u_int ackNumber;
   u_char dataOffset;
   u_char flag;
   u_short windowSize;
   u_short checksum;
}TcpStruct;

typedef struct __attribute__((packed)) {
   u_char sourceAddress[IP_SIZE];
   u_char destAddress[IP_SIZE];
   u_char reserved;
   u_char protocol;
   u_short tcpLength;
}PseudoStruct;

typedef struct __attribute__((packed)) {
   u_char type;
}IcmpStruct;

typedef struct __attribute__((packed)) {
   u_short sourcePort;
   u_short destPort;
}UdpStruct;

void printMacAddress(u_char address[MAC_SIZE], int length) {
   int i;
   for (i = 0; i < length; i++) {
      if (i != length - 1)
         printf("%x:", address[i]);
      else
         printf("%x\n", address[i]);
   }
}

void printIpAddress(u_char address[IP_SIZE], int length) {
   int i;
   for (i = 0; i < length; i++) {
      if (i != length -1)
         printf("%d.", address[i]);
      else
         printf("%d\n", address[i]);
   }
}
void initPseudoHdr(PseudoStruct *psHdr, IpStruct *ipHdr) {
   memcpy(psHdr->sourceAddress, ipHdr->senderIp, IP_SIZE);
   memcpy(psHdr->destAddress, ipHdr->destIp, IP_SIZE);
   psHdr->reserved = 0;
   psHdr->protocol = ipHdr->protocol;
   psHdr->tcpLength = htons(ntohs(ipHdr->totalLength) - 
    (ipHdr->verHdrLen & 0x0f) * 4);
}

void flagCheck(u_char flag, int shift) {
   if ((flag & (1 << shift)) != 0)
      printf("Yes\n");
   else
      printf("No\n"); 
}

void checkPortNumber(u_short portNumber) {
   u_short hostPort = ntohs(portNumber);
   
   if (hostPort == PORT_NUMBER_FTP)
      printf("FTP\n");
   else if (hostPort == PORT_NUMBER_TELNET)
      printf("Telnet\n");
   else if (hostPort == PORT_NUMBER_SMTP)
      printf("SMTP\n");
   else if (hostPort == PORT_NUMBER_DNS)
      printf("DNS\n");
   else if (hostPort == PORT_NUMBER_HTTP)
      printf("HTTP\n");
   else if (hostPort == PORT_NUMBER_POP3)
      printf("POP3\n");
   else
      printf("%hu\n", hostPort);
}

int checkProtocol(u_char protocol) {
   int flag = 0;
   if (protocol == PROTOCOL_UDP)
      printf("UDP\n");
   else if (protocol == PROTOCOL_TCP)
      printf("TCP\n");
   else if (protocol == PROTOCOL_ICMP)
      printf("ICMP\n");
   else {
      printf("Unknown\n");
      flag = 1;
   }
   return flag;
}

void ethernetParse(EthernetStruct *ethernet) {
   printf("\tEthernet Header\n");
   
   printf("\t\tDest MAC: ");
   printMacAddress(ethernet->destMac, MAC_SIZE);
   
   printf("\t\tSource MAC: ");
   printMacAddress(ethernet->sourceMac, MAC_SIZE);
   
   if (ntohs(ethernet->etherType) == ETHER_TYPE_ARP)
      printf("\t\tType: ARP\n\n");
   else if(ntohs(ethernet->etherType) == ETHER_TYPE_IP)
      printf("\t\tType: IP\n\n");
}

void arpParse(ArpStruct *arpHdr) {
   printf("\tARP header\n");
   
   if (ntohs(arpHdr->opcode) == ARP_REQUEST) {
      printf("\t\tOpcode: Request\n");
   }
   else if (ntohs(arpHdr->opcode) == ARP_REPLY) {
      printf("\t\tOpcode: Reply\n");
   }
   
   printf("\t\tSender MAC: ");
   printMacAddress(arpHdr->senderMac, MAC_SIZE);
   
   printf("\t\tSender IP: ");
   printIpAddress(arpHdr->senderIp, IP_SIZE);
   
   printf("\t\tTarget MAC: ");
   printMacAddress(arpHdr->targetMac, MAC_SIZE);
   
   printf("\t\tTarget IP: ");
   printIpAddress(arpHdr->targetIp, IP_SIZE);
   printf("\n"); //need extra line to match output
}

void ipParse(IpStruct *ipHdr) {
   int unknownFlagPrint = 0;
    //mask the lower 4 bits and then multiply by 4
   int len = (ipHdr->verHdrLen & 0x0f) * 4;
   u_short check = in_cksum((u_short*)(ipHdr),len);
  
   printf("\tIP Header\n");
   printf("\t\tIP Version: %d\n", ipHdr->verHdrLen >> 4);  
   printf("\t\tHeader Len (bytes): %d\n", len); 
   
   printf("\t\tTOS subfields:\n");
   printf("\t\t   Diffserv bits: %d\n", ipHdr->tos >> 2);
   printf("\t\t   ECN bits: %d\n", ipHdr->tos & 0x03);
   printf("\t\tTTL: %d\n",ipHdr->ttl);
   
   printf("\t\tProtocol: ");
   unknownFlagPrint = checkProtocol(ipHdr->protocol);
   
   printf("\t\tChecksum: ");
   if (check == 0)
      printf("Correct ");
   else
      printf("Incorrect ");     
   printf("(0x%04x)\n", ntohs(ipHdr->checksum)); 

   printf("\t\tSender IP: ");
   printIpAddress(ipHdr->senderIp, IP_SIZE);
   printf("\t\tDest IP: ");
   printIpAddress(ipHdr->destIp, IP_SIZE);
   if (unknownFlagPrint != 1)
      printf("\n"); //need extra line to match output
}

void tcpParse(TcpStruct *tcpHdr, PseudoStruct *psHdr) {
   int size = sizeof(PseudoStruct) + psHdr->tcpLength;
   u_char combinedBuffer[size];
   u_short check;
   
   printf("\tTCP Header\n");
   printf("\t\tSource Port:  ");
   checkPortNumber(tcpHdr->sourcePort);
   printf("\t\tDest Port:  ");
   checkPortNumber(tcpHdr->destPort);
   
   printf("\t\tSequence Number: %u\n", htonl(tcpHdr->sequenceNumber));
   printf("\t\tACK Number: %u\n", htonl(tcpHdr->ackNumber));
   printf("\t\tData Offset (bytes): %d\n", (tcpHdr->dataOffset >> 4) * 4);
   
   printf("\t\tSYN Flag: ");
   flagCheck(tcpHdr->flag, SYN_FLAG_SHIFT);
   printf("\t\tRST Flag: ");
   flagCheck(tcpHdr->flag, RST_FLAG_SHIFT);
   printf("\t\tFIN Flag: ");
   flagCheck(tcpHdr->flag, FIN_FLAG_SHIFT);
   printf("\t\tACK Flag: ");
   flagCheck(tcpHdr->flag, ACK_FLAG_SHIFT);
   
   printf("\t\tWindow Size: %hu\n", ntohs(tcpHdr->windowSize));
   printf("\t\tChecksum: ");
   memcpy(combinedBuffer, psHdr, sizeof(PseudoStruct));
   memcpy(combinedBuffer + sizeof(PseudoStruct), tcpHdr, ntohs(psHdr->tcpLength));
   check = in_cksum((u_short*)combinedBuffer, ntohs(psHdr->tcpLength) + sizeof(PseudoStruct));
   if (check == 0)
      printf("Correct ");
   else
      printf("Incorrect ");
   printf("(0x%04x)\n", ntohs(tcpHdr->checksum));
   
}

void icmpParse(IcmpStruct *icmpHdr) {
   printf("\tICMP Header\n");
   printf("\t\tType: ");
   if (icmpHdr->type == ICMP_REPLY)
      printf("Reply\n");
   else if (icmpHdr->type == ICMP_REQUEST)
      printf("Request\n");
   else
      printf("%d\n", icmpHdr->type);  
}

void udpParse(UdpStruct *udpHdr) {
   printf("\tUDP Header\n");
   printf("\t\tSource Port:  ");
   checkPortNumber(udpHdr->sourcePort);
   printf("\t\tDest Port:  ");
   checkPortNumber(udpHdr->destPort);
}

int main(int argc, char **argv) {
   pcap_t *handler;
   char errbuff[PCAP_ERRBUF_SIZE];
   struct pcap_pkthdr *header;
   const u_char *packet;
   //had to malloc b/c random seg faults
   EthernetStruct *ethernet = malloc(sizeof(EthernetStruct));
   ArpStruct *arpHdr = malloc(sizeof(ArpStruct));
   IpStruct *ipHdr = malloc(sizeof(IpStruct));
   TcpStruct *tcpHdr = malloc(sizeof(TcpStruct));
   PseudoStruct *psHdr = malloc(sizeof(PseudoStruct));
   IcmpStruct *icmpHdr = malloc(sizeof(IcmpStruct));
   UdpStruct *udpHdr = malloc(sizeof(UdpStruct));
   int packetNumber = 0;
   int ipLen = 0;
   
   if (argc != 2)  {
      fprintf(stderr, "only 1 argument, the pcap file is required\n");
      exit(1);
   }
   handler = pcap_open_offline(argv[1], errbuff);
   if (handler == NULL) {
      fprintf(stderr, "error reading pcap file: %s\n", errbuff);
      exit(1);

   }
   
   while (pcap_next_ex(handler, &header, &packet) >= 0) {
      packetNumber++;
      printf("\nPacket number: %d", packetNumber);
      printf("  Packet Len: %d\n\n", header->caplen);
      ethernet = (EthernetStruct*)(packet);
      ethernetParse(ethernet);
 
      if (ntohs(ethernet->etherType) == ETHER_TYPE_ARP) {
         // the +6 is to skip the 6 bytes of information before opcode
         arpHdr = (ArpStruct*)(packet + ET_LEN + 6);
         arpParse(arpHdr);
      }
      else if (ntohs(ethernet->etherType) == ETHER_TYPE_IP) {
         ipHdr = (IpStruct*)(packet + ET_LEN);
         ipParse(ipHdr);
         ipLen = (ipHdr->verHdrLen & 0x0f) * 4;
         
         if (ipHdr->protocol == PROTOCOL_TCP) {
            initPseudoHdr(psHdr, ipHdr);
            tcpHdr = (TcpStruct*)(packet + ET_LEN + ipLen);
            tcpParse(tcpHdr, psHdr);            
         }
        
         else if (ipHdr->protocol == PROTOCOL_ICMP) {
            icmpHdr = (IcmpStruct*)(packet + ET_LEN + ipLen);
            icmpParse(icmpHdr);
         }
         
         else if (ipHdr->protocol == PROTOCOL_UDP) {
            udpHdr = (UdpStruct*)(packet + ET_LEN + ipLen);
            udpParse(udpHdr);   
         }
     
      }     
   }

   return 0;
   
}
