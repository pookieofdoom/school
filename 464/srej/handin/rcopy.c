/*CPE 464 
   Anthony Dinh
   rcopy.c
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

#include "networks.h"
#include "cpe464.h"


typedef enum State STATE;

enum State
{
   DONE, FILENAME, WINDOW_OPEN, WINDOW_CLOSED, FILE_OK, PROCESS_ACK, LAST_DATA
};

typedef struct 
{
  uint32_t seq_num;
  int32_t buf_len;
  uint8_t flag;
  uint8_t buf[MAX_LEN];
} Window_Buffer;

/*proto functions */

void check_args(int argc, char **argv);
STATE filename(char *fname, int32_t buf_size, int32_t window_size);
void processStates();
/*STATE send_data(Connection *server, uint8_t *packet, int32_t *packet_len,
 int32_t data_file, int buf_size, uint32_t *seq_num, int32_t window_size); */
STATE send_data(Window_Buffer *window_buf, int32_t window_size, int32_t *bottom_window, int32_t * upper_edge, int32_t index); 
int32_t read_data_into_window(Window_Buffer *window_buf, int32_t data_file,
 int32_t buf_size, int32_t window_size, uint32_t *seq_num);
uint32_t get_ack(uint32_t *recv_ack);
void update_window(Window_Buffer *window_buf, int32_t window_size, int32_t *bottom_window, int32_t *upper_edge, uint32_t recv_ack);
STATE last_data(Window_Buffer *window_buf, int32_t window_size, int32_t *bottom_window, int32_t *upper_edge, int *resend_counter);
STATE window_closed(Window_Buffer *window_buf, int32_t window_size, int32_t *bottom_window, int32_t *upper_edge, int *resend_counter); 

Connection server;

int main (int argc, char **argv)
{
   check_args(argc, argv);  
   sendErr_init(atof(argv[4]), DROP_ON, FLIP_ON, DEBUG_ON, RSEED_ON);
   processStates(argv);
   return 0;
}


/*the main process for rcopy */
void processStates(char **argv)
{
   STATE state = FILENAME;
   int32_t select_count = 0;
   int last_count = 0;
   int resend_counter = 0;
   int32_t input_file = 0;
   int32_t buf_size = atoi(argv[3]);
   uint32_t seq_num = START_SEQ_NUM;
   int32_t window_size = atoi(argv[5]);
   int32_t bottom_window = 1;
   int32_t upper_edge = bottom_window + window_size;
   int32_t index = 0;
   Window_Buffer *window_buf = malloc(sizeof(Window_Buffer) * window_size); //window containing window_size of buffers(not including the header)

   while (state != DONE)
   {
      switch (state)
      {
         // minimize this part
         case FILENAME:
            /*Everytime we try to start/restart a connection get a new socket */
            if (udp_client_setup(argv[6], atoi(argv[7]), &server) < 0)
            {
               perror("host not found");
               exit(-1);
            }
            
            state = filename(argv[2], buf_size, window_size);
            
            /*if no response from server then repeat sending filename*/
            if (state == FILENAME)
               close(server.sk_num);
            
            select_count++;
            if (select_count > 9)
            {
               printf("Server unreachable, client terminating\n");
               state = DONE;
            }
            break;
         //write a function for this   
         case FILE_OK:

            if ((input_file = open(argv[1], O_RDONLY)) < 0)
            {
               perror("File open");
               state = DONE;
            }
            else
            {
               //read_window(window_buf, input_file, buf_size, window_size, &seq_num);
               state = WINDOW_OPEN;
            }
            break;
            
         case WINDOW_OPEN:
            //read data into window -> send data -> check for reply -> repeat(until window closes or problems)
            if (seq_num != upper_edge)
            {
               index = read_data_into_window(window_buf, input_file, buf_size, window_size, &seq_num);
               state = send_data(window_buf, window_size, &bottom_window, &upper_edge, index);
            }
            else
            {
               state = WINDOW_CLOSED;
            }
            break;
         
         case WINDOW_CLOSED:
            //if timeout, resend lowest window packet
            state = window_closed(window_buf, window_size, &bottom_window, &upper_edge, &resend_counter);
            if (resend_counter > 9)
            {
               printf("Resent 10 times, connection lost\n");
               state = DONE;
            }
            break;
            
            
         case LAST_DATA:
            state = last_data(window_buf, window_size, &bottom_window, &upper_edge, &last_count);

            if (last_count > 9)
            {
               printf("Resent 10 times, connection lost\n");
               state = DONE;
            }
            
         case DONE:
            break;
         
         default:
            printf("ERROR - in default state\n");
            break;
      }
   }
}

