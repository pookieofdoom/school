#include <stdio.h>
#include <string.h>

typedef struct {
   int field1;
   int field2;
} RandomStruct;

void swap(void *one, void *two, int size) {
   char *data = one, *dataTwo = two;
   char temp[100];
   memmove(temp, two, size);
   memmove(two, one, size);
   memmove(one, temp, size);

}

int main() {
   RandomStruct a;
   RandomStruct b;

   scanf("%d", &a.field1);
   scanf("%d", &a.field2);

   scanf("%d", &b.field1);
   scanf("%d", &b.field2);

   printf("%d %d\n", a.field1, a.field2);
   printf("%d %d\n", b.field1, b.field2);

   swap(&a, &b, sizeof(RandomStruct));

   printf("%d %d\n", a.field1, a.field2);
   printf("%d %d\n", b.field1, b.field2);

return 0;
}