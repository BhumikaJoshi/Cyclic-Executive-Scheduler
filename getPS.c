#include "cyclicexe.h"   

void initialize()
{
    for(int i=0;i<MAX_SIZE;i++)
    {
        tA[i].scheduleInFrame=0;
        tS[i].scheduleInFrame=0;
        tPS[i].index=0;
        tPS[i].flag=0;
        //tPS[i].job=0;
        tPS[i].totJobs=0;
        fCE[i].flag=0;
        fCE[i].index=0;
        fCE[i].flagIdle=0;
        fCE[i].slack=0;
        //fCE[i].frameTasks=0;
        for(int j=0;j<MAX_SIZE;j++)
        {
            tPS[i].taskJobPS[j].scheduleInFrame=0;
            tPS[i].taskJobPS[j].flag=0;
        }
    }
}

void getPS(char *fName3)
{
    nPS=0;
    tPSindex=0;
    initialize();
	int i;
    char ch3;
    FILE *fp3=fopen(fName3,"r"); //aperiodic tasks-file name taken from the command line
    if (fp3 == NULL)
    {
      printf("Cannot open file \n");
      exit(1);
    }

    long int pointerEOF,checkEOF;
    ch3 = getc(fp3);
    while (ch3 != EOF)
    {
        pointerEOF=ftell(fp3);
        //take next character from file.
        ch3 = getc(fp3);
    }
    //printf("\nfp3 at EOF=%ld",ftell(fp3));
    //pointerEOF++;
    fseek(fp3, 0, SEEK_SET);

    fscanf(fp3,"Number of frames: %d    Best frame size possible: %d[^\n]",&numOfFramesCE,&bestFSpossibleCE);
    hyperPeriodCE=numOfFramesCE*bestFSpossibleCE;
    // printf("\nnumOfFramesCE=%d\n",numOfFramesCE);
    // printf("\n%ld",ftell(fp3));
    //printf("\nbestFSpossibleCE=%d\n",bestFSpossibleCE);
    //printf("\n%ld",ftell(fp3));
    char frTaskIdle[10];
    int fID,tID,jID;
    float schST,schET,jAT,idleST,idleET;

    checkEOF=ftell(fp3);
    // printf("\ncheckEOF=%ld\n",checkEOF);
    // printf("\npointerEOF=%ld\n",pointerEOF);//gives index for EOF
    fscanf(fp3,"%s",frTaskIdle);
    //printf("\nbefore while %s\n",frTaskIdle);
    while(checkEOF != pointerEOF-1)
    {
        if(strcmp(frTaskIdle,"Frame")==0)
        {
            fscanf(fp3," : %d[^\n]",&fID);
            fCE[fID].id=fID;
            fCE[fID].flag=1;
            fCE[fID].startTime=bestFSpossibleCE*fID;
            fCE[fID].endTime=bestFSpossibleCE*(fID+1);
            fCE[fID].indexTasksSinFramePS=0;
            fCE[fID].indexTasksAinFramePS=0;
            //fCE[fID].totJobs=0;

        }
        else if(strcmp(frTaskIdle,"task")==0)
        {
            fscanf(fp3," : %d,job : %d    %f to %f    Arrival : %f[^\n]",&tID,&jID,&schST,&schET,&jAT);
            //these only done once
            if(tPS[tID].flag==0)
            {
                tPS[tID].id=tID;
                tPS[tID].jobID=tPS[tID].index;//gives job id
                tPS[tID].execTime=schET-schST;
                tPS[tID].flag=1;
                tPS[tID].taskJobPS[tPS[tID].index].execTime=schET-schST;
            }
            //these done each time
            tPS[tID].jobID=tPS[tID].index;
            tPS[tID].taskJobPS[tPS[tID].index].taskNo=tID;
            tPS[tID].taskJobPS[tPS[tID].index].jobNo=jID;
            tPS[tID].taskJobPS[tPS[tID].index].arrival=jAT;
            tPS[tID].taskJobPS[tPS[tID].index].execTime=schET-schST;
            tPS[tID].taskJobPS[tPS[tID].index].scheduleInFrame=fID+1;
            tPS[tID].taskJobPS[tPS[tID].index].startSchTime=schST;
            tPS[tID].taskJobPS[tPS[tID].index].endSchTime=schET;
            tPS[tID].taskJobPS[tPS[tID].index].flag=1;

            //tPS[tID].job+=1;//index will tell same thing
            tPS[tID].totJobs+=1;
            
            fCE[fID].whichTask=1;
            //at which pos task is stored in frame struct array
            fCE[fID].taskLoc=fCE[fID].index;

            //put in frame-add after adding all parameters to tasks and its job above
            fCE[fID].tasksInFramePS[fCE[fID].index]=tPS[tID];//retrieve jobNo from it to find which job of this task
            //is present in this frame

            tPS[tID].index++;//do at last only
            fCE[fID].index++;//will also give num of tasks in the frame
        }
        else if(strcmp(frTaskIdle,"IDLE")==0)
        {
            fscanf(fp3," :              %f to %f[^\n]",&idleST,&idleET);
            fCE[fID].currentFrameTime=idleST;
            fCE[fID].currentFrameTimeS=idleST;
            fCE[fID].flagIdle=1;
            fCE[fID].slack=idleET-idleST;
            fCE[fID].slackS=idleET-idleST;
            fCE[fID].slackAux=idleET-idleST;
        }
        checkEOF=ftell(fp3);
        //printf("\ncheckEOF=%ld\n",checkEOF);

        if(checkEOF!=pointerEOF-1)
            fscanf(fp3,"%s",frTaskIdle);
    }
    
    //counting total number of periodic jobs
    for(int j=0;j<MAX_SIZE;j++)
    {
        if(tPS[j].flag==1)
            nPS++;
    }
    fclose(fp3);
}