#include <stdio.h>
#include <stdlib.h>

typedef struct {
   void *v0;
   char *cp0;
} SomeStruct;

void FreeAll(SomeStruct *data) {
SomeStruct *temp, *old;
old = data[0].v0;
free(data[0].cp0);
temp = data[1].v0;
printf("sup");
free(data[1].cp0);
old->v0 = old;
printf("hi");
free(old->cp0);
printf("sup2");
old = temp->v0;
free(temp);
temp = old->v0;
free(old);
temp->v0 = temp;
free(temp->v0);

   
   
}   
      
      


   


int main() {
   SomeStruct data[3];
   SomeStruct *curStruct;
   SomeStruct *tempStruct;

   int i0 = 10;
   char *cp0 = malloc(16);
   char c = '\0';

   data[0].v0 = &data[1];
   data[0].cp0 = malloc(16);

   curStruct = data[1].v0 = malloc(sizeof(SomeStruct));
   curStruct->cp0 = cp0;
   curStruct = curStruct->v0 = malloc(sizeof(SomeStruct));
   curStruct->cp0 = cp0;
   curStruct = curStruct->v0 = malloc(sizeof(SomeStruct));
   curStruct->v0 = curStruct;
   curStruct->cp0 = malloc(sizeof(int));

   curStruct = data[2].v0 = malloc(sizeof(SomeStruct));
   curStruct->v0 = tempStruct;
   curStruct->cp0 = &c;
   
   data[2].cp0 = malloc(10);

   FreeAll(data);

   

   return 0;
}
