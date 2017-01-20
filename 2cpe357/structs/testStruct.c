#include <stdio.h>


typedef struct {

   int x;
   double y;

} Test;

int main () {

   Test testStruct = { 5, 6.0};
   Test *testPointer = &testStruct;
   
   Test temp = *testPointer;
   
   printf("testStruct is %d and %f\n", testStruct.x, testStruct.y);
   printf("test pointer is %d and %f\n", testPointer->x, testPointer->y); 
   printf("temp is %d and %f\n", temp.x, temp.y);


}
