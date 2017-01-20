#include <stdio.h>
#include <string.h>

#define NAME_LEN 20
#define NUM_STUDENTS 3

typedef struct {
   int id;
   char name[NAME_LEN+1];
   double gpa;
} Student;

void cloneStudent(Student *s1, Student *s2) {
   s2->id = s1->id;
   strcpy(s2->name, s1->name);
   s2->gpa = s1->gpa;
}

int IsEqual(Student *sa, Student *sb) {
   return sa->id == sb->id && sa->gpa == sb->gpa
      && strcmp(sa->name, sb->name) == 0;
}

int main() {
   Student s1 = {1, "Bob", 3.0}, s2 = {4, "Sue", 3.5};

   cloneStudent(&s1, &s2);

   if (IsEqual(&s1, &s2)) {
      printf("Successfuly cloned a student");
   }
   else {
      printf("Failed to clone a student");
   }

   return 0;
}
