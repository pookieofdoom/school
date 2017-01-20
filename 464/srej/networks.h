#ifndef _NETWORKS_H_
#define _NETWORKS_H_

#define MAX_LEN 1500
#define START_SEQ_NUM 1

#include <netinet/in.h>
#include <netdb.h>

enum FLAG
{
   //0           1      2        3    4        5          6      7         8           9           -1          
   NOT_USED_0, DATA, NOT_USED_2, RR, SREJ, NOT_USED_5, FNAME, FNAME_OK, FNAME_BAD, END_OF_FILE, CRC_ERROR = -1
};

enum SELECT
{
   SET_NULL, NOT_NULL
};

typedef struct connection Connection;

struct connection
{
   int32_t sk_num;
   struct sockaddr_in remote;
   uint32_t len;
};

int32_t udp_server(int port);
int32_t udp_client_setup(char *hostname, uint16_t port_num, Connection *connection);
int32_t select_call(int32_t socket_num, int32_t seconds, int32_t microseconds, int32_t set_null);
int32_t send_buf(uint8_t *buf, int32_t len, Connection *connection, uint8_t flag, uint32_t seq_num, uint8_t *packet);
int32_t recv_buf(uint8_t *buf, int32_t len, int32_t recv_sk_num, Connection *from_connection, uint8_t *flag, uint32_t *seq_num);

#endif
