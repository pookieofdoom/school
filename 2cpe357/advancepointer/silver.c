#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "SmartAlloc.h"

#define DIM1 6
#define DIM2 8
#define NAME_LEN 20

typedef struct Name {
   char first[NAME_LEN + 1];
   char last[NAME_LEN + 1];
} Name;

// Support function for comparing two doubles, pointed to by o1 and o2
int DblLess(void *o1, void *o2) {
   

   return *(double*)o1 < *(double*)o2;

}

// Support functions NameGreater, DblGreater, NameLess, and StrLess

int NameGreater(void *a, void *b) {
   
   Name *c = a, *d = b;
   int ret = strcmp(c->last, d->last);
   return ret > 0 || strcmp (c->first, d->first) > 0 && ret == 0;

}

int DblGreater(void *a, void *b) {
   return *(double*)a > *(double*)b;
}

int NameLess(void *a, void *b) {
   Name *c = a, *d = b;
   int ret = strcmp(c->last, d->last);
   return ret < 0 || strcmp(c->first, d->first) < 0 && ret == 0;
}

int StrLess(void *a, void *b) {
   return strcmp(*(char**)a, *(char**)b) < 0;
}

// Function GenInsertSort
void GenInsertSort(void *sort, int numElements, int size, int (*comp)(void *, void *)) {

   int ndx, insNdx;
   void *temp = malloc(size);
   
  
   for(ndx=size; ndx< numElements*size; ndx+=size) {
   
         insNdx = ndx;
        
         memcpy(temp, sort+insNdx, size) ;
       
       
      while(insNdx >0 && (comp)(temp, sort + insNdx-size)) {
        
       
         memcpy(sort+insNdx, sort+insNdx-size,size);
         
         insNdx-=size;
      }
   
      memcpy(sort+insNdx, temp,size);
   }
   free(temp);
   
}


int main() {
   Name names[DIM1];
   double vals[DIM2];
   char *words[DIM2];
   int i;

   //read in names
   for (i = 0; i < DIM1; i++) {
      scanf("%s %s", names[i].first, names[i].last);
   }
   //read in doubles
   for (i = 0; i < DIM2; i++) {
      scanf("%lf", &vals[i]);
   }
   //read in words
   for (i = 0; i < DIM2; i++) {
      words[i] = malloc(NAME_LEN);
      scanf("%s", words[i]);
   }

   GenInsertSort(vals, DIM2, sizeof(double), DblLess);
   printf("\nDblLess sort:\n");
   for (i = 0; i < DIM2; i++)
      printf("%f ", vals[i]);
   
   GenInsertSort(vals, DIM2, sizeof(double), DblGreater);
   printf("\n\nDblGreater sort:\n");
   for (i = 0; i < DIM2; i++)
      printf("%f ", vals[i]);
   
   GenInsertSort(names, DIM1, sizeof(Name), NameLess);
   printf("\n\nNameLess sort:\n");
   for (i = 0; i < DIM1; i++)
      printf("%s %s  ", names[i].first, names[i].last);
	  
   GenInsertSort(names, DIM1, sizeof(Name), NameGreater);   
   printf("\n\nNameGreater sort:\n");
   for (i = 0; i < DIM1; i++)
      printf("%s %s  ", names[i].first, names[i].last);

   GenInsertSort(words, DIM2, sizeof(char *), StrLess);
   printf("\n\nStrLess sort:\n");
   for (i = 0; i < DIM2; i++)
      printf("%s ", words[i]);
   printf("\n");

   for (i = 0; i < DIM2; i++)
      free(words[i]);

   printf("Final allocated space: %ld\n", report_space());

   return 0;
}