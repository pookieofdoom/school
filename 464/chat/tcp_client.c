/******************************************************************************
* tcp_client.c
*
*****************************************************************************/

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
#include <ctype.h>

#include "networks.h"
#include "testing.h"


#define CMD_SKIP 3


void set_client_handle(int argc, char * argv[], u_char *client_handle)
{
 
   if(argc!= 4)
   {
      printf("usage: %s host-name port-number \n", argv[0]);
      exit(1);
   }

   memcpy(client_handle, argv[1], strlen(argv[1]));

}


int get_input(char* input)
{
   int send_len= 0;        //amount of data to send

   while ((input[send_len] = getchar()) != '\n' && send_len < MAX_LEN_MSG - 1)
   {
      send_len++;
   }

   input[send_len] = '\n';
   return send_len;
}

u_short get_message(char* input, u_char *message)
{
   int msg_length= 0;        //amount of data to send
   int input_index = 0;
   if (input[input_index++] != '\n')
   {
     
      while ((message[msg_length] = input[input_index]) != '\n' && msg_length < MAX_LEN_MSG - 1)
      {
         msg_length++;
         input_index++;
      }

   }

   message[msg_length] = '\0';
      //text message
   //printf("this is msg %s\n", message);
   return msg_length + 1;
}


int parse_target_handle(char *cmd, u_char *handle)
{
   int stringIndex;
   int handleIndex = 0;
   for(stringIndex = 0; stringIndex < strlen(cmd); stringIndex++) {
      if(handleIndex == 255 || cmd[stringIndex] == ' ' || cmd[stringIndex] == '\n') {
         handle[handleIndex] = '\0';
         //printf("this is sender handle %s\n", handle);
         return handleIndex;
      }
      handle[handleIndex] = cmd[stringIndex];
      handleIndex++;
   }
   handle[handleIndex] = '\0';
   return handleIndex;
}

int parse_client_handle(char *handle, char *msg_handle)
{
   int index;
   for (index = 0; index < strlen(handle); index++) 
   {
      msg_handle[index] = handle[index];
   }
   return strlen(handle);
}

int tcp_send_setup(char *host_name, char *port)
{
   int socket_num;
   struct sockaddr_in remote;       // socket address for remote side
   struct hostent *hp;              // address of remote host

   // create the socket
   if ((socket_num = socket(AF_INET, SOCK_STREAM, 0)) < 0)
   {
      perror("socket call");
      exit(-1);
   }
   

   // designate the addressing family
   remote.sin_family= AF_INET;

   // get the address of the remote host and store
   if ((hp = gethostbyname(host_name)) == NULL)
   {
      printf("Error getting hostname: %s\n", host_name);
      exit(-1);
   }
   
   memcpy((char*)&remote.sin_addr, (char*)hp->h_addr, hp->h_length);

   // get the port used on the remote side and store
   remote.sin_port= htons(atoi(port));

   if(connect(socket_num, (struct sockaddr*)&remote, sizeof(struct sockaddr_in)) < 0)
   {
      perror("connect call");
      exit(-1);
   }

   return socket_num;
}

void initNormalHeader(NormalHeader *header, u_int *seq_num, u_short length, u_char flag)
{
  header->sequence_number = htons(++*seq_num);
  //header->sequence_number = (*seq_num)++;
   header->packet_length = htons(sizeof(NormalHeader) + length);
   //printf("length is %hu\n", header->packet_length);
   header->flag = flag;
}

