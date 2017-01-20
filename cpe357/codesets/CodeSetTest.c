
#include <stdio.h>
#include "SmartAlloc.h"
#include "CodeSet.h"

int main() {
   char command;
   void *cs[3];  // Array of three void pointers
   int idx, ndx, numCodes, val, set, depth;
   unsigned long space, add;
   Code code;
   
  while (EOF != scanf(" %c", &command)) {
      printf("%c \n", command);
      switch (command) {
      case 'C': // create new codeSet     C <set> <maxCodes>
         scanf("%d%d", &set, &numCodes);
         cs[set] = CreateCodeSet(numCodes);
         printf("Current space: %d\n", report_space());
         //printf("Set %d initialized\n", set);
         printf("Current space: %d\n", report_space());
         printf("HIIII\n");
         break;
       case 'N': // add new code           N <set> <value>
      
         scanf("%d%d", &set, &val);
       
         printf("New code in set %d at index %d\n", set, NewCode(cs[set], val));
         
         
         break;
         
      case 'E': // extend existing code   E <set> <codeIndex>
         scanf("%d%d", &set, &idx);
         printf("Added extended code %d\n", ExtendCode(cs[set], idx));
        
         
         break;
       
      case 'S': // set suffix             S <set> <codeIndex> <suffix>
         scanf("%d%d%d", &set, &idx, &val);
         SetSuffix(cs[set], idx, val);
         break;
     
      case 'G': // get code               G <set> <codeIndex>
         scanf("%d%d", &set, &idx);
         
         code = GetCode(cs[set], idx);
         printf("Code %d in set %d has value: ", idx, set);
         ndx = 0;
       
         while(ndx < code.size){
            printf("%d ", *(code.data+ndx));
            ndx++;
         }
         printf("\n");
            
         
 
        
         break;
      case 'F':
          scanf("%d%d", &set, &idx);
          FreeCode(cs[set], idx);
          
         break;
        
      case 'R': // Report current space
         printf("Current space: %d\n", report_space());
         break;
      case 'B': // Grab current space used
         space = report_space();
         break;
      case '+': // Adds an amount to the current used space.
         scanf("%lu", &add);
         space += add;
        
         break;      
      case '-': // Decreases an amount to the current used space.
         scanf("%lu", &add);
         space -= add;
         break;
      case 'L': // Call limit space
        
         limit_space(space);
         break;
      case 'V': // Verify Space has not changed
         if (space != report_space()) {
            printf("Space Differs by %d\n", report_space() - space);
         }
         break;
         
      case 'Y':
         scanf("%d%d", &set, &depth);
         for (idx = 0; idx < depth; idx++) {
            FreeCode(cs[set], idx);
         }
         break;
      case 'X': // Add many codes in prefix order  X <set> <depth>
         scanf("%d%d", &set, &depth);
         ndx = NewCode(cs[set], 'X');
         while (--depth) {
            ndx = ExtendCode(cs[set], ndx);
            SetSuffix(cs[set], ndx, 'X');
         }
         break;
      case 'Z': // Fun GetCode chain  Z <set> <depth>
         scanf("%d%d", &set, &depth);
         for (idx = 0; idx < depth; idx++) {
            GetCode(cs[set], idx);
         }
         break;
      case 'D': // Destroy existing code set  D <set>
         scanf("%d", &set);
         DestroyCodeSet(cs[set]);
         printf("Set %d destroyed\n", set);
         break; 
      default:
         break;
      }
   }

   return 0;
}
