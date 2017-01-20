#include <stdio.h>
#include <stdarg.h>

/* Accept a format string comprised only of the letters c d i s and f for char,
 * double, int, short, and float, respectively.  Accept as many variadic
 * parameters after that format string as there are letters in the string.
 * Assume the actual parameters in the main were of the indicated types 
 * (though passed variadically).  Total the parameters and return the total
 * (use the ASCII value of any char parameter. */
double addEm(char *format, ...) {
   double total = 0 ;
   va_list params;
   va_start(params, format);
   while(*format) {
      switch(*format++) {
      case 'c':
        
         total += va_arg(params, int);
         
         break;
      case 'd':
         total+=va_arg(params,double);
         break;
      case 'i':
         
         total+=va_arg(params,int);
         break;
      case 's':
        
         total+=va_arg(params, int);
         break;
      case 'f':
         total+=va_arg(params,double);
        
         break;
      default:
        break;
      }
   }

   return total;
  

}


int main() {
   double dVal;
   float fVal;
   int iVal;
   short sVal;
   char cVal;
  
   scanf("%d %hd %c %f %lf", &iVal, &sVal, &cVal, &fVal, &dVal);
  
   printf("Total is %0.2f or %0.2f if you add 42\n",
    addEm("fdisc", fVal, dVal, iVal, sVal, cVal),
  addEm("siccddf", sVal, iVal, cVal, 42, dVal, 0.0, fVal));

   return 0;
}