int send_message_to_handle(u_char *client_handle, char *cmd, int socket_num, u_int *seq_num, u_char flag)
{
   Message *message = malloc(sizeof(Message));
   u_char dest_size = 0;
   u_char *handle_name_dest = malloc(sizeof(255));
   u_char send_size = strlen((char*)client_handle);
   u_char text[MAX_LEN_MSG];
   u_short msg_length;
   u_short data_length = 0;

   if (flag == FLAG_M)
   {
      dest_size = parse_target_handle(cmd, handle_name_dest);
      msg_length = get_message(cmd + dest_size, text);
      
      //printf("this is text %s\n", text);
      //printf("this is text length %d\n", msg_length);
      memcpy(message->text_message, &dest_size, sizeof(u_char));
      
      data_length += sizeof(u_char);
      memcpy(message->text_message +  data_length, handle_name_dest, dest_size);
      data_length += dest_size;
   }
   else if (flag == FLAG_B)
   {
      //printf("this is cmd %s\n", cmd);
      msg_length = get_message(cmd - 1, text);
      //printf("this is text length %d\n", msg_length);
   }
   

      memcpy(message->text_message +  data_length, &send_size, sizeof(u_char));
      data_length += sizeof(u_char);
      memcpy(message->text_message + data_length, client_handle, send_size);
      data_length += send_size;
      memcpy(message->text_message +  data_length, text, msg_length);
      data_length += msg_length;

   initNormalHeader(&message->header, seq_num, data_length, flag);
   //printf("this is normalHeader %hu\n", message->header.packet_length);
   //printf("this is message %s\n", message->text_message);
   return send(socket_num, message, ntohs(message->header.packet_length), 0);
 
}


int send_normal_header_only(int socket_num, u_int *seq_num, u_char flag)
{
   NormalHeader *header = malloc(sizeof(NormalHeader)); //might not need check later
   // change other fuction to return a normal header and combine these functions together
   //header->sequence_number = htons(*seq_num++);
   //header->packet_length = sizeof(NormalHeader);
   //header->flag = flag;
   initNormalHeader(header, seq_num, sizeof(NormalHeader), flag);
   return send(socket_num, header, ntohs(header->packet_length), 0);

}

void get_cmd(char *input, u_char *client_handle, u_int *seq_num, int socket_num) 
{
   int send_len = 0;
   int sent = 0;
   int in_len = 0;
   input[send_len] = getchar();

   while (input[send_len] != ' ' && input[send_len] != '\n' && send_len < CMD_SKIP)
   {
      send_len++;
      input[send_len] = getchar();
   }
   //printf("this is command %s\n", input);
   //printf("lowering the letter %c\n", tolower(*++input));
   if (tolower(*++input) == 'm')
   {
      in_len = get_input(input);
      //printf("input is %s\n", input);
      if(in_len ==0)
      {
         printf("Error, no handle given\n");
         
      }
      else
         sent =  send_message_to_handle(client_handle, input, socket_num, seq_num, FLAG_M);
      //printf("String sent: %s \n", input);
      //printf("Amount of data sent is: %d\n", sent);

   }
   else if(tolower(*input) == 'b')
   {
      //printf("input is %s\n", input);
      in_len = get_input(input);
      //printf("this is in_len %d\n", in_len);
      //printf("input is %s\n", input);
      sent =  send_message_to_handle(client_handle, input, socket_num, seq_num, FLAG_B);
      //printf("String sent: %s \n", input);
      //printf("Amount of data sent is: %d\n", sent);

   }
   else if(tolower(*input) == 'l')
   {

      sent = send_normal_header_only(socket_num, seq_num, FLAG_L);


   }
   else if(tolower(*input) == 'e')
   {
      //input[send_len] = '\n';
      sent = send_normal_header_only(socket_num, seq_num, FLAG_E);
   }

   else
   {
      //needs fix
      //in_len = get_input(input);
      printf("Invalid Command\n");
      printf("$: ");
      fflush(stdout);
   }

   if(sent < 0)
   {
      perror("send call");
      exit(-1);
   }

}

