#include "executive.h"   

int gcd(int x,int y)
{
    if(y==0)
        return x;
    else
    {
        gcd(y,x%y);
    }
}

int lcm(int x,int y)
{
    return((x*y)/gcd(x,y));
}

float minPandD(float p,float d)
{
    if(p<d)
        return p;
    else
        return d;
}

void findHyperPeriod(char *fName)
{
    FILE *fp=fopen(fName,"w"); //file name taken from the command line
    if (fp == NULL)
    {
      printf("Cannot open file \n");
      exit(1);
    }
    hyperPeriod = t[0].period;
    int m =n;
    totalUtilization = 0;
    for(int i=0;i<n;i++)
    {
        t[i].utilization=t[i].execTime/minPandD(t[i].period,t[i].deadline);
        totalUtilization += t[i].utilization;
    }
    totalUtilization *= 100;
    m--;
    while(m>=1)
    {
        hyperPeriod = lcm(hyperPeriod,t[m].period);
        m--;
    }
    printf("\nhyperperiod=%f",hyperPeriod);
    printf("\ntotal utilization=%f",totalUtilization);
    fprintf(fp, "hyperperiod: %f\n", hyperPeriod); // write to file
    fprintf(fp, "total utilization: %f\n", totalUtilization); // write to file
    fclose(fp);
}
