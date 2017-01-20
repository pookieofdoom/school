#ifndef SERVER_H
#define SERVER_H

typedef enum {false, true} bool;

//Enum for the states that the server transitions between
typedef enum {
  FILENAME, RECV_DATA, SEND_ACK, DONE
} STATE;

/* Function Prototypes */
void waitForClients(char *argv[]);
void checkArgs(int argc, char *argv[]);
void processClient(uint8_t *buf,
		   int32_t recvLen, Connection *client);
STATE processFilename(Connection *client, uint8_t *buf, int32_t recvLen,
		      int32_t *dataFile, int32_t *bufSize, int32_t *windowSize);
STATE processReceive(Connection *client, int32_t bufSize,
		     int *expNum, bool *quiet, int winSize);

#endif