void send_flag_1(int socket_num, u_int *seq_num, u_char *client_handle)
{
   int sent = 0;
   u_short data_length = 0;
   Message *message = malloc(sizeof(Message));
   u_char send_size = strlen((char*)client_handle);
   memcpy(message->text_message, &send_size, sizeof(u_char));
   data_length += sizeof(u_char);
   memcpy(message->text_message + data_length, client_handle, send_size);
   data_length += send_size;
   //printf("data_length is %d\n", data_length);
   initNormalHeader(&message->header, seq_num, data_length, FLAG_1);
   //printf("this is first send seq number %d\n", ntohs(message->header.sequence_number));
   sent = send(socket_num, message, ntohs(message->header.packet_length), 0);
   
   if(sent < 0)
   {
      perror("send call");
      exit(-1);
   }
   printf("$: ");
   fflush(stdout);
   
}

void authenticate_connection(int socket_num, u_char *client_handle)
{
   //printf("da hello\n");
   int message_len = 0;
   int flag = 0;
   Message *message = malloc(sizeof(Message));
   while (!flag)
   {
      if ((message_len = recv(socket_num, message, MAX_LEN_MSG, 0)) < 0)
      {
         perror("recv call");
         exit(-1);
      }
      if (message->header.flag == 2)
      {
         flag = 1;
      }
      else if (message->header.flag == 3)
      {
         flag = -1;
      }
      else //wrong flags
      {
         flag = 0;
      }
   }
   if (flag == -1)
   {
      printf("Handle already in use: %s\n", client_handle);
      close(socket_num);
      exit(1);
   }


}

void parse_broadcast(Message *message)
{
   int message_len = ntohs(message->header.packet_length) - sizeof(NormalHeader) - sizeof(u_char);
   u_char *parsed_message = malloc(MAX_LEN_MSG);
   u_char handle_len = 0;
   u_char *handle_name = malloc(sizeof(255));
   int offset = 0;
   memcpy(&handle_len, message->text_message, sizeof(u_char));
   offset += sizeof(u_char);
   message_len -= handle_len;
   memcpy(handle_name, message->text_message + offset, handle_len);
   offset += handle_len;
   memcpy(parsed_message, message->text_message + offset, message_len);
   printf ("\n%s: %s\n", handle_name, parsed_message);
      printf("$: ");
      fflush(stdout);
}

void parse_message(Message *message)
{
   int message_len = ntohs(message->header.packet_length) - sizeof(NormalHeader) - sizeof(u_char);
   u_char dest_len = 0;
   u_char *dest_name = malloc(sizeof(255));
   u_char sender_len = 0;
   u_char *sender_name = malloc(sizeof(255));
   u_char *parsed_message = malloc(MAX_LEN_MSG);
   int offset = 0;
   memcpy(&dest_len, message->text_message, sizeof(u_char));
   offset += sizeof(u_char);
   memcpy(dest_name, message->text_message + offset, dest_len);
   offset += dest_len;
   message_len -= dest_len;
   memcpy(&sender_len, message->text_message + offset, sizeof(u_char));
   offset += sizeof(u_char);
   message_len -= sizeof(u_char);
   memcpy(sender_name, message->text_message + offset, sender_len);
   offset += sender_len;
   message_len -= sender_len;
   memcpy(parsed_message, message->text_message + offset, message_len);
   //printf("this is seq number.. should be 3, i got %d\n", message->header.sequence_number);
   printf("\n%s: %s \n", sender_name, parsed_message);
   printf("$: ");
   fflush(stdout);
}
void error_client(Message *message)
{
   u_char handle_len = 0;
   u_char *handle_name = malloc(sizeof(255));
   int offset = 0;
   memcpy(&handle_len, message->text_message, sizeof(u_char));
   offset += sizeof(u_char);
   memcpy(handle_name, message->text_message + offset, handle_len);
   //printf("GOT A FLAG_7 \n\n");
   printf("Client with handle %s does not exist\n", handle_name);
   printf("$: ");
   fflush(stdout);

}

void parse_num_clients(Message *message, u_int *num_clients)
{
   memcpy(num_clients, message->text_message, sizeof(u_int));
}

