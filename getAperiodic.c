#include "cyclicexe.h"   

void getAperiodic(char *fName1)
{
	int i;
  char ch1;
  float art,ex;
	FILE *fp1=fopen(fName1,"r"); //aperiodic tasks-file name taken from the command line
    if (fp1 == NULL)
    {
      printf("Cannot open file \n");
      exit(1);
    }
    ch1 = getc(fp1);
    while (ch1 != EOF)
    {
        //Count whenever new line is encountered
        if (ch1 == '\n')
        {
            nA = nA + 1;
        }
        //take next character from file.
        ch1 = getc(fp1);
    }
    //printf("\nfinal nA=%d\n",nA);
    fseek(fp1, 0, SEEK_SET);
    for(i=0;i<nA;i++)
    {
       fscanf(fp1,"%f %f[^\n]",&art,&ex);    //Reading from the input file
       tA[i].id=i;
       tA[i].arrival=art;   
       tA[i].execTime=ex;
       tA[i].remTime=ex;
       tA[i].remTimeAux=ex;
       tA[i].remTimeAuxA=ex;      
    }
    fclose(fp1);
}