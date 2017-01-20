/******************************************************************************
* tcp_server.c
*
* CPE 464 - Program 1
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

#include "networks.h"

#define TABLE_SIZE 20
#define FREE 0

typedef struct __attribute__((packed)) 
{
   int socket_num;
   u_char handle_len;
   u_char handle[255];
} Client;


/* This function sets the server socket.  It lets the system
   determine the port number.  The function returns the server
   socket number and prints the port number to the screen.  */

int tcp_recv_setup(int argc, char *argv[])
{
   int server_socket= 0;
   struct sockaddr_in local;      /* socket address for local side  */
   socklen_t len= sizeof(local);  /* length of local address        */
   int port = 0;
   if (argc == 2)
   {
      port = atoi(argv[1]);
   }
   else if(argc > 2)
   {
     printf("usage: %s port_number(optional) \n", argv[0]);
     exit(1);
   }

   /* create the socket  */
   server_socket= socket(AF_INET, SOCK_STREAM, 0);
   if(server_socket < 0)
   {
      perror("socket call");
      exit(1);
   }

   local.sin_family= AF_INET;         //internet family
   local.sin_addr.s_addr= INADDR_ANY; //wild card machine address
   local.sin_port= htons(port);                 //let system choose the port

   /* bind the name (address) to a port */
   if (bind(server_socket, (struct sockaddr *) &local, sizeof(local)) < 0)
   {
      perror("bind call");
      exit(-1);
   }
   
   //get the port name and print it out
   if (getsockname(server_socket, (struct sockaddr*)&local, &len) < 0)
   {
      perror("getsockname call");
      exit(-1);
   }

   printf("Server is using port %d \n", ntohs(local.sin_port));
   
   return server_socket;
}

/* This function waits for a client to ask for services.  It returns
   the socket number to service the client on.    */

void tcp_listen(int server_socket, int back_log)
{
   if (listen(server_socket, back_log) < 0)
   {
      perror("listen call");
      exit(-1);
   }
}


int check_if_handle_exist(Client client_table[], int max_table, u_char *message)
{
   int i, error = 0;

   for (i = 0; i < max_table; i++)
   {
      
      if (strcmp((char *)client_table[i].handle, (char*)(message + 1)) == 0)
      {
         error = 1;
         return error;
      }
   }
   return 0;
}

void parse_client(Client *client, Message *message)
{
   memcpy(&client->handle_len, message->text_message, sizeof(u_char) );
   memcpy(client->handle, message->text_message + sizeof(u_char), client->handle_len);
   int len = client->handle_len;
   //printing purposes.. come back to later
   client->handle[len] = '\0';
}

void initNormalHeader(NormalHeader *header, u_int *seq_num, u_short length, u_char flag)
{
   header->sequence_number = htons(++*seq_num);
   header->packet_length = htons(sizeof(NormalHeader) + length);
   header->flag = flag;
}


int send_normal_header_only(int socket_num, u_int *seq_num, u_char flag)
{
   NormalHeader *header = malloc(sizeof(NormalHeader)); //might not need check later
   initNormalHeader(header, seq_num, 0, flag);
   return send(socket_num, header, ntohs(header->packet_length), 0);

}

void print_client_table(Client client_table[], int max_table)
{
   int i;
   //printf("this is legnth of client table %d\n", num_clients);
   for (i = 0; i < max_table; i++)
   {
      if(client_table[i].socket_num != FREE)
         printf("Client[%d]: %s %d with len %d\n", i, client_table[i].handle, client_table[i].socket_num, client_table[i].handle_len);
   }
}

void free_client(Client client_table[], int max_table, int client_socket)
{
   int i;
   for (i = 0; i < max_table; i++)
   {
      if(client_table[i].socket_num == client_socket)
      {
         client_table[i].socket_num = FREE;
         client_table[i].handle[0] = FREE;
      }
   }
}

//deal with seq number
void send_broadcast(Client client_table[], int max_table, Message *message, int client_socket)
{
   int i;
   int sent = 0;

   for (i = 0; i < max_table; i++)
   {
      if (client_table[i].socket_num != FREE && client_table[i].socket_num != client_socket)
      {
         sent = send(client_table[i].socket_num, message, ntohs(message->header.packet_length), 0);
         if(sent < 0)
         {
            perror("send call");
            exit(-1);
         }
      }
   }
}

