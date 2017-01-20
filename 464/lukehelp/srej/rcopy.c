/*

 * Luke Gnos
 * 2/21/16

 * rcopy
 * to run: rcopy <localfile> <remotefile> <bufsize>
         <error%> <windowsize> <machine> <port>
 */ 

//TODO
//test with working send
//test with error send

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cpe464.h"
#include "networks.h"
#include "rcopy.h"

FILE *localFile;
Connection server;
int32_t sequenceNumber = 1;
int32_t windowSize = 0;
int32_t bufferSize = 0;
node *winBufHead;
node *winBufTail;

int main(int argc, char *argv[]) {

  checkArgs(argc, argv);
  
  sendtoErr_init(atof(argv[4]), DROP_OFF, FLIP_OFF, DEBUG_ON, RSEED_ON);

  checkFilename(argv[1]);

  manageLoop(argv);

  return 0;
}

/*
 * Function that manages the loop for rcopy, transitioning between the
 *  the different states
 */
void manageLoop(char *argv[]) {
  STATE state = FILENAME;
  int selectCount = 1, lastCount = 1;
  int bottom = 1;
  int upperEdge = bottom + windowSize;
  
  while (state != DONE) {
    switch (state) {
    case FILENAME:
      //Get a new socket every time 
      if (udp_client_setup(argv[6], atoi(argv[7]), &server) < 0)
	exit(-1);

      state = filenameState(argv[2], bufferSize);

      if (state == FILENAME)
	close(server.sk_num);

      if (selectCount++ > 9) {
	printf("Server unreachable, client terminating\n");
	state = DONE;
      }      
      break;

    case SEND_OPEN:
      selectCount = 0;

      if (sequenceNumber != upperEdge) {
	state = sendFileOpen(&bottom, &upperEdge);
      } else {
	state = SEND_CLOSED;
      }
      break;

    case SEND_CLOSED:
      printf("in send closed\n");
      exit(-1);
      if (++selectCount < 10 ) {
	state = sendFileClosed(&bottom, &upperEdge);
      } else {
	state = DONE;
      }
      
      break;

    case SENT_LAST:

      printf("Got to send last\n");
      exit(-1);
      
      if (++lastCount < 10) {
	state = sentLastData(&bottom);
      } else {
	state = DONE;
      }
      
      break;

    case FINISHED:
      printf("Success! File transferred to remote server.\n");
      state = DONE;
      break;

      //case DONE: //shouldnt actually enter done state due to loop setup

    default:
      printf("Error, in default state, exiting...\n");
      exit(-1);
      break;
    }
  }

  printf("Exiting...\n");
}

/*
 * Function that waits for the acknowledgement for the final data packet
 * If the 1s select call times out, it resends the last data packet again
 * If it receives a SREJ it resends that packet.
 * If it receives a RR for the last data packet, program finishes, if the RR 
 *  is for a lower packet, it does nothing with the RR
 */
STATE sentLastData(int *bottom) {
  node *data;
  uint8_t packet[MAX_LEN], flag;
  int32_t seqNum = 0, resSeqNum = 0;

  if (select_call(server.sk_num, 1, 0, NOT_NULL) == 0) {
    //No response, send last data again
    data = getWindowNode(sequenceNumber);
    send_buf(data->buffer, data->len, &server, LAST_DATA,
	     data->seqNum, packet);
    return SENT_LAST;
    
  } else {
    //Response received, check for errors
    if (recv_buf(packet, bufferSize, server.sk_num,
		 &server, &flag, &seqNum) == CRC_ERROR) {
      //If error, ignore packet and return to select
      return SENT_LAST;
    }
    //Otherwise no error, check type of response
    memcpy(&resSeqNum, packet, 4); //Get the sequence number sent in the data
    
    if (flag == RR) { // Got a RR
      //Check if RR is for the last packet
      if (resSeqNum == sequenceNumber) {
	return FINISHED;
      } //else don't care, ignore RR
	
    } else if (flag == SREJ) { //Got a SREJ
      //get the packet from the windowArray, send again
      data = getWindowNode(resSeqNum);
      send_buf(data->buffer, data->len, &server, DATA,
	       data->seqNum, packet);
    } else {
      printf("Packet with unknown flag received, discarding...\n");
    }
  
    return SENT_LAST;
  }
}

/*
 * Function that manages sending the file when the window is closed
 * Checks for a server response on a select call with a 1s timeout
 * If a response was found, it processes it then returns to sending
 * If a timeout occurs, it sends the lowest frame in the window and returns 
 *  to the 1s select
 */
