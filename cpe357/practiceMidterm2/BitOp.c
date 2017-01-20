//Replace a section of an integer
//Take in 2 numbers, want to take the first N number of bits from second number and mask it to beginning of first number.
// one liner

#include <stdio.h>
void ReplaceBits(int *trg, int src, int numBits) {

   *trg = *trg & (~0 << numBits) | src  &~(~0<<numBits);
  

}

int main() {

int target =255;
int source = 100;

int numBits = 5;

int a = ~(~0 <<numBits);
ReplaceBits(&target, source, numBits);
printf("%X\n", target);
printf("%X\n", a);

return 0;
}