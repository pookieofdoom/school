#include <stdio.h>
#include <string.h>

#define A_FIELDS 5
#define B_FIELDS 6

typedef struct {
   int offset;  
   int size;   
} Field;

typedef struct {
   char c0;
   double d0;
   short s0;
   char c1;
   short s1;
} StructA;

typedef struct {
   short s0;
   char c0;
   double d0;
   char c1;
   char c2;
   double d1;
} StructB;

void Compress(const void *structA, char *buf, Field *flds, int fldCount) {
   int fldNdx;
   Field *fld;

   for (fldNdx = 0; fldNdx < fldCount; fldNdx++) {
      fld = flds + fldNdx;
      memmove(buf, structA+fld->offset, fld->size);
      buf += fld->size;
     
   }
}

void Uncompress(const void *structA, char *buf, Field *flds, int fldCount) {
   int fldNdx;
   Field *fld;

   for (fldNdx = 0; fldNdx < fldCount; fldNdx++) {
      fld = flds + fldNdx;
      memmove(structA+fld->offset, buf, fld->size);
      
      buf+=fld->size;
   }
}






int main() {
   StructA sa1, sa2;
   StructB sb1, sb2;
   char bufA[2*sizeof(char) + 2*sizeof(short) + sizeof(double)];
   char bufB[3*sizeof(char) + sizeof(short) + 2*sizeof(double)];

   Field structAFlds[] = {{0, sizeof(char)}, {(char *)&sa1.d0 - (char *)&sa1, sizeof(double)}, {(char *)&sa1.s0 - (char *)&sa1, sizeof(short)}, {(char *)&sa1.c1 - (char *)&sa1, sizeof(char)}, {(char *)&sa1.s1 - (char *)&sa1, sizeof(short)}};
   Field structBFlds[] = {{0, sizeof(short)}, {(char *)&sb1.c0 - (char *)&sb1, sizeof(char)}, {(char *)&sb1.d0 - (char *)&sb1, sizeof(double)}, {(char *)&sb1.c1 - (char *)&sb1, sizeof(char)}, {(char *)&sb1.c2 - (char *)&sb1, sizeof(char)}, {(char *)&sb1.d1 - (char *)&sb1, sizeof(double)}};

   scanf(" %c %lf %hd %c %hd", &sa1.c0, &sa1.d0, &sa1.s0, &sa1.c1, &sa1.s1);
   scanf(" %hd %c %lf %c %c %lf", &sb1.s0, &sb1.c0, &sb1.d0, &sb1.c1, &sb1.c2, &sb1.d1);

   Compress(&sa1, bufA, structAFlds, A_FIELDS);
   Compress(&sb1, bufB, structBFlds, B_FIELDS);

   Uncompress(&sa2, bufA, structAFlds, A_FIELDS);
   Uncompress(&sb2, bufB, structBFlds, B_FIELDS);

   printf("%c %.1lf %hd %c %hd\n", sa2.c0, sa2.d0, sa2.s0, sa2.c1, sa2.s1);
   printf("%hd %c %.1lf %c %c %.1lf\n", sb2.s0, sb2.c0, sb2.d0, sb2.c1, sb2.c2, sb2.d1);

   return 0;
}