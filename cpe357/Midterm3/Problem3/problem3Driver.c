#include <stdio.h>
#include <string.h>
#include "problem3.h"

#define MAX_COMMAND_SIZE 20

/* Prototype of function used during testing and provided in an object file */
int isStack(const Stack *stack, int expectedSize);

int main() {
   char command[MAX_COMMAND_SIZE + 1] = "NOT_DONE";
   int i, count;
   double value;
   Stack *stack;
   
   while (0 != strcmp("done", command)) {
      /* Read a command */
      if (EOF == scanf("%s", command)) {
         printf("End of input, terminating...\n");
         break;
      }

      /* Process the command */
      if (0 == strcmp("newStack", command)) {
         stack = NULL;
      }
      else if (0 == strcmp("isEmpty?", command)) {
         if (isEmpty(stack))
            printf("isEmpty? TRUE\n");
         else
            printf("isEmpty? FALSE\n");
      }
      else if (0 == strcmp("push", command)) {
         scanf("%d", &count);
         printf("push %d: ", count);

         for (i = 0; i < count; i++) {
            scanf("%lf", &value);
            printf("%.2f ", value);
            push(&stack, value);
         }

         printf("\n");
      }
      else if (0 == strcmp("pop", command)) {
         scanf("%d", &count);
         printf("pop  %d: ", count);

         for (i = 0; i < count; i++)
            printf("%.2f ", pop(&stack));

         printf("\n");
      }
      else if (0 == strcmp("isStack?", command)) {
         scanf("%d", &count);

         if (isStack(stack, count))
            printf("isStack? TRUE\n");
         else
            printf("isStack? FALSE\n");
      }
      else if (0 == strcmp("checkSpace", command)) {
         scanf("%d", &count);

         if (report_space() > sizeof(Stack) * count)
            printf("checkSpace: Too much memory allocated\n");
         else if (report_space() < sizeof(Stack) * count)
            printf("checkSpace: Too little memory allocated\n");
         else
            printf("checkSpace: Expected memory allocated\n");
      }
      else if (0 != strcmp("done", command)) {
         printf("Unknown command\n");
      }
   }

   return 0;
}
