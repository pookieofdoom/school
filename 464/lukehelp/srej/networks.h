#ifndef NETWORKS_H
#define NETWORKS_H

#include <netinet/in.h>

#define MAX_LEN 1500
#define START_SEQ_NUM 1

//Enum for the different flags sent between client and server in the headers
enum FLAG {
  ZERO, DATA, NOT_USED_2, RR, SREJ, NOT_USED_5, ESTAB,
  ESTACK, ESTNACK, LAST_DATA, FINISHED, CRC_ERROR = -1
};

enum SELECT {
  SET_NULL, NOT_NULL
};

typedef struct connection Connection;

struct connection {
  int32_t sk_num;
  struct sockaddr_in remote;
  uint32_t len;
};

typedef struct windowNode {
  uint8_t buffer[MAX_LEN];
} windowNode;

int32_t udp_server(int portNum);
int32_t udp_client_setup(char *hostname, uint16_t portNum, Connection *conn);
int32_t select_call(int32_t socketNum, int32_t seconds, int32_t msecs, int32_t set_null);
int32_t send_buf(uint8_t *buf, uint32_t len, Connection *conn, uint8_t flag,
		 uint32_t seq_num, uint8_t *packet);
int32_t recv_buf(uint8_t *buf, int32_t len, int32_t recv_sk_num,
		 Connection *fromConn, uint8_t *flag, int32_t *seq_num);

#endif
