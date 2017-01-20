#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define FLOAT 32

//struct that contains IEEE754 format for easier use
typedef struct myFloat {
   float value;
   unsigned int sign, exponent, fraction;
} myFloat;

//function that normalizs a given fraction
void normalize(myFloat *a) {
   if (a->fraction == 0)
      return;
   
   int sign = a->fraction >> (FLOAT - 1);
   int hidden = a->fraction >> (FLOAT - 2);
   
   while (sign == hidden) {
      a->fraction <<= 1;
      hidden = a->fraction >> (FLOAT - 2);
      a->exponent -= 1;
   }
}
//function that prints binary(not used)
void print_binary(float f) {
   unsigned int iNumber;
   iNumber = (unsigned int) * (unsigned int *) &f;
   int i;
   printf("IEEE 754 Binary Representation of %lf is: ", f);
   for (i=0; i<=31; i++)
   {
      if ((iNumber >> (31-i)) & 1)
         printf("1");
      else
         printf("0");
   }
   printf("\n");
}
//function that prints the sign, fraction, and exponent
//given IEEE754 formatted float
void print_value(myFloat a) {
   int i;
   float x = 0;
   
   for (i=1; i<=31; i++) {
      x = x + ((a.fraction >> (31-i)) & 1) * pow(2, -i);
   }
   printf("%f = sign: %d,  Fraction: %X(%f) with exp: %d\n", a.value, a.sign, a.fraction, x, a.exponent);

}

//function that unpacks the components of the float
myFloat unpack_ieee_754(float f) {
   myFloat retz;
   unsigned int iNumber;
   iNumber = (unsigned int) * (unsigned int *) &f;
   
   retz.value = f;
   retz.sign = iNumber >> 31;
   
   //extract exponent and + 1 since adding hidden 1
   retz.exponent = ((iNumber >> 23) & 0xff) - 126;
   
   //extract fraction and insert hidden 1
   retz.fraction = (iNumber & 0x7fffff) << 7 | 0x40000000;

  return retz;
}

//packs components into iEEE 754 float
//assmes fraction is normalized
float pack_ieee_754(int sign, int expo, int frac) {
   float f = 0;
   int i;
   float x = 0;
   unsigned int iNumber = 0;
   iNumber = (unsigned int) * (unsigned int *) &f;
   
   iNumber |= ((sign &0x1) << 31);
   //add bias to exponent
   expo += 126;
   iNumber |= ((expo & 0xff) << 23);
   
   frac = (frac & 0x3FFFFF80) >> 7;
   iNumber |= frac;

   //loop that will help print out float (to confirm packed correctly)
   for (i=1; i<=23; i++) {
      x = x + ((iNumber >> (23-i)) & 1) * pow(2, -i);
   }

   printf("packed ieee754 is: %X (%f)\n", iNumber, pow(-1, sign) *(1+x) * pow(2,expo -127));

   return iNumber;
}

//function that does addition
float single_float_add(float a, float b) {

   myFloat f_a, f_b, result;
   //unpack the floats into my struct 
   f_a = unpack_ieee_754(a);
   f_b = unpack_ieee_754(b);
   
   //scale_shift to make everything on same scale before addition
   int scale_shift = f_a.exponent - f_b.exponent;
   printf("a exp is %d and b exp is %d\n", f_a.exponent, f_b.exponent);
   if (scale_shift < 0) {
      f_a.exponent -= scale_shift;
      f_a.fraction >>= -scale_shift;
   }
   else if (scale_shift > 0) {
      f_b.exponent += scale_shift;
      f_b.fraction >>= scale_shift;
   }
   //printf("scale for a is %d and scale for b is %d\n", f_a.exponent, f_b.exponent);

   //shift everything right by 1 to compensate for overflow
   f_a.fraction >>= 1;
   f_a.exponent +=1;
   f_b.fraction >>= 1;
   f_b.exponent +=1;
   
   //complement the fraction before addition
   if (f_a.sign)
      f_a.fraction = ~(f_a.fraction) + 1;
   if (f_b.sign)
      f_b.fraction = ~(f_b.fraction) + 1;

   //integer addition of the fraction stored into result struct
   result.fraction = f_a.fraction + f_b.fraction;
   result.exponent = f_a.exponent;
   result.value = f_a.value + f_b.value;
   result.sign = result.fraction >> 31;
   //complement the answer if negative
   if (result.sign == 1) {
      result.fraction = ~(result.fraction)+ 1;
   }
   
   //finally normalize the final result
   normalize(&result);
   printf("this is sum of %f + %f: \n", a, b);
   print_value(result);
   return pack_ieee_754(result.sign, result.exponent, result.fraction);
}

//function that does subtraction (literally same as add but subtract the fractions)
float single_float_sub(float a, float b) {
   myFloat f_a, f_b, result;
   //unpack the floats into my struct
   f_a = unpack_ieee_754(a);
   f_b = unpack_ieee_754(b);
   
   //scale_shift to make sure everything is common scale
   int scale_shift = f_a.exponent - f_b.exponent;
   if (scale_shift < 0) {
      f_a.exponent -= scale_shift;
      f_a.fraction >>= -scale_shift;
   }
   else if (scale_shift > 0) {
      f_b.exponent += scale_shift;
      f_b.fraction >>= scale_shift;
   }
   //printf("\nscale for a is %d and scale for b is %d\n", f_a.exponent, f_b.exponent);

   //shift everything right by 1 to compensate for overflow
   f_a.fraction >>= 1;
   f_a.exponent +=1;
   f_b.fraction >>= 1;
   f_b.exponent +=1;
   
   //complement fraction if negative before subtraction
   if (f_a.sign)
      f_a.fraction = ~(f_a.fraction) + 1;
   if (f_b.sign)
      f_b.fraction = ~(f_b.fraction) + 1;
   
   //subtract the fractions and store into result
   result.fraction = f_a.fraction - f_b.fraction;
   result.exponent = f_a.exponent;
   result.value = f_a.value - f_b.value;
   
   result.sign = result.fraction >> 31;
   //complement result if negative
   if (result.sign == 1) {
      result.fraction = ~(result.fraction)+ 1;
   }
   
   //normalize final result
   normalize(&result);
   printf("\nthis is the difference: %f - %f \n", a,b);
   print_value(result);
   return pack_ieee_754(result.sign, result.exponent, result.fraction);
}

//floating point multiply function
float single_float_multiply(float a, float b) {
   myFloat f_a, f_b, result;
   result.fraction = 0;
   //unpack floats into struct
   f_a = unpack_ieee_754(a);
   f_b = unpack_ieee_754(b);
   
   //multiply the fraction but store into 64bit
   unsigned long long c = (unsigned long long)f_a.fraction * (unsigned long long )f_b.fraction;
   //store multiplicant into fraction by shifting 64bit result by 31
   result.fraction = c >> 31;
   //result exponent is the addition of the two
   result.exponent = f_a.exponent + f_b.exponent;
   result.value = f_a.value * f_b.value;
   //sign will depend on xor of the signs
   result.sign = f_a.sign ^ f_b.sign;

   //normalize the result
   normalize(&result);
   printf("\nthis is the multiplication: %f * %f \n", a, b);
   print_value(result);
   return pack_ieee_754(result.sign, result.exponent, result.fraction);
}


int main() {
   float x = single_float_add(-0.625, 8.5);
   float y = single_float_sub(5.15, -2);
   float z = single_float_multiply(6932.5, 523.1);
   return 0;

}
