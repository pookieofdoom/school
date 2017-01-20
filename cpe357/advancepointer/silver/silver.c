#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DIM1 6
#define DIM2 8
#define NAME_LEN 20

#define qsort NOT_ALLOWED


typedef struct Name {
   char first[NAME_LEN+1];
   char last[NAME_LEN+1];
} Name;

// Support functions NameLess, NameGreater, DblLess, and StrLess

int  NameLess(void *a, void *b) {
   
   Name *c = a, *d = b;
   int ret = strcmp(c->last, d->last);
  
   return ret <0 || strcmp(c->first, d->first)   <0 && ret ==0;
  
   
}
int NameGreater(void *a, void*b) {


   Name *c = a, *d = b;
    int ret = strcmp(c->last, d->last);
    return ret >0 || strcmp(c->first, d->first)   >0 &&ret ==0;  
   

   
}


int DblLess (void *a, void *b) {
   
   return *(double*)a< *(double*)b ;

}

int StrLess (void *a, void *b) {

   return strcmp(*(char**)a,*(char**)b) <0 ;
   
}

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
   
   
}





int main() {
   Name names[DIM1] = {{"John", "Smith"}, {"Jane", "Smith"}, {"Bill", "Jones"},
      {"Sue", "Johnson"}, {"Susan", "Johnson"}, {"Jim", "Taylor"}
   };
   double vals[DIM2] = {1.1, -2.2, 3.3, -4.2, 5.5, -6.6, 7.7, -8.8};
   char *words[DIM2]
    = {"alpha", "beta", "gamma", "delta", "epsilon", "pi", "phi", "omega"};
   int i;
   
   GenInsertSort(names, DIM1, sizeof(Name), NameLess);
   for (i = 0; i < DIM1; i++)
      printf("%s %s\n", names[i].first, names[i].last);
	 
   GenInsertSort(names, DIM1, sizeof(Name), NameGreater);   
   for (i = 0; i < DIM1; i++)
      printf("%s %s\n", names[i].first, names[i].last);

   GenInsertSort(vals, DIM2, sizeof(double), DblLess);
   for (i = 0; i < DIM2; i++)
      printf("%f ", vals[i]);
   printf("\n");
   
   GenInsertSort(words, DIM2, sizeof(char *), StrLess);
   for (i = 0; i < DIM2; i++)
      printf("%s ", words[i]);
   printf("\n");

   return 0;
}
