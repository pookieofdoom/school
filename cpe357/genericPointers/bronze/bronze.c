#include <stdio.h>
#define NAME_LEN 20

typedef struct {
   char name[NAME_LEN+1];
   int id;
} Person;

typedef struct {
   char name[NAME_LEN+1];
   int id;
   double gpa;
} Student;

typedef struct {
   char name[NAME_LEN+1];
   int id;
   char advisor[NAME_LEN+1];
} GradStudent;


int SameId(void *v1, void *v2) {


   return ((Person *)v1)->id == ((Person *)v2)->id == 1; 
}


int main() {
   Person p;
   Student s;
   GradStudent g;
   
   scanf("%d%s", &p.id, &p.name);
   scanf("%d%s%lf", &s.id, &s.name, &s.gpa);
   scanf("%d%s%s", &g.id, &g.name, &g.advisor);
   
   if (SameId(&g, &p) && SameId(&g, &s) && SameId(&s, &g))
      printf("All have the same id.\n");

   return 0;
}