#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
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

typedef enum State STATE;

enum State
{
   START, DONE, FILENAME, RECV_DATA, FILE_OK
};

typedef struct 
{
  uint32_t seq_num;
  int32_t buf_len;
  uint8_t flag;
  uint8_t buf[MAX_LEN];
} Window_Buffer;

/*proto funcs*/

int check_args(int argc, char **argv);
void main_process(int32_t server_socket);
void process_client(int32_t server_socket, uint8_t *buf, int32_t recv_len, Connection *client);
STATE filename(Connection *client, uint8_t *buf, int32_t recv_len, int32_t *data_file, int32_t *buf_size, int32_t *window_size);
STATE recv_data(Connection *client, Window_Buffer *window_buf,  int32_t output_file, int32_t buf_size, int32_t window_size);
void send_ack(Connection *client, uint8_t recv_seq_num, uint8_t flag, uint32_t *sever_seq);
int store_data(Connection *client, int32_t output_file,  Window_Buffer *window_buf, int32_t *index, 
 int32_t buf_size,  uint32_t *expected_seq_num, int32_t window_size, uint32_t *server_seq, uint32_t diff);


int main (int argc, char **argv)
{
   int32_t server_socket = 0;
   int port_number = check_args(argc, argv);
   sendtoErr_init(atof(argv[1]), DROP_ON, FLIP_ON, DEBUG_ON, RSEED_ON);
   
   /* set up the main server port */
   server_socket = udp_server(port_number);
   
   while (1)
   {
      main_process(server_socket);
   }
   return 0;
}

int check_args(int argc, char **argv)
{
   //error rate
   if (atof(argv[1]) < 0 || atof(argv[1]) >= 1)
   {
      printf("Error rate needs to be between 0 and less than 1 and is: "
       "%f\n", atof(argv[1]));
       exit(-1);
   }

   if (argc == 3)
   {
      return atoi(argv[2]);
   }
   else if (argc !=2)
   {
      printf("Usage %s error_rate and port number(optional)", argv[0]);
      exit(-1);
   }


   
   return 0;
}

void main_process(int32_t server_socket)
{
   pid_t pid = 0;
   int status = 0;
   uint8_t buf[MAX_LEN];
   Connection client;
   uint8_t flag = 0;
   uint32_t seq_num = 0;
   int32_t recv_len = 0;
   
   if (select_call(server_socket, 1, 0, NOT_NULL) == 1)
   {
      recv_len = recv_buf(buf, 1000, server_socket, &client, &flag, &seq_num);
      if (recv_len != CRC_ERROR)
      {
         /*fork will go here*/
         if ((pid = fork()) < 0)
         {
            perror("fork");
            exit(-1);
         }
         //process child
         if (pid == 0)
         {
            process_client(server_socket, buf, recv_len, &client);
            exit(0);
         }
      }
      while (waitpid(-1, &status, WNOHANG) >0)
      {
         printf("processed wait\n");
      }
   }
}

void process_client(int32_t server_socket, uint8_t *buf, int32_t recv_len, Connection *client)
{
   STATE state = START;
   int32_t data_file = 0;
   //int32_t packet_len = 0;
   //uint8_t packet[MAX_LEN];
   int32_t buf_size = 0;
   uint32_t seq_num = START_SEQ_NUM;
   int32_t window_size = 0;
   Window_Buffer *window_buf;
   
   while (state != DONE)
   {
      switch(state)
      {
         case START:
            state = FILENAME;
            break;
         
         case FILENAME:
            seq_num = 1;
            state = filename(client, buf, recv_len, &data_file, &buf_size, &window_size);
            window_buf = calloc(window_size, sizeof(Window_Buffer));
            break;
            
         case RECV_DATA:
            state = recv_data(client, window_buf, data_file, buf_size, window_size);
            break;
            
         case DONE:
            break;
         
         default:
            printf("In default\n");
            state = DONE;
            break;
      }

   }
}

