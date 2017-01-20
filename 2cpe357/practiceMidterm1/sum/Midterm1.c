double sum(double *array, int size) {
   double sum = 0;
   while(size--) {
      sum += *array++;
   }
      
   return sum;
   
   
}