STATE sendFileClosed(int *bottom, int *uEdge) {
  node *data;
  uint8_t packet[MAX_LEN];
  uint8_t flag = 0;
  int32_t seqNum = 0, resSeqNum = 0;

  if (select_call(server.sk_num, 1, 0, NOT_NULL) == 0) {
    //No response available = Timeout, send lowest frame in window
    data = winBufHead;
    send_buf(data->buffer, data->len, &server, DATA, data->seqNum, packet);
    return SEND_CLOSED;
      
  } else {
    //Response available, check for error
    if (recv_buf(packet, bufferSize, server.sk_num,
		 &server, &flag, &seqNum) == CRC_ERROR) {
      //If error, ignore packet and return to select
      return SEND_CLOSED;
    }
    //Otherwise, no error, determine type of response
    memcpy(&resSeqNum, packet, 4); //Get the sequence number sent in the data

    manageResponse(resSeqNum, bottom, uEdge, flag);

    return SEND_OPEN;
  }
}

/*
 * Function that manages sending the file while the window is open
 * Sends either a flag = 1 or flag = 9 (last data) packet if no response is
 *  ready from the server, otherwise it processes the response first.
 */
STATE sendFileOpen(int *bottom, int *uEdge) {
  uint8_t flag = 0;
  int32_t seqNum = 0, resSeqNum = 0;
  uint8_t packet[MAX_LEN];
  
  if (select_call(server.sk_num, 0, 0, NOT_NULL) == 0) {
    //No Response available, get data from file
    return manageSend();
    
  } else {
    //Response available, check for error
    if (recv_buf(packet, bufferSize, server.sk_num,
		 &server, &flag, &seqNum) == CRC_ERROR) {
      //If error, ignore packet and return to select
      return SEND_OPEN;
    }
    //Otherwise no error, check type of response
    memcpy(&resSeqNum, packet, 4); //Get the sequence number sent in the data
    printf("got a response with type: %d, for %d \n", flag, resSeqNum);

    manageResponse(resSeqNum, bottom, uEdge, flag);
    
    return SEND_OPEN;
  }
}

void manageResponse(int seqNum, int *bottom, int *uEdge, int flag) {
  node *data;
  
  if (flag == RR) {
    *bottom = seqNum;
    *uEdge = *bottom + windowSize;
    //Add removing stuff from buffer*******************************
    
  } else if (flag == SREJ) {
    //Get the seqNum packet then resend it
    data = getWindowNode(seqNum);
    //send_buf(node->buffer, node->len, &server, DATA, seqNum, packet); 
  } else {
    printf("Packet with unknown flag received, discarding...\n");
  }
}

/*
 * Function that reads data from the file and then sends it to the server
 *  with the correct flag
 */
STATE manageSend() {
  bool isLast = false;
  int len = 0;
  node *data;
  uint8_t packet[MAX_LEN];
  //uint8_t toSend[MAX_LEN];
  
  //Read data from file and add to the window buffer
  isLast = getDataFromFile(&len);
  data = getWindowNode(sequenceNumber);
  
  printf("Sending data with len: %d\n", len);
  
  if (isLast == true) { //Reached EOF in the file
    send_buf(data->buffer, data->len, &server, LAST_DATA, data->seqNum, packet);
    exit(0);
    return SENT_LAST;
  } else { //No EOF, just send the data
    send_buf(data->buffer, len, &server, DATA, sequenceNumber++, packet);
    return SEND_OPEN;
  }  
}

/*
 * Linked-List helper function that adds the newest frame of the window
 *  to the end of the list.
 */
void addtoWindowBuffer(uint8_t *data, int32_t seqNum, int len) {
  node *new;

  //Malloc space for new node and its buffer
  if ((new = malloc(sizeof(node))) == NULL) {
    perror("malloc");
    exit(-1);
  }

  if ((new->buffer = malloc(len)) == NULL) {
    perror("malloc");
    exit(-1);
  }

  //copy over from data into buffer and seqNum/len
  memcpy(new->buffer, data, len);
  new->len = len;
  new->seqNum = seqNum;
  new->next = NULL;
  
  //put new node into list
  if (winBufHead == NULL) {
    winBufHead = winBufTail = new;
    
  } else {
    winBufTail->next = new;
    winBufTail = new;    
  }
}

/*
 * Function that removes the head of the linked list, freeing its components
 */
void removefromWindowBuffer() {
  node *temp;

  if (winBufHead == NULL) {
    printf("Detected attempt to remove buffer from empty list\n");
    exit(-1);
  }

  temp = winBufHead->next;

  free(winBufHead->buffer);
  free(winBufHead);

  winBufHead = temp;
}

