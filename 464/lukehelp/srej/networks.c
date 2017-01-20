/*
 networks.c

 Courtesy of HUGH SMITH
*/

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
#include <netinet/in.h>
#include <netdb.h>

#include "cpe464.h"
#include "networks.h"

/*
 * Function that initializes the server socket, either with the given argument
 *  or with a random one if the argument is 0
 * Prints out the port number it uses
 */
int32_t udp_server(int portNum) {
  int sk = 0;
  struct sockaddr_in local;      /* socket address for local side  */
  uint32_t len = sizeof(local);  /* length of local address        */

  /* create the socket  */
  sk = socket(AF_INET, SOCK_DGRAM, 0);
  if(sk < 0)
    {
      perror("socket call");
      exit(-1);
    }

  local.sin_family= AF_INET;         //internet family
  local.sin_addr.s_addr= INADDR_ANY; //wild card machine address
  local.sin_port = htons(portNum);      //let system choose the port

  /* bind the name (address) to a port */
  if (bindMod(sk, (struct sockaddr *)&local, sizeof(local)) < 0)
    {
      perror("bind call");
      exit(-1);
    }
    
  //get the port name and print it out
  if (getsockname(sk, (struct sockaddr*)&local, &len) < 0)
    {
      perror("getsockname call");
      exit(-1);
    }

  printf("Using port %d \n", ntohs(local.sin_port));
	        
  return sk;
}

/*
 * Function that sets up the connection from the client to the server on the 
 *  given hostname using the given port number, placing the info into the 
 *  connection pointer
 */
int32_t udp_client_setup(char *hostname, uint16_t port_num,
			 Connection *connection) {
  struct hostent *hp = NULL;

  connection->sk_num = 0;
  connection->len = sizeof(struct sockaddr_in);

  if ((connection->sk_num = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("udp_client_setup, socket");
    exit(-1);
  }

  connection->remote.sin_family = AF_INET;

  hp = gethostbyname(hostname);

  if (hp == NULL) {
    printf("host '%s' not found\n", hostname);
    return -1;
  }

  memcpy(&(connection->remote.sin_addr), hp->h_addr, hp->h_length);

  connection->remote.sin_port = htons(port_num);

  return 0;
}

/*
 * Function that calls a select call on the given socket, with a 
 *  seconds.mseconds timeout period if set_null = NOT_NULL, or timeout of
 *  0 otherwise.
 * Returns 1 if there is data available, 0 otherwise
 */
int32_t select_call(int32_t socket_num, int32_t seconds,
		    int32_t mseconds, int32_t set_null) {

  fd_set fdvar;
  struct timeval *timeout = NULL;

  if (set_null == NOT_NULL) {
    timeout = (struct timeval *)malloc(sizeof(struct timeval));
    timeout->tv_sec = seconds;
    timeout->tv_usec = mseconds;
  }

  FD_ZERO(&fdvar);
  FD_SET(socket_num, &fdvar);

  //Call the modified select
  if (selectMod(socket_num+1, (fd_set *)&fdvar, (fd_set *)0, (fd_set *)0, timeout) < 0) {
    perror("select");
    exit(-1);
  }

  if (FD_ISSET(socket_num, &fdvar)) {
    return 1;
  } else {
    return 0;
  }
}

/*
 * Function that sends the data given in 'buf' on the 'connection' socket
 * It sets up a header using the seq_num and flag values, and calculating
 *  the internet checksum bytes
 */
int32_t send_buf(uint8_t *buf, uint32_t len, Connection *connection,
		 uint8_t flag, uint32_t seq_num, uint8_t *packet) {

  int32_t send_len = 0;
  int16_t checksum = 0;
  
  //If there is any data, add it after the header
  if (len > 0) 
    memcpy(&packet[7], buf, len);
  
  //Add the seq number and flag
  seq_num = htonl(seq_num);
  memcpy(&packet[0], &seq_num, 4);
  packet[6] = flag;

  //Add 0's for checksum bytes
  memset(&packet[4], 0, 2);
  checksum = in_cksum((unsigned short *)packet, len+8);
  memcpy(&packet[4], &checksum, 2);

  printf("data after copy to packet: %s\n", &packet[7]);
  
  if ((send_len = sendtoErr(connection->sk_num, packet, len+8, 0,
			    (struct sockaddr *)&(connection->remote),
			    connection->len)) < 0) {
    perror("send_buf, sendto");
    exit(-1);
  }

  return send_len;
}

/*
 * Function that places any data found in the packet into 'buf'
 * Populates the flag and seqnum values with those found in the packet's header
 * Checks for CRC error and returns if one was found
 */
int32_t recv_buf(uint8_t *buf, int32_t len, int32_t recv_sk_num,
		Connection *connection, uint8_t *flag, int32_t *seq_num) {

  char data_buf[MAX_LEN];
  int32_t recv_len = 0;
  uint32_t remote_len = sizeof(struct sockaddr_in);

  if ((recv_len = recvfrom(recv_sk_num, data_buf, len, 0,
			   (struct sockaddr *)&(connection->remote), &remote_len)) < 0) {
    perror("recv_buf, recvfrom");
    exit(-1);
  }

  printf("Received data: %s\n", data_buf);
  
    *flag = data_buf[6];
    
    printf("this is flag %d\n", *flag);

  if (in_cksum((unsigned short *)data_buf, recv_len) != 0) {
    return CRC_ERROR;
  }


  memcpy(seq_num, data_buf, 4);

  *seq_num = ntohl(*seq_num);

  if (recv_len > 7)
    memcpy(buf, &data_buf[7], recv_len - 8);

  connection->len = remote_len;

  return (recv_len - 8);  
}
