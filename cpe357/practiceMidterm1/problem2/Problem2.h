#ifndef PROBLEM2_H_INCLUDED
#define PROBLEM2_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
   int id;
   float gpa;
} GPARecord;

int countMatches(void *vArr, int dim, void *vVal, int vBytes);

#endif
