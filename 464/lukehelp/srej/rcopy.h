#ifndef RCOPY_H
#define RCOPY_H

typedef enum {false, true} bool;

//Enum for the different states the client transition between
typedef enum {
  FILENAME, SEND_OPEN, SEND_CLOSED, SENT_LAST, DONE
} STATE;

typedef struct node {
  uint8_t *buffer;
  int32_t seqNum;
  int32_t len;
  struct node *next;
} node;

/* Function prototypes */
void checkArgs(int argc, char *argv[]);
void checkFilename(char *filname);
void manageLoop(char *argv[]);
STATE filenameState(char *fname, int32_t bufSize);
STATE sendFileOpen(int *bottom, int *uEdge);
void manageResponse(int seqNum, int *bottom, int *uEdge, int flag);
STATE manageSend();

node *getWindowNode(int seqNum);
STATE sendFileClosed(int *bottom, int *uEdge);
STATE sentLastData(int *bottom);
bool getDataFromFile(int *len);

void addtoWindowBuffer(uint8_t *data, int32_t seqNum, int len);
void removefromWindowBuffer();

#endif

