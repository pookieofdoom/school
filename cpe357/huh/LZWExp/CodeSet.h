/* One entry in a dictionary of codes.
 * |data| points to the sequence of bytes the code represents.
 * |size| is the sequence length.
 */
typedef struct Code {
   char *data;
   unsigned short size;
} Code;

/* Allocate, initialize, and return a CodeSet object, via void *
 * The CodeSet will have room for |numCodes| codes, though it will
 * initially be empty. */ 
void *createCodeSet(int numCodes);

/* Add a new 1-byte code to |codeSet|, returning its index, with
 * the first added code having index 0.  The new code's byte is
 * equal to |val|.  Assume (and assert if needed) that there
 * is room in the |codeSet| for a new code. */
int newCode(void *codeSet, char val);

/* Create a new code by copying the existing code at index
 * |oldCode| and extending it by one zero-valued byte.  
 * Return the new code's index.  Assume |oldCode| is a valid
 * index and that there is enough room for a new code. */
int extendCode(void *codeSet, int oldCode);

/* Set the final byte of the code at index |code| to |suffix|.  
 * This is used to override the zero-byte added by extendCode. */
void setSuffix(void *codeSet, int code, char suffix);

/* Return the code at index |code| */
Code getCode(void *codeSet, int code);

/* Free all dynamic storage associated with |codeSet| */
void destroyCodeSet(void *codeSet);