void send_message(Client client_table[], int max_table, Message *message, int client_socket)
{
   int i = 0;
   int exist = -1;
   u_char dest_len = 0;
   u_char *dest_name = malloc(sizeof(255));
   int sent = 0;
   int offset = 0;
   Message *new_message = malloc(sizeof(Message));
   memcpy(&dest_len, message->text_message, sizeof(u_char));
   offset += sizeof(u_char);
   memcpy(dest_name, message->text_message + sizeof(u_char), dest_len);
   offset += dest_len;
      //check if client exist
   for (i = 0; i < max_table; i++)
   {
      if (strcmp((char *)client_table[i].handle, (char*)(dest_name)) == 0)
      {
         exist = i;
      }
   }
   //a lot of repeated code. can be cleaned up
   if (exist != -1)
   {
      //printf("woo this is spot in table %d\n", exist);
      memcpy(new_message->text_message, &dest_len, sizeof(u_char));
      memcpy(new_message->text_message + sizeof(u_char), dest_name, dest_len);
      initNormalHeader(&new_message->header, &(message->header.sequence_number), offset, FLAG_6);
      sent = send(client_socket, new_message, ntohs(new_message->header.packet_length), 0 );
      if(sent < 0)
      {
         perror("send call");
         exit(-1);
      }
      sent = 0;
      //printf("this is seq number.. should be 4, got %d\n", ntohs(message->header.sequence_number) );
      sent = send(client_table[exist].socket_num, message, ntohs(message->header.packet_length), 0);
      if(sent < 0)
      {
         perror("send call");
         exit(-1);
      }
   }
   else
   {
      //printf("client doesnt exist\n");
      initNormalHeader(&new_message->header, &(message->header.sequence_number), offset, FLAG_7);
      memcpy(new_message->text_message, &dest_len, sizeof(u_char));
      memcpy(new_message->text_message + sizeof(u_char), dest_name, dest_len);
      sent = send(client_socket, new_message, ntohs(new_message->header.packet_length), 0);
      if(sent < 0)
      {
         perror("send call");
         exit(-1);
      }


   }
}
u_int get_num_clients(Client client_table[], int max_table)
{
   int i =0;
   int num_clients = 0;
   for (i = 0; i < max_table; i++)
   {
      if(client_table[i].socket_num != FREE)
      {
         num_clients++;
      }
   }
   return num_clients;
}

void send_flag_11(Message *message, Client client_table[], int max_table, int client_socket)
{
   Message *new_message = malloc(sizeof(Message));
   int sent = 0;
   u_int num_clients = htonl(get_num_clients(client_table, max_table));
   initNormalHeader(&new_message->header, &(message->header.sequence_number), sizeof(int), FLAG_11);
   memcpy(new_message->text_message, &num_clients, sizeof(u_int));
   sent = send(client_socket, new_message, ntohs(new_message->header.packet_length), 0 );
   if(sent < 0)
   {
      perror("send call");
      exit(-1);
   }
}

void send_flag_12(Message *message, Client client_table[], int max_table, int client_socket)
{
   int i, sent = 0;
   int data_len = 0;
   Message *new_message = malloc(sizeof(Message));
   initNormalHeader(&new_message->header, &(message->header.sequence_number), 0, FLAG_12);
   new_message->header.packet_length = htons(0);
   
   sent = send(client_socket, &new_message->header, sizeof(NormalHeader), 0);
   if(sent < 0)
   {
      perror("send call");
      exit(-1);
   }
   //printf("this is sent %d\n",sent );
   //printf("going to send tons of siht\n");
   
   for (i = 0; i < max_table; i++)
   {
      if (client_table[i].socket_num != FREE)
      {
         memcpy(new_message->text_message + data_len, &client_table[i].handle_len, sizeof(u_char));
         data_len += sizeof(u_char);
         memcpy(new_message->text_message+ data_len, client_table[i].handle, client_table[i].handle_len);
         data_len +=client_table[i].handle_len;
         //printf("this is data_len %d\n", data_len);

      }
   }
   
            sent = send(client_socket, new_message->text_message, data_len, 0);
         if(sent < 0)
         {
            perror("send call");
            exit(-1);
         }
         
   //memset(new_message->text_message + data_len, "\n", 1); 
   


   
}

