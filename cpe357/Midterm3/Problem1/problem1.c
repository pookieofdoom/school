


int getBit(unsigned int from, int at) {
   
   int value;
   value = (from  &  1<<at)>>at;
   return value;

}
