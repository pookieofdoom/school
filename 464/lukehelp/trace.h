#ifndef TRACE_H
#define TRACE_H

#include <pcap.h>

#define MAC_ADDR_SIZE 6

#define ETH_ADDR_LEN 6
#define ETH_HEAD_SIZE 14
#define ETH_IP_TYPE 8
#define ETH_ARP_TYPE 1544

struct ethHeader { //should be 14 bytes
  u_char desthost[MAC_ADDR_SIZE]; //6
  u_char srchost[MAC_ADDR_SIZE]; //6
  u_short type; //2
} __attribute__((packed));
typedef struct ethHeader ethHeader;

#define IP_HEAD_SIZE 20
#define NUM_IP_FIELDS 4
#define IP_VERS_SHIFT 4
#define IP_DFSRV_SHIFT 2
#define IP_ECN_MASK 0x03
#define IP_ICMP_PROTO 1
#define IP_UDP_PROTO 17
#define IP_TCP_PROTO 6

struct ipHeader { //should be 20 bytes
  u_char type; //1
  u_char tos; //1
  u_short length; //2
  u_int id; //4
  u_char ttl; //1
  u_char protocol; //1
  u_char cs_one; //1
  u_char cs_two; //1
  u_char srcip[NUM_IP_FIELDS]; //4
  u_char destip[NUM_IP_FIELDS]; //4    
} __attribute__((packed));
typedef struct ipHeader ipHeader;

#define UDP_HEAD_SIZE 20
#define UDP_DNS_PORT 53

struct udpHeader { //should be 8
  u_short srcport;
  u_short destport;
  u_short leng;
  u_short checksum;
} __attribute__((packed));
typedef struct udpHeader udpHeader;

#define ICMP_HEAD_SIZE 8
#define ICMP_REQUEST 8
#define ICMP_REPLY 0

struct icmpHeader { //Should be 8 bytes
  u_char type; //1
  u_char code; //1
  u_short checksum; //2
  u_int info; //4
} __attribute__((packed));
typedef struct icmpHeader icmpHeader;

#define ARP_HEAD_SIZE 28
#define ARP_REQUEST 256
#define ARP_REPLY 512

struct arpHeader { //Should be 28
  u_short hwtype; //2
  u_short ptype; //2
  u_char hwaddrlen; //1
  u_char paddrlen; //1
  u_short opcode; //2
  u_char sendmac[MAC_ADDR_SIZE]; //6
  u_char sendip[NUM_IP_FIELDS]; //4
  u_char targmac[MAC_ADDR_SIZE]; //6
  u_char targip[NUM_IP_FIELDS]; //4
} __attribute__((packed));
typedef struct arpHeader arpHeader;

#define TCP_HEAD_SIZE 20
#define TCP_SYN_MASK 0x02
#define TCP_RST_MASK 0x04
#define TCP_FIN_MASK 0x01
#define TCP_ACK_MASK 0x10

struct tcpHeader { //should be 20
  u_short srcport; //2
  u_short destport; //2
  u_int seq; //4
  u_int acknum; //4
  u_char offset; //1
  u_char flags; //1
  u_short winsize; //2
  u_char cs_one; //1
  u_char cs_two; //1
  u_short urg; //2
} __attribute__((packed));
typedef struct tcpHeader tcpHeader;

struct tcpPseudo {
  u_char srcip[NUM_IP_FIELDS]; //4
  u_char destip[NUM_IP_FIELDS]; //4
  u_char zeroes;
  u_char proto;
  u_short tcplen;
}__attribute__((packed));
typedef struct tcpPseudo tcpPseudo;


#endif
