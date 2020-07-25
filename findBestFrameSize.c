#include "executive.h"

void factorsOfHP(int hp)
{
int i,j;
j=0;
    /* Iterate from 1 to hp */
    for(i=1; i<=hp; i++)
    {
        /* 
         * If num is exactly divisible by i
         * Then i is a factor of hp
         */
        if(hp % i == 0)
        {
            factorsHP[j]=i;
	    j++;
        }
    }
}

void conditionE1(int hp)
{
    int i,j;
    //printf("factorsHPsize= %d\n",factorsHPsize);
    i=0;
    for(j=0;j<factorsHPsize;j++)
    {
        if(factorsHP[j]>=1&&factorsHP[j]<=hp)
        {
            validfactorsHP[i]=factorsHP[j];
            i++;
        }
    }
}

//int gcd(int x,int y)-no need to define again as has already been defined

void conditionE2()
{
    float fvn[n],b;
    int a,fvf;
    fvf=0;
    for(int i=0;i<validfactorsHPsize;i++)
    {
        for(int j=0;j<n;j++)
        {
            a=t[j].period/validfactorsHP[i];
            b=t[j].period/validfactorsHP[i];
            if((float)a-b==0)
            {
                finalvalidfactorsHP[fvf]=validfactorsHP[i];
                fvf++;
                break;
            }
        }
    }
}

void conditionE3()
{
    int e3,fs;
    fs=0;
    for(int i=0;i<finalvalidfactorsHPsize;i++)
    {
        for(int j=0;j<n;j++)
        {
            e3=2*finalvalidfactorsHP[i]-gcd(t[j].period,finalvalidfactorsHP[i]);
            if(e3<=t[j].deadline)
                t[j].flagE3=1;
        }
        for(int j=0;j<=n;j++)
        {
            if(j<n&&t[j].flagE3==1)
            {
                continue;
            }
            else if(j<n&&t[j].flagE3==0)
            {
                break;
            }
            else if(j==n)
            {
                possibleFSs[fs]=finalvalidfactorsHP[i];
                fs++;
            }
        }
        for(int j=0;j<n;j++)
            t[j].flagE3=0;
    }
}

void possibleFSsInDecOrder()
{
    int rev;
    rev=possibleFSsSize-1;
    for(int i=0;i<possibleFSsSize,rev>=0;i++)
    {
        finalpossibleFSs[i]=possibleFSs[rev];
        rev--;
    }
}

void findBestFrameSize(void)
{
    if(totalUtilization>100)
    {
        printf("\nSchedule not possible\n");
        exit(0);
    }
    factorsOfHP(hyperPeriod);
    unsigned int fHPx = sizeof(factorsHP)/sizeof(factorsHP[0]);
    //printf("fHPx=%d\n",fHPx);
    for(int i=0;i<fHPx;i++)
        if(factorsHP[i]>0)
            factorsHPsize++;
    //printf("factorsHPsize here=%d\n",factorsHPsize);

    conditionE1(hyperPeriod);
    unsigned int vfHPx = sizeof(validfactorsHP)/sizeof(validfactorsHP[0]);
    //printf("vfHPx=%d\n",vfHPx);
    for(int i=0;i<vfHPx;i++)
    if(validfactorsHP[i]>0)
    validfactorsHPsize++;
    //printf("validfactorsHPsize here=%d\n",validfactorsHPsize);

    conditionE2();
    unsigned int fvfHPx = sizeof(finalvalidfactorsHP)/sizeof(finalvalidfactorsHP[0]);
    //printf("fvfHPx=%d\n",vfHPx);
    for(int i=0;i<fvfHPx;i++)
    if(finalvalidfactorsHP[i]>0)
    finalvalidfactorsHPsize++;
    //printf("finalvalidfactorsHPsize here=%d\n",finalvalidfactorsHPsize);

    conditionE3();
    unsigned int pFSsx = sizeof(possibleFSs)/sizeof(possibleFSs[0]);
    //printf("pFSsx=%d\n",pFSsx);
    for(int i=0;i<pFSsx;i++)
    if(possibleFSs[i]>0)
    possibleFSsSize++;
    printf("possibleFSsSize here=%d\n",possibleFSsSize);

    possibleFSsInDecOrder();
    finalpossibleFSsSize=possibleFSsSize;

    // printf("max ET: %f \n",maxExecT);
    // for(int j=0;j<factorsHPsize;j++)
    // printf("factorsOfHP at %d %d \n",j,factorsHP[j]);
    // for(int j=0;j<validfactorsHPsize;j++)
    // printf("validfactorsHP at %d %d \n",j,validfactorsHP[j]);
    // for(int j=0;j<finalvalidfactorsHPsize;j++)
    // printf("fv[]=%d\n",finalvalidfactorsHP[j]);
    // for(int j=0;j<possibleFSsSize;j++)
    // printf("possibleFSs at %d %d \n",j,possibleFSs[j]);
    for(int j=0;j<finalpossibleFSsSize;j++)
        printf("finalpossibleFSs %d \n",finalpossibleFSs[j]);
}

