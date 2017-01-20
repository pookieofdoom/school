/*
 * Luke Gnos
 * 2/24/16
 * server.c
 */

//TODOs
//set up receiving data->writing to file
//set up responding with RRs and SREJs
//set up buffering received data

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "cpe464.h"
#include "networks.h"
#include "server.h"

int32_t serverSocketNum = 0; //Socket number for the server
FILE *writeFilePtr = NULL;   //FILE pointer for the file being written to
int sequenceNumber = 1;
windowNode *windowArray;

int main(int argc, char *argv[]) {

  checkArgs(argc, argv);

  printf("errorperc: %f\n", atof(argv[1]));
  
  sendtoErr_init(atof(argv[1]), DROP_OFF, FLIP_OFF, DEBUG_ON, RSEED_ON);

  waitForClients(argv);
  
  return 0;
}

/*
 * Function that waits in an infinite loop until it receives a request packet
 * When it receives a request packet it forks off a child to manage it and returns
 *  to check for new clients
 */ 
void waitForClients(char *argv[]) {
  int32_t serverSKNum = 0, recvLen = 0;
  pid_t pid = 0;
  int status = 0;
  uint8_t buf[MAX_LEN];
  uint8_t flag;
  int32_t seqNum = 0;
  Connection client;

  //struct sockaddr_in local;
  //uint32_t len = sizeof(local);

  //Set up the server socket
  serverSKNum = udp_server(serverSocketNum);

  while (1) {
    //Check for a new request with a 1s timeout
    if (select_call(serverSKNum, 1, 0, NOT_NULL)) {
      //If a request was found, receive the packet
      recvLen = recv_buf(buf, 1000, serverSKNum, &client, &flag, &seqNum);

      //If there is no CRC error on the packet, fork off child to manage client
      if (recvLen != CRC_ERROR) {
	if ((pid = fork()) < 0) {
	  perror("fork");
	  exit(-1);
	}

	//Have child process the client, parent returns to loop
	if (pid == 0) {
	  processClient(buf, recvLen, &client);
	  exit(0);
	}
	
      } else {
	printf("Received request with CRC error, ignoring\n");
      }

      //Check for any child processes that have finished
      while (waitpid(-1, &status, WNOHANG) > 0) {
	printf("Processed wait\n");
      }
    }
  }
}

/*
 * Function that manages the flow between the different states of the server
 * When the DONE state is reached the child process will exit
 */
void processClient(uint8_t *buf,
		   int32_t recvLen, Connection *client) {
  
  STATE state = FILENAME;
  int32_t dataFile = 0;
  int32_t windowSize = 0;
  //int32_t packetLen = 0;
  //int32_t packet[MAX_LEN];
  int32_t bufSize = 0;
  //int32_t seqNum = START_SEQ_NUM;
  int expNum = 1;
  bool quiet = false;
  
  while (state != DONE) {
    switch (state) {
    case FILENAME:

      state = processFilename(client, buf, recvLen, &dataFile,
			      &bufSize, &windowSize);
      break;
    case RECV_DATA:

      printf("waiting for response on socket: %d\n", client->sk_num);
      
      if (select_call(client->sk_num, 10, 0, NOT_NULL) != 0) {
	//process response
	state = processReceive(client, bufSize, &expNum, &quiet, windowSize);
      } else {
	printf("Server timed out while waiting for client, exiting...\n");
	state = DONE;
      }
      break;

    default:
      printf("Error, in default state\n");
      state = DONE;
      break;
    }
  }
}

STATE processReceive(Connection *client, int32_t bufSize,
		     int *expNum, bool *quiet, int winSize) {
  uint8_t packet[MAX_LEN], flag;
  int32_t seqNum = 0;
  windowNode curr;
  int32_t data_len = 0;

  if ((data_len = recv_buf(packet, bufSize, client->sk_num, client,
	       &flag, &seqNum)) == CRC_ERROR) {
    printf("received a bad packet with data: %s\n", packet);

    exit(0);
    //Received a bad packet, send SREJ on that sequence number
    if (*quiet == false)
      send_buf((uint8_t *)&seqNum, 4, client, SREJ, sequenceNumber++, packet);
    return RECV_DATA;
  }
  printf("\n\n\n this is data_len %d\n", data_len);
  printf("received packet with flag: %d\n", flag);
  
  //Otherwise, no error, determine response
    if (seqNum == *expNum) { //Got expected, RR and write to file
      if (fwrite(packet, 1, data_len, writeFilePtr) != bufSize) {
	perror("fwrite");
	exit(-1);
      }
      if (*quiet == false)
	send_buf((uint8_t *)&seqNum, 3, client, RR, sequenceNumber++, packet);
      (*expNum)++;
      
    } else if (seqNum < *expNum) { //Got a lost packet resend
      //got a lost packet back from SREJ
      //write all available, send RR 
      //quiet = false
      


      
    } else if (seqNum > *expNum) {
      //store the packet
      curr = windowArray[seqNum % winSize];
      memcpy(curr.buffer, packet, bufSize);
      //send SREJ
      if (*quiet == false)
	send_buf((uint8_t *)&seqNum, 4, client, SREJ, sequenceNumber++, packet);
      *quiet = true;
      (*expNum)++;
      
    }
   else if (flag == LAST_DATA) {


  } else {
    printf("Packet with unkown flag received, discarding...\n");
  }

  return DONE;
}

/*
 * Function that manages the filename state of the server
 * Opens a new socket for this particular client, then attempts to open the 
 *  file specified in the request packet
 * If the open succeeds it sends an ACK to the client, otherwise it sends
 *  a NACK and then exits normally
 */
STATE processFilename(Connection *client, uint8_t *buf, int32_t recvLen,
		      int32_t *dataFile, int32_t *bufSize,
		      int32_t *windowSize) {

  uint8_t response[1];
  char fname[MAX_LEN];
  int32_t offset = 0;
  
  memcpy(bufSize, buf, 4);
  offset += 4;
  memcpy(windowSize, buf + offset, 4);
  offset += 4;
  memcpy(fname, buf + offset, recvLen - offset);

  if ((client->sk_num = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
      perror("filename,  open client socket");
      exit(-1);
  }

  printf("received request for file: %s, with bufSize: %d, winSize: %d on port %d\n", fname, *bufSize, *windowSize, client->sk_num);
  
  //Attempt to open the file for writing
  writeFilePtr = fopen(fname, "w");
  
  if (writeFilePtr == NULL) { //respond with a NACK
    send_buf(response, 0, client, ESTNACK, sequenceNumber++, buf);
    perror("fopen, server write");
    return DONE;
    
  } else { //respond with an ACK
    send_buf(response, 0, client, ESTACK, sequenceNumber++, buf);
    return RECV_DATA;
  }
}

/*
 * Function that checks the commandline arguments for errors
 */
void checkArgs(int argc, char *argv[]) {
  
  if (argc != 2 && argc != 3) {
    printf("Invalid input. Usage: server <errorpercent>"
	   " <portnum (optional)>\n");
    exit(-1);
  }

  if (atof(argv[1]) < 0 || atof(argv[1]) >= 1) {
    printf("Error, percentage rate needs to be between 0 and 1 and is: "
	   "%f\n", atof(argv[1]));
    exit(-1);
  }

  if (argc == 3) {
    serverSocketNum = atoi(argv[2]);
  }
}
