#define COUNTER_H
#ifndef A
#define A
int counter = 0;
#endif
counter++;
#ifndef PRINT
#define PRINT 1
#else
#undef PRINT 
#endif