/*
 * Linked list helper function that searches through the list for the
 *  node with the sequence number 'seqNum', and returning a pointer to it
 */
node *getWindowNode(int seqNum) {
  node *temp;

  if (winBufHead == NULL) {
    printf("Detected attempt to get data from empty window buffer\n");
    exit(-1);
  }

  temp = winBufHead;

  while (temp != NULL) {
    if (temp->seqNum == seqNum) {
      break;
    }

    temp = temp->next;
  }

  if (temp == NULL) {
    printf("Could not find data with seqNum %d in buffer\n", seqNum);
    exit(-1);
  }

  return temp;
}

/*
 * Function that gets the next chunk of data from the local file
 * Returns a bool for if the data just read was the last in the file.
 * Places the number of bytes read into the len parameter
 */
bool getDataFromFile(int *len) {
  bool toRet = false;
  uint8_t buffer[MAX_LEN];
  
  if ((*len = fread(buffer, 1, bufferSize, localFile)) != bufferSize) {
    if (ferror(localFile)) {
      perror("fread");
      exit(-1);
    }
    printf("at end of file, len = %d\n", *len);
    //If no error, has to be eof reached
    toRet = true;
  }

  addtoWindowBuffer(buffer, sequenceNumber, *len); 
  
  return toRet;
}

/*
 * Function that sends the request to the server and manages the select call
    waiting for a response
 */
STATE filenameState(char *fname, int32_t bufSize) {
  uint8_t packet[MAX_LEN];
  uint8_t buf[MAX_LEN];
  uint8_t flag = 0;
  int32_t fnameLen = strlen(fname) + 1;
  int32_t recvCheck = 0;
  int32_t seqNum = 0;
  int32_t offset = 0;

  //Place buffer size
  memcpy(buf, &bufSize, 4);
  offset += 4;
  //Place window size
  memcpy(buf + offset, &windowSize, 4);
  offset += 4;
  //place filename
  memcpy(buf + offset, fname, fnameLen);
  offset += fnameLen;
  
  //Send the request
  send_buf(buf, offset, &server, ESTAB, sequenceNumber++, packet);

  //Check for a response from the server with a 1s timeout
  if (select_call(server.sk_num, 1, 0, NOT_NULL) == 1) {
    //Get the response packet
    recvCheck = recv_buf(packet, bufferSize, server.sk_num,
			 &server, &flag, &seqNum);

    //If the response has errors, discard it, send request again
    if (recvCheck == CRC_ERROR) {
      printf("Received data with bad CRC\n");
      return FILENAME;
    }

    //If the response was a NACK, go to end state
    if (flag == ESTNACK) {
      printf("File %s could not be created on server\n", fname);
      return DONE;
    } 
    
    //If the response was an ACK, set seqNum and go to sendfile state
    sequenceNumber = START_SEQ_NUM;
    return SEND_OPEN;
  }

  //If no response from server, check again
  return FILENAME;
}

/*
 * Function that checks if the local filename is available to open
 */
void checkFilename(char *filename) {
  
  localFile = fopen(filename, "r");

  if (localFile == NULL) {
    perror("rcopy, fopen");
    exit(-1);
  }
}

/*
 * Funtion that checks the commandline arguments for errors
 */
void checkArgs(int argc, char *argv[]) {

  if (argc != 8) {
    printf("Usage: %s <localfile> <remotefile> <bufsize>"
	   "  <errorpercent> <windowsize> <machine> <port>\n", argv[0]);
    exit(-1);
  }

  if (strlen(argv[1]) > 1000) {
    printf("Local filename needs to be less than 1000 characters"
	   " and is currently: %d\n", (int)strlen(argv[1]));
    exit(-1);
  }

  if (strlen(argv[2]) > 1000) {
    printf("Remote filename needs to be less than 1000 characters"
	   " and is currently: %d\n", (int)strlen(argv[2]));
    exit(-1);
  }

  if (atoi(argv[3]) < 400 || atoi(argv[3]) > 1400) {
    printf("Buffer size needs to be between 400 and 1400 and is: "
	   "%d\n", atoi(argv[3]));
    exit(-1);
  } else {
    bufferSize = atoi(argv[3]);
  }

  if (atof(argv[4]) < 0 || atof(argv[4]) >= 1) {
      printf("Error percentage rate needs to be between 0 and 1 and is: "
	     " %f\n", atof(argv[4]));
      exit(-1);
  }

  if (atoi(argv[5]) < 1 || atoi(argv[5]) > 100) {
	printf("Window size needs to be between 1 and 100 and is: "
	       " %d\n", atoi(argv[5]));
	exit(-1);
  } else {
    windowSize = atoi(argv[5]);
  }

}