STATE filename(Connection *client, uint8_t *buf, int32_t recv_len, int32_t *data_file, int32_t *buf_size, int32_t *window_size)
{
   uint8_t response[1];
   char fname[MAX_LEN];

   memcpy(buf_size, buf, 4);
   memcpy(window_size, buf + 4, 4);
   memcpy(fname, &buf[8], recv_len - 8);
   
   /* Create client socket to allow for processing this particular client*/
   if ((client->sk_num = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
   {
      perror("filename, open client socket");
      exit(-1);
   }
   
   if (((*data_file) = open(fname, O_WRONLY | O_CREAT, 0666)) < 0)
   {
      send_buf(response, 0, client, FNAME_BAD, 0, buf);
      return DONE;
   }
   else
   {
      //write(*data_file, "hi", 4);
      send_buf(response, 0, client, FNAME_OK, 0, buf);
      return RECV_DATA;
   }
}

STATE recv_data(Connection *client, Window_Buffer *window_buf, int32_t output_file, int32_t buf_size, int32_t window_size)
{
   uint32_t recv_seq_num = 0;
   static uint32_t server_seq = 1;
   uint8_t flag = 0;
   int32_t data_len = 0;
   uint8_t data_buf[MAX_LEN];
   int32_t index = 0;
   uint32_t diff = 0;
   static uint32_t expected_seq_num = START_SEQ_NUM;
   int store_return ;
   
   if (select_call(client->sk_num, 10, 0, NOT_NULL) == 0)
   {
      printf("Timeout after 10 seconds, client done. \n");
      return DONE;
   }
   
   data_len = recv_buf(data_buf, buf_size + 8, client->sk_num, client, &flag, &recv_seq_num);
   
   /* do state RECV_DATA again if there is a crc error (don't send ack, don't write data)*/
   if (data_len == CRC_ERROR)
   {
      //CRC_ERROR means corrupted packet so ignore it and keep trying to recv
      return RECV_DATA;
   }
   // need to send a different seq_num and seq_num + 1 is in ACK
   if (recv_seq_num == expected_seq_num)
   {
      expected_seq_num++;
      write(output_file, &data_buf, data_len);
   }
   else if (recv_seq_num > expected_seq_num)
   {
      //store this packet into buffer and go into store_data function (this makes parameters smaller)
      diff = recv_seq_num - expected_seq_num;

      for (index = 0; index < diff; index++)
      {
         send_ack(client, expected_seq_num + index, SREJ, &server_seq);
      }

      index = recv_seq_num % window_size;
      window_buf[index].seq_num = recv_seq_num;
      window_buf[index].buf_len = data_len;
      window_buf[index].flag = flag;
      memcpy(window_buf[index].buf, data_buf, data_len);
      if ((store_return = store_data(client, output_file, window_buf, &index, buf_size, &expected_seq_num, window_size, &server_seq, diff)) == 1)
         return RECV_DATA;
      else
         return DONE; 

   }

   
   if (flag == DATA)
   {
      /* send ACK */
      send_ack(client, recv_seq_num, RR, &server_seq);
      //send_buf(packet, 8, client, RR, seq_num, packet);
   }
   
   else if (flag == END_OF_FILE)
   {
      //send_buf(packet, 8, client, END_OF_FILE, seq_num, packet);
      send_ack(client, recv_seq_num, END_OF_FILE, &server_seq);
      printf("File Done... will timeout in 10 seconds\n");
   }
   

   
   return RECV_DATA;
}

void send_ack(Connection *client, uint8_t recv_seq_num, uint8_t flag, uint32_t *server_seq)
{
   uint8_t packet[MAX_LEN];
   uint8_t data;
   if (flag == RR || flag == END_OF_FILE)
      data = recv_seq_num + 1;
   else if (flag == SREJ)
      data = recv_seq_num;

   send_buf(&data, 4, client, flag, *server_seq, packet);
   (*server_seq)++;
}

int store_data(Connection *client, int32_t output_file,  Window_Buffer *window_buf, int32_t *index, 
 int32_t buf_size,  uint32_t *expected_seq_num, int32_t window_size, uint32_t *server_seq, uint32_t diff)
{
   uint8_t data_buf[MAX_LEN];
   uint8_t flag = 0;
   uint32_t recv_seq_num = 0;
   int32_t data_len = 0;
   int32_t seq_tracker = 0;
   int32_t loop_count = diff + 1;
   int32_t count = 1;
   int done = 0;
   int i;

   //send_ack(client, *expected_seq_num, SREJ, server_seq);

   while(!done)
   {

      
      if (select_call(client->sk_num, 10, 0, NOT_NULL) == 0)
      {
         printf("Timeout after 10 seconds in the store_data.., client done. \n");
         return -1;
      }

      data_len = recv_buf(data_buf, buf_size + 8, client->sk_num, client, &flag, &recv_seq_num);
      if (data_len != CRC_ERROR)
      {
         seq_tracker = *expected_seq_num + loop_count;

         if (recv_seq_num != *expected_seq_num)
         {
            if (recv_seq_num < *expected_seq_num)
            {
               //ack must have been lost
               //resedning ack
               send_ack(client, recv_seq_num, RR, server_seq);
            }
            else
            {
               //add into buffer         
               *index = recv_seq_num % window_size;
               window_buf[*index].seq_num = recv_seq_num;
               window_buf[*index].buf_len = data_len;
               window_buf[*index].flag = flag;
               memcpy(window_buf[*index].buf, data_buf, data_len);
               count++;
               
               if(recv_seq_num > seq_tracker)
               {
                  diff = recv_seq_num - seq_tracker;
                  for (i = 0; i < diff; i++)
                     send_ack(client, seq_tracker + i, SREJ, server_seq);
                  loop_count += diff;
               }
               loop_count++;
            }

         }
         else
         {
            //expected_num == recv_seq_num
            *index = *expected_seq_num % window_size;
            write(output_file, &data_buf, data_len);
            send_ack(client, *expected_seq_num, RR, server_seq);
            (*expected_seq_num)++;
            *index = *expected_seq_num % window_size;
            //empty out the window
            while (window_buf[*index].seq_num == *expected_seq_num)
            {
               write(output_file, window_buf[*index].buf, window_buf[*index].buf_len);
               count--;

               if (window_buf[*index].flag == DATA)
               {
                  send_ack(client, window_buf[*index].seq_num, RR, server_seq);
                  (*expected_seq_num)++;
                  *index = *expected_seq_num % window_size;
               }
               else if(window_buf[*index].flag == END_OF_FILE)
               {
                  send_ack(client, window_buf[*index].seq_num, END_OF_FILE, server_seq);
                  (*expected_seq_num)++;
                  *index = *expected_seq_num % window_size;
                  printf("File Done... will timeout in 10 seconds\n");
                  return 1;  
               }

            }
            if (*expected_seq_num > window_buf[*index].seq_num)
            {
               //this is when we are done with the window
               if (count == 0)
                  done = 1;
            }
            else
            {
               //expected < seq (this can occur if another packet is lost while waiting for SREJ)
               //send another selective reject
               done = 0;

            }

         }
      }
      
   }

   return done;
}
