#include <stdio.h>
#include <string.h>

#define SECS_PER_HOUR 3600
#define SECS_PER_MIN 60
typedef struct
{
	char name[20];
	double distance;
	int prSec;
	int count;
} Run;


void secsToHMS(int totalSecs, int *h, int *m, int *s);
void findRun(Run r[], int numRuns, char name[], int *index);
void writeFile(Run r[], int numRuns);
void displayRuns(Run r[], int numRuns);
void addRun(Run r[], int *numRuns);


int main(void)
{
   Run runs[30];
	char x=0;
	int i =0;
   FILE *fp;
   fp = fopen("run.data", "r");
	
	while (feof (fp) == 0)
	{
		fscanf(fp,"%s %lf %d %d\n", runs[i].name, &runs[i].distance, &runs[i].prSec, &runs[i].count);
		i++;
		
	}
	
	displayRuns(runs, i);
	
	while (x!= 'q')
	{
		printf("(a)dd run or (q)uit: ");
		scanf(" %c", &x);
   
		if (x == 'q')
		{
			printf("\nHappy trails!\n");
		
		}
		if (x == 'a')
		{
			addRun(runs, &i);
			
		}
	}
	
	fclose(fp);
	

   return 0;
}

void secsToHMS(int totalSecs, int *h, int *m, int *s)
{
   *h = totalSecs/SECS_PER_HOUR;
	totalSecs = totalSecs % SECS_PER_HOUR;
	*m = totalSecs/SECS_PER_MIN;
	totalSecs = totalSecs % SECS_PER_MIN;
	*s = totalSecs;
}

void displayRuns(Run r[], int numRuns)
{
	int i,hour, minute, second;
	int pace, ph,pm,ps;
	printf("\nRun Report:\n");
	printf("\nName                 Distance   PR       Pace    Count\n");
	printf("------------------------------------------------------\n");
	for(i=0; i<numRuns; i++)
	{
		pace = r[i].prSec/r[i].distance;
		secsToHMS(r[i].prSec,&hour,&minute,&second);
		secsToHMS(pace,&ph,&pm,&ps);
		printf("%-22s %7.2f  %d:%02d:%02d %3d:%02d %7d\n", r[i].name, r[i].distance, hour,minute,second, pm,ps, r[i].count); 
	}
}

void findRun(Run runs[], int numRuns, char name[], int *index)
{
   int i;

   *index = -1;

   for (i=0; i<numRuns && *index==-1; i++)
      if (!strcmp(name, runs[i].name))
         *index = i;
}

void writeFile(Run runs[], int numRuns)
{
   FILE *fp = NULL;
   int i = 0;

   fp = fopen("run.data", "w");

   for (i = 0; i<numRuns; i++) {
      fprintf(fp, "%s %.2f %d %d\n", runs[i].name, runs[i].distance,
       runs[i].prSec, runs[i].count);
   }
   fclose(fp);
}

void addRun(Run r[], int *numRuns)
{
	char name[20];
	int i, seconds;
	double distance;
	int hour, minute;
	printf("\nRun Name: ");
	scanf("%s", name);
	findRun(r, *numRuns, name, &i);
	if(i!=-1)
	{
		printf("Time (hh mm ss): ");
		scanf("%d %d %d", &hour, &minute, &seconds);
		seconds = hour * SECS_PER_HOUR + minute * SECS_PER_MIN + seconds;
		if(r[i].prSec > seconds)
		{
			r[i].prSec = seconds;
			
		}
		r[i].count +=1;
	}
	else
	{
		
		strcpy(r[*numRuns].name, name);
		printf("Distance in Miles: ");
		scanf("%lf", &distance);
		r[*numRuns].distance = distance;
		printf("Time (hh mm ss): ");
		scanf("%d %d %d", &hour, &minute, &seconds);
		seconds = hour * SECS_PER_HOUR+ minute * SECS_PER_MIN + seconds;
		r[*numRuns].prSec = seconds;
		r[*numRuns].count = 1;
		*numRuns = *numRuns +1;
	}
	writeFile(r, *numRuns);
	displayRuns(r, *numRuns);
		
}
