


void setBit(unsigned int *value, int at, int bitValue) {
   if(bitValue == 1) 
      *value = *value | bitValue <<at;
   else {
       
      *value = *value & ~((bitValue | 1) <<at);
   }

}
