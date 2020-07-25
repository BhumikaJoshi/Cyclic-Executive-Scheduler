#include "cyclicexe.h"   

void getSporadic(char *fName2)
{
	int i;
    char ch2;
    float artS,exS,dl,pe;
    FILE *fp2=fopen(fName2,"r"); //sporadic tasks-file name taken from the command line
    if (fp2 == NULL)
    {
      printf("\nCannot open file : %s\n",strerror(errno));
      exit(1);
    }
    ch2 = getc(fp2);
    while (ch2 != EOF)
    {
        //Count whenever new line is encountered
        if (ch2 == '\n')
        {
            nS = nS + 1;
        }
        //take next character from file.
        ch2 = getc(fp2);
    }
    //printf("\nfinal nS=%d\n",nS);
    fseek(fp2, 0, SEEK_SET);
    for(i=0;i<nS;i++)
    {
       fscanf(fp2,"%f %f %f[^\n]",&artS,&exS,&dl);    //Reading from the input file
       tS[i].id=i;
       tS[i].arrival=artS;   
       tS[i].execTime=exS;
       tS[i].deadline=dl;
       tS[i].remTime=exS;
       tS[i].remTimeAux=exS;
       tS[i].remTimeAuxS=exS;
    }
    fclose(fp2);
}
