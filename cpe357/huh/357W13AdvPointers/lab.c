/*Following the spirit of the general qsort C library function, implement a GenInsertSort function that does an insertion sort on an array of any type, given the pointer to the array, number of elements, element size, and a comparison function pointer. Fill in comparison functions as called from the main example.

For the files below, please obey the following rules:
For file GenInsertSort.c:
   For entry space 1: a full programThe code must have complexity no higher than 90 per the standard complexity rules.
Meeting this bar will get you 50% credit.   For entry space 2: just one functionThe code must have complexity no higher than 90 per the standard complexity rules.
Meeting this bar will get you 50% credit.
Enter code for GenInsertSort.c*/

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

int NameGreater(void* first, void* second)
{
   char *s1 = ((Name*)second)->last;
	char *s2 = ((Name*)first)->last;
	
	return StrLess(&s1, &s2);
}


int NameLess(void* first, void* second)
{
	Name *s2 = (Name*)second;
	Name *s1 = (Name*)first;
	
	int val = strcmp((*s1).last, (*s2).last);
	return !val ? strcmp((*s1).first, (*s2).first) : val;
		
}

int DblLess(void* first, void* second)
{
	return *(double*)first < *(double*)second ? -1:1;
}

int StrLess(void* first, void* second)
{
	return strcmp( (*(char**)first), (*(char**)second) );
}


// Function GenInsertSort
void GenInsertSort(void* vals, int size, int structSize, int fp(void*, void*))
{
   //direct copy from lmq
   // void InsertSort(int vals[], int size) {
   //   int ndx, insNdx;
   //   int toInsert;
   //
   //   for (ndx = 1; ndx < size; ndx++) {
   //      toInsert = vals[ndx];
   //      insNdx = ndx;
   //      while (insNdx > 0 && toInsert <= vals[insNdx-1]) {
   //         insNdx--;
   //    }
   //    vals[insNdx] = toInsert;
   //  }
   
	int ndx, insNdx;
	void *toInsert = malloc(structSize);
	
	for ( ndx =1; ndx < size; )
	{
		insNdx = ndx;
		memcpy(toInsert, vals + ndx++ * structSize, structSize);
		while (insNdx && fp(toInsert, vals + insNdx * structSize - structSize) <= 0)
		{
			memcpy(vals + insNdx-- * structSize, vals + insNdx * structSize - structSize, structSize);
		}
		memcpy(vals + insNdx * structSize, toInsert, structSize);
	}
}


void main() {
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
}

