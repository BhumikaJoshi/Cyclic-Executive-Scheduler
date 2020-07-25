#include "executive.h"   

void getTasks(char *fName)
{
  FILE *fp=fopen(fName,"r"); //file name taken from the command line
  if (fp == NULL)
  {
    printf("Cannot open file \n");
    exit(1);
  }
  fscanf(fp,"%d[^\n]",&n);    //number of tasks
  nBeforeSplitting=n;
  nAfterSplitting=n;//initializing
  char ch;
  int i;
  n=0;
  ch = getc(fp);
  while (ch != EOF)
  {
      //Count whenever new line is encountered
      if (ch == '\n')
      {
          n = n + 1;
      }
      //take next character from file.
      ch = getc(fp);
  }

  printf("\nfinal n=%d",n);
  fseek(fp, 0, SEEK_SET);
  for(i=0;i<n;i++)
  {
     fscanf(fp,"%f %f %f %f[^\n]",&a,&p,&e,&d);    //Reading from the input file
     t[i].id=i;
     t[i].arrival=a;
     t[i].period=p;    
     t[i].execTime=e;  
     t[i].deadline=d;
     t[i].execTimeAux=e;
     t[i].numOfTaskSplits=0;
     t[i].flagSplit=0;
  }
  fclose(fp);

  for(i=0;i<n;i++)
  {
      printf("\n%f %f %f %f",t[i].arrival,t[i].period,t[i].execTime,t[i].deadline);
  }
}