void parse_handle_table(Message * message, u_int *num_clients, int socket_num)
{
   int i;
   int message_len = 0;
   Message *new_message;
   u_char handle_len = 0;
   printf("%d handles\n", ntohl(*num_clients));
   
   for (i =0; i < ntohl(*num_clients); i++)
   {
      new_message = malloc(sizeof(Message));
      memcpy(&handle_len, message->text_message + message_len, sizeof(u_char));
      message_len += sizeof(u_char);
      memcpy(new_message->text_message, message->text_message + message_len, handle_len);
      message_len += handle_len;
      printf("Handles: %s\n", new_message->text_message);
      free(new_message);

   }
 

      /*
      if ((message_len = recv(socket_num, message, MAX_LEN_MSG, 0)) < 0)
      {
         perror("recv call");
         exit(-1);
      }
      */
      //printf("fk im stuck\n");
      
      //printf("%s \n", message->text_message + 1);
   
}
void select_server(int socket_num, char *input, u_char *client_handle, u_int *seq_num, u_int *num_clients)
{
   int error, message_len = 0;
   fd_set fdvar;
   
   struct timeval timeout;
   timeout.tv_sec = 1;
   timeout.tv_usec = 0;
   //u_int *num_clients = malloc(sizeof(num_clients));
   Message *message = malloc(sizeof(Message));
   FD_ZERO(&fdvar);
   FD_SET(0, &fdvar);
   FD_SET(socket_num, &fdvar);
   //printf("this is socket_num %d\n", socket_num);

   error = select(socket_num + 1, (fd_set *) &fdvar, (fd_set *) 0, (fd_set *) 0, NULL);
   //printf("never got here\n");

   if (error < 0)
   {
      perror("select call");
      exit(-1);
   }
   
   if (FD_ISSET(socket_num, &fdvar))
   {

      if ((message_len = recv(socket_num, message, MAX_LEN_MSG, 0)) < 0)
      {
         perror("recv call");
         exit(-1);
      }

      else if (message_len ==0)
      {
         printf("Server Terminated\n");
         close(socket_num);
         exit(1);
      }
      else if(message_len > MAX_LEN_MSG)
      {
         printf("Message is %d bytes, this is too long.\
          Message truncated to 32kbytes.\n", message_len);
      }

      if (message->header.flag == 4)
      {
         //printf("%s\n", message->text_message);
         parse_broadcast(message);
      }
      if (message->header.flag == 5)
      {
         parse_message(message);  
      }
      if (message->header.flag == 6)
      {
         //printf("client was in the handle!\n");
      }
      if (message->header.flag == 7)
      {
         error_client(message);
      }
      if (message->header.flag == 9)
      {
         //close(socket_num);
         printf("\n");
         exit(1);
      }
      if (message->header.flag == 11)
      {

         parse_num_clients(message, num_clients);
      }
      if (message->header.flag == 12)
      {
         FD_CLR(0, &fdvar);
         parse_handle_table(message, num_clients, socket_num);
         printf("$: ");
         fflush(stdout);

      }


   }
   //printf("wat da\n");
   if (FD_ISSET(0, &fdvar))
   {
      printf("$: ");
      fflush(stdout);
      get_cmd(input, client_handle, seq_num, socket_num);
   }
}

int main(int argc, char * argv[])
{
   int socket_num;         //socket descriptor
   char *send_buf = (char *) malloc(MAX_LEN_MSG);//data buffer
   u_char *client_handle = malloc(sizeof(255));
   u_int *seq_num = malloc(sizeof(u_int));
   u_int *num_clients = malloc(sizeof(u_int));
   *seq_num = 0, *num_clients = 0;
   set_client_handle(argc, argv, client_handle);
   socket_num= tcp_send_setup(argv[2], argv[3]);
   send_flag_1(socket_num, seq_num, client_handle);
   authenticate_connection(socket_num, client_handle);
   while(1)
   {
      select_server(socket_num, send_buf, client_handle, seq_num, num_clients);
   }
}