void parse_message(Message *message, Client client_table[], int max_table, int client_socket, int location)
{
   int sent = 0;
   int error_flag; 
   
   message->header.sequence_number = ntohs(message->header.sequence_number);
   //printf("this is received seq number %d\n", message->header.sequence_number);
   if (message->header.flag == FLAG_1)
   {
      //printf("Flag_1 received bois\n");
      error_flag = check_if_handle_exist(client_table, max_table, message->text_message);
      if (!error_flag)
      {
         parse_client(client_table + location, message);
         print_client_table(client_table, max_table);
         sent = send_normal_header_only(client_socket, &(message->header.sequence_number), FLAG_2);
         if(sent < 0)
         {
            perror("send call");
            exit(-1);
         }
      }
      else
      {
         //remove client and close client
         //printf("sending error flag!\n");
         print_client_table(client_table, max_table);
         free_client(client_table, max_table, client_socket);
         printf("\n\n\n");
         print_client_table(client_table, max_table);
         sent = send_normal_header_only(client_socket, &(message->header.sequence_number), FLAG_3);
         if(sent < 0)
         {
            perror("send call");
            exit(-1);
         }
         close(client_socket);
      }
   }
   if (message->header.flag == FLAG_B)
   {
      //printf("NOOO\n\n");
      send_broadcast(client_table, max_table, message, client_socket);
   }
   if (message->header.flag == FLAG_M)
   {
      send_message(client_table, max_table, message, client_socket);
   }
   if (message->header.flag == FLAG_E)
   {
      //printf("received exit call\n");
      free_client(client_table, max_table, client_socket);
      sent = send_normal_header_only (client_socket, &(message->header.sequence_number), FLAG_ACK);
      if(sent < 0)
      {
         perror("send call");
      }
      close(client_socket);
   }
   if (message->header.flag == FLAG_L)
   {
      send_flag_11(message, client_table, max_table, client_socket);
      send_flag_12(message, client_table, max_table, client_socket);
   }
}



int find_max_socket_num(Client client_table[], int max_table, int max)
{
   int i;
   for (i = 0; i < max_table; i++)
   {
      if (max < client_table[i].socket_num)
      {
         max = client_table[i].socket_num;
      }
   }
   return max;
}

int check_max_table(Client **client_table, int max_table)
{
   int i;
   int count = 0;
   //Client *temp;
   
   for (i = 0; i < max_table; i++)
   {  
      if((*client_table + i)->socket_num != FREE)
      {
         count++;
      }
   }

   if (max_table-1 == count)
   {
      *client_table = realloc(*client_table, max_table *2);
      return max_table * 2;
   }
   else
   {
      return max_table;
   }
}

void select_client(Client client_table[], int max_table, Message *message, int buffer_size, int server_socket)
{
   int i, error;
   int new_socket = 0;
   int message_len= 0;     //length of the received message
   fd_set fdvar;
   int max_socket = find_max_socket_num(client_table, max_table, server_socket);

   FD_ZERO(&fdvar);
   FD_SET(server_socket, &fdvar); //need to set all of them
   //printf("this is server_socket %d\n", server_socket);
   //set the sockets that are ready 
   //check_max_table(client_table, max_table)
   for (i =0; i < max_table; i++)
   {

      if (client_table[i].socket_num > FREE)
      {
         FD_SET(client_table[i].socket_num, &fdvar);
      }
   }


   error = select(max_socket + 1, (fd_set *) &fdvar, (fd_set *) 0, (fd_set *) 0, NULL);
   if (error < 0)
   {
      perror("select call");
   }


   if(FD_ISSET(server_socket, &fdvar))
   {

      if ((new_socket= accept(server_socket, (struct sockaddr*)0, (socklen_t *)0)) < 0)
         {
            perror("accept call");
            exit(-1);
         }
         //make function call add_to array
      for (i=0; i < max_table; i++)
      {
         if(client_table[i].socket_num == FREE)
         {
            client_table[i].socket_num = new_socket;
            break;
         }
      }
   }

   for (i =0; i < max_table; i++)
   {

      if (FD_ISSET(client_table[i].socket_num, &fdvar))
      {

         if ((message_len = recv(client_table[i].socket_num, message, buffer_size, 0)) < 0)
         {
            perror("recv call");
            exit(-1);
         }
         else if (message_len == 0)
         {
            //printf("Client Exited using Ctrl C \n");
            free_client(client_table, max_table, client_table[i].socket_num);
            close(client_table[i].socket_num);
         }
         else
         {
            //printf("Message received, length: %d\n", message_len);
            //printf("Data: %s\n", message->text_message);
            parse_message(message, client_table, max_table, client_table[i].socket_num, i);
         }

      }
   }

  
            
}

int main(int argc, char *argv[])
{
   int server_socket= 0;   //socket descriptor for the server socket
   int buffer_size= MAX_LEN_MSG;  //packet size variable
   Message *message = malloc(sizeof(Message));
   int max_table = TABLE_SIZE;
   Client *client_table = calloc(max_table, sizeof(Client));
   server_socket = tcp_recv_setup(argc, argv);
   tcp_listen(server_socket, 5);
   while (1)
   {
      max_table = check_max_table(&client_table, max_table);
      select_client(client_table, max_table, message, buffer_size, server_socket);
   }
}

