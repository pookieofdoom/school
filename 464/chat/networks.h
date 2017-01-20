#define MAX_LEN_MSG 31993
#define FLAG_M 5
#define FLAG_B 4
#define FLAG_L 10
#define FLAG_E 8
#define FLAG_1 1
#define FLAG_2 2
#define FLAG_3 3
#define FLAG_6 6
#define FLAG_7 7
#define FLAG_ACK 9
#define FLAG_11 11
#define FLAG_12 12
#define FLAG_13 13

// for the server side
int tcp_recv_setup();
void tcp_listen(int server_socket, int back_log);

// for the client side
int tcp_send_setup(char *host_name, char *port);


typedef struct __attribute__((packed)) 
{
   u_int sequence_number;
   u_short packet_length;
   u_char flag;
} NormalHeader;

typedef struct __attribute__((packed)) 
{
   NormalHeader header;
   u_char text_message[MAX_LEN_MSG];
} Message;