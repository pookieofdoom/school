#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>

#include "networks.h"
#include "cpe464.h"


int32_t udp_server(int port)
{
   int sk = 0;    //socket descriptor
   struct sockaddr_in local;  //socket address for us
   uint32_t len = sizeof(local); //length of local address
   
   //create the socket
   if ((sk = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
   {
      perror("socket");
      exit(-1);
   }
   
   //set up the socket 
   local.sin_family= AF_INET;         //internet family
   local.sin_addr.s_addr= INADDR_ANY; //wild card machine address
   local.sin_port= htons(port);       //let system choose the port
   
   //bind the name(address) to a port     
   if (bindMod(sk, (struct sockaddr *) &local, sizeof(local)) < 0)
   {
      perror("udp_server, bind");
      exit(-1);
   }
   
   //get the port name and print it out
   if (getsockname(sk, (struct sockaddr*)&local, &len) < 0)
   {
      perror("getsockname call");
      exit(-1);
   }
   
   printf("Server is using port %d \n", ntohs(local.sin_port));
   
   return(sk);
}

int32_t udp_client_setup(char *hostname, uint16_t port_num, Connection *connection)
{
   /*returns pointer to a sockaddr_in that it created or NULL if host not found */
   /* also passes back the socket number in sk*/
   
   struct hostent *hp = NULL;    //address of remote host
   
   connection->sk_num = 0;
   connection->len = sizeof(struct sockaddr_in);
   
   //create the socket
   if ((connection->sk_num = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
   {
      perror("udp_client_setup, socket");
      exit(-1);
   }
   
   //designate the addressing family
   connection->remote.sin_family = AF_INET;
   
   //get the address of the remote host and store
   if ((hp = gethostbyname(hostname)) == NULL)
   {
      printf("Host not found: %s\n", hostname);
      exit(-1);
   }
   
   memcpy(&(connection->remote.sin_addr), hp->h_addr, hp->h_length);
   
   //get the port used on the remote side and store
   connection->remote.sin_port = htons(port_num);
   
   return 0;
}

int32_t select_call(int32_t socket_num, int32_t seconds, int32_t microseconds, int32_t set_null)
{
   fd_set fdvar;
   struct timeval *timeout = NULL;
   
   if(set_null == NOT_NULL)
   {
      timeout = (struct timeval *) malloc(sizeof(struct timeval));
      timeout->tv_sec = seconds; // set timeout to second
      timeout->tv_usec = microseconds; //set timeout (in ms)
   }
   
   FD_ZERO(&fdvar);  //reset variables
   FD_SET(socket_num, &fdvar);
   
   if(selectMod(socket_num + 1, (fd_set *) &fdvar, (fd_set *) 0, (fd_set *) 0, timeout) < 0)
   {
      perror("select");
      exit(-1);
   }
   
   if (FD_ISSET(socket_num, &fdvar))
   {
      return 1;
   }
   else
   {
      return 0;
   }
}

int32_t send_buf(uint8_t *buf, int32_t len, Connection *connection, uint8_t flag, uint32_t seq_num, uint8_t *packet)
{
   int32_t send_len = 0;
   uint16_t checksum = 0;
   
   /*set up the packet (seq #, crc, flag, data) */
   if (len > 0)
      memcpy(&packet[7], buf, len);
      
   seq_num = htonl(seq_num);
   memcpy(&packet[0], &seq_num, 4);
   packet[6] = flag;
   
   memset(&packet[4], 0, 2);
   
   checksum = in_cksum((unsigned short *)packet, len + 8);
   
   memcpy(&packet[4], &checksum, 2);
   
   if ((send_len = sendtoErr(connection->sk_num, packet, len + 8, 0,
    (struct sockaddr *) &(connection->remote), connection->len)) < 0)
   {
      perror("send_buf, sendto");
      exit(-1);
   }
   
   return send_len;
}

int32_t recv_buf(uint8_t *buf, int32_t len, int32_t recv_sk_num, Connection *connection, uint8_t *flag, uint32_t *seq_num)
{
   uint8_t data_buf[MAX_LEN]= {0};
   int32_t recv_len = 0;
   uint32_t remote_len = sizeof(struct sockaddr_in);
   
   if ((recv_len = recvfrom(recv_sk_num, data_buf, len, 0, 
    (struct sockaddr *) &(connection->remote), &remote_len)) < 0)
   {
      perror("recv_buf, recvfrom");
      exit(-1);
   }
   //printf("this is recv_len %d\n", recv_len);
   //printf("this is data_buf\n%s\n", data_buf + 7);
   
   if (in_cksum((unsigned short *)data_buf, recv_len) !=0)
   {
      return CRC_ERROR;
   }
   
   *flag = data_buf[6];
   memcpy(seq_num, data_buf, 4);
   *seq_num = ntohl(*seq_num);
   
   if(recv_len > 7)
      memcpy(buf, &data_buf[7], recv_len - 8);
   
   connection->len = remote_len;
   return (recv_len - 8);

}