//send the file name, the file size, and window size
STATE filename(char *fname, int32_t buf_size, int32_t window_size)
{
   uint8_t packet[MAX_LEN];
   uint8_t buf[MAX_LEN];
   uint8_t flag = FNAME;
   uint32_t seq_num = 0;
   int32_t fname_len = strlen(fname) + 1;
   int32_t recv_check = 0;
   
   memcpy(buf, &buf_size, 4);
   memcpy(&buf[4], &window_size, 4);
   memcpy(&buf[8], fname, fname_len);
   
   send_buf(buf, fname_len + 8, &server, flag, seq_num, packet);

   if (select_call(server.sk_num, 1, 0, NOT_NULL) == 1)
   {
      recv_check = recv_buf(packet, 1000, server.sk_num, &server, &flag, &seq_num);
      
      /*check for bit flip ... if so send the file name again */
      if (recv_check == CRC_ERROR)
      {
         return FILENAME;
      }
      
      if (flag == FNAME_BAD)
      {
         printf("File %s not found\n", fname);
         return(DONE);
      }
      return (FILE_OK);
   }
   return (FILENAME);
}


STATE send_data(Window_Buffer *window_buf, int32_t window_size, int32_t *bottom_window, int32_t *upper_edge, int32_t index)
{
   //read data into window -> send data -> check for ack
   uint8_t packet[MAX_LEN] = {0};
   uint8_t recv_flag = 0;
   uint32_t recv_ack = 0;
   int32_t srej_index = 0;

   send_buf(window_buf[index].buf, window_buf[index].buf_len, &server,
    window_buf[index].flag, window_buf[index].seq_num, packet);

   

   if (window_buf[index].flag == END_OF_FILE)
   {
      return LAST_DATA;
   }

   //check for ACK immediately (timeout = 0)
   if (select_call(server.sk_num, 0, 0, NOT_NULL) == 1)
   {
      
      if((recv_flag = get_ack(&recv_ack)) == RR)
      {
         //update the window
         update_window(window_buf, window_size, bottom_window, upper_edge, recv_ack);
      }
      else if (recv_flag == SREJ)
      {
         //resend that packet

         srej_index = recv_ack % window_size;
         send_buf(window_buf[srej_index].buf, window_buf[srej_index].buf_len, &server,
          window_buf[srej_index].flag, window_buf[srej_index].seq_num, packet);
      }

   }

   return WINDOW_OPEN;


}
 
int32_t read_data_into_window(Window_Buffer *window_buf, int32_t data_file, int32_t buf_size,
 int32_t window_size, uint32_t *seq_num)
{
   int32_t len_read = 0;

   int32_t index = *seq_num % window_size;
      if ((len_read = read(data_file, window_buf[index].buf, buf_size)) < 0)
      {
         perror("send_data, read error");
         exit(-1);
      }
      
      else if (len_read != buf_size)
      {
         window_buf[index].seq_num = *seq_num;
         window_buf[index].buf_len = len_read;
         window_buf[index].flag = END_OF_FILE;
      }
      else
      {
         window_buf[index].seq_num = *seq_num;
         (*seq_num)++;
         window_buf[index].buf_len = len_read;
         window_buf[index].flag = DATA;    
      }

   return index;     
}

//note that the recv_seq is not the same value as the RR
uint32_t get_ack(uint32_t *recv_ack)
{
   uint8_t packet[MAX_LEN] = {0};
   uint8_t recv_flag = 0;
   uint32_t recv_seq = 0;
    //receive RR or SREJ
   if (recv_buf(packet, 1000, server.sk_num, &server, &recv_flag, &recv_seq) != CRC_ERROR)
   {
      //probably wrong, ask luke what serer is suppose to send
      memcpy(recv_ack, packet, sizeof(uint32_t));
      return recv_flag;

   }
   else
   {
      return CRC_ERROR;
   }
   return 0;
}

void update_window(Window_Buffer *window_buf, int32_t window_size, int32_t *bottom_window, int32_t *upper_edge, uint32_t recv_ack)
{
   *bottom_window = recv_ack;
   *upper_edge = *bottom_window + window_size;
}

STATE window_closed(Window_Buffer *window_buf, int32_t window_size, int32_t *bottom_window, int32_t *upper_edge, int *resend_counter)
{
   uint8_t recv_flag = 0;
   uint8_t packet[MAX_LEN] = {0};
   uint32_t recv_ack = 0;
   int32_t resend_index = *bottom_window % window_size;
   int32_t srej_index = 0;

   if (select_call(server.sk_num, 1, 0, NOT_NULL) == 1)
   {
      // need to process the RR
      if ((recv_flag = get_ack(&recv_ack)) == RR)
      {
         //update the window and go back to sending data
         update_window(window_buf, window_size, bottom_window, upper_edge, recv_ack);
         *resend_counter = 0;
         return WINDOW_OPEN;

      }
      else if (recv_flag == SREJ)
      {
         srej_index = recv_ack % window_size;
         send_buf(window_buf[srej_index].buf, window_buf[srej_index].buf_len, &server,
          window_buf[srej_index].flag, window_buf[srej_index].seq_num, packet);
         *resend_counter = 0;
         return WINDOW_CLOSED;
      }
      else
      {
         return WINDOW_CLOSED;
      }

   }
   else
   {
      //no ack to update window with
      //break deadlock by sending lowest window packet
      send_buf(window_buf[resend_index].buf, window_buf[resend_index].buf_len, &server,
       window_buf[resend_index].flag, window_buf[resend_index].seq_num, packet);
      (*resend_counter)++;
      return WINDOW_CLOSED;
   }
   return DONE;
}

STATE last_data(Window_Buffer *window_buf, int32_t window_size, int32_t *bottom_window, int32_t *upper_edge, int *resend_counter)
{
   uint8_t recv_flag = 0;
   uint32_t recv_ack = 0;
   uint8_t packet[MAX_LEN] = {0};
   int32_t resend_index = *bottom_window % window_size;
   int32_t srej_index = 0;

   if (select_call(server.sk_num, 1, 0, NOT_NULL) == 1)
   {
      if ((recv_flag = get_ack(&recv_ack)) == END_OF_FILE)
      {
         return DONE;
      }
      else if (recv_flag == RR)
      {
         //should i process the RR's if last data was sent
         update_window(window_buf, window_size, bottom_window, upper_edge, recv_ack);
         *resend_counter = 0;
         return LAST_DATA;
      }
      else if (recv_flag == SREJ)
      {
         //selective reject
         srej_index = recv_ack % window_size;
         send_buf(window_buf[srej_index].buf, window_buf[srej_index].buf_len, &server,
          window_buf[srej_index].flag, window_buf[srej_index].seq_num, packet);
         *resend_counter = 0;
      }
      else
      {
         //flag is CRC_ERROR, going to ignore
         return LAST_DATA;
      }
   }
   else
   {
      //when last few packets are lost, or flipped, expecially the file done packet
      resend_index = *bottom_window % window_size;
      send_buf(window_buf[resend_index].buf, window_buf[resend_index].buf_len, &server,
       window_buf[resend_index].flag, window_buf[resend_index].seq_num, packet);
      (*resend_counter)++;
      return LAST_DATA;
   }

   return LAST_DATA;
}



void check_args(int argc, char **argv)
{
   int32_t file_check;

   if (argc != 8)
   {
      printf("Usage %s [local-file] [romate-file] [buffer-size] [error-percent] "
       "[window-size] [hostname] [port]\n", argv[0]);
       exit(-1);
   }
   
   if (strlen(argv[1]) > 1000)
   {
      printf("local filename too long, needs to be less than 1000 and "
       "is %zd\n", strlen(argv[1]));
       exit(-1);
   }

   if ((file_check = open(argv[1], O_RDONLY)) < 0)
   {
      printf("Error opening local file: %s\n", argv[1]);
      exit(-1);
   }
 
   if (strlen(argv[2]) > 1000)
   {
      printf("remote filename too long, needs to be les than 1000 and "
       "is %zd\n", strlen(argv[2]));
       exit(-1);
   }
   
   if (atoi(argv[3]) < 400 || atoi(argv[3]) > 1400)
   {
      printf("Buffer size needs to be between 400 and 1400 and is: "
       "%d\n", atoi(argv[3]));
      exit(-1);
   } 
   if (atof(argv[4]) < 0 || atof(argv[4]) >= 1)
   {
      printf("Error rate needs to be between 0 and less than 1 and is: "
       "%f\n", atof(argv[4]));
       exit(-1);
   }

}