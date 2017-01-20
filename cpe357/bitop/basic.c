#include <stdio.h>

#define NUMVALS 6
#define SIZE 5
#define MAX 31

int main() {
int vals = 0;
short curVal, idx = 0;
while(idx < NUMVALS ) {
  scanf("%hu", &curVal);
 // curVal = curVal << (SIZE*idx);
  vals |= curVal;
  vals = vals << SIZE;
  printf("%d\n", vals);
  //vals =vals<<SIZE;
   idx++;
  
} 
   
   while(idx >0) {
   //curVal >>(SIZE*idx) 
   //vals = vals >> SIZE;
   curVal =  (vals>>(SIZE*idx)) & MAX ;
   printf("%u ",curVal);
 
   idx --;
 
}

   return 0;
}
