#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#define MAX_SIZE 60
#define GRANULARITY 0.5

#ifndef CYCLICEXE_H
    #define CYCLICEXE_H

    void getAperiodic(char *fName1);
    void getSporadic(char *fName2);
    void getPS(char *fName3);

    int numOfFramesCE;
    int bestFSpossibleCE;
    float utilizationCE;

    int nA;
    int nS;
    int nPS;
    typedef struct TaskA
    {
    	int id;
        float arrival;
        float execTime;
        float remTime;
        float remTimeAux;
        float remTimeAuxA;
        int scheduleInFrame;//will have to use +1 then check by doing -1
        float startSchTime;
        float endSchTime;//final end time will be stored finally
        int flagStartSchTime;
        int flagEndSchTime;
        float finalST;
        float finalET;
        float respTime;
        float waitTime;

        float actualET;
    }taskA;
    taskA tA[MAX_SIZE];
    int aA[MAX_SIZE];//sort aperiodic tasks in increasing order by AT
    taskA pri_queue_tA[MAX_SIZE];
    int frontA,rearA;
    taskA pri_queue_tAaux[MAX_SIZE];
    int frontAaux,rearAaux;
    taskA pri_queue_tA_sched[MAX_SIZE];
    int frontA_sched,rearA_sched;
    float avgRespTimeA;
    float avgWaitTimeA;

    typedef struct TaskS
    {
        int id;
        //int jobNo;
        float arrival;
        //float period;
        float execTime;
        float deadline;//absolute
        float remTime;
        float remTimeAux;
        float remTimeAuxS;
        int scheduleInFrame;//
        float startSchTime;
        float endSchTime;
        int flagStartSchTime;
        int flagEndSchTime;
        float finalST;
        float finalET;

        float respTime;
        float waitTime;

        float actualET;
        int flagAT;
        int totJobs;
    }taskS;
    taskS tS[MAX_SIZE];
    int aS[MAX_SIZE];
    taskS pri_queue_tS[MAX_SIZE];//queue obtained after performing acceptance test-sorted by arrival time
    int frontS,rearS;
    taskS pri_queue_tSaux[MAX_SIZE];//queue obtained after performing acceptance test-sorted by arrival time
    int frontSaux,rearSaux;
    taskS pri_queue_tS_sched[MAX_SIZE];//queue obtained after performing edf and scheduling
    int frontS_sched,rearS_sched;
    int acceptanceTestSporadic(taskS tc);
    float avgRespTimeS;
    float avgWaitTimeS;

    typedef struct TaskJobPS
    {
        int taskNo;
        int jobNo;
        float arrival;
        float execTime;
        int scheduleInFrame;//
        float startSchTime;
        float endSchTime;
        int flag;

        float absRespTimeJitter;
        float relRespTimeJitter;

        float respTime;
        float waitTime;

        float actualET;
    }TaskJobPS;    

    typedef struct TaskPS
    {
        int id;
        int jobID;
        float execTime;
        struct TaskJobPS taskJobPS[MAX_SIZE];
        int index;
        int flag;//to check if array position of this task id is filled or not

        float maxRespTime;
        float minRespTime;
        float avgRespTime;
        float maxWaitTime;
        float minWaitTime;
        float avgWaitTime;

        float msRtPS[MAX_SIZE];
        float msWtPS[MAX_SIZE];
        //int job;
        int totJobs;
    }taskPS;
    taskPS tPS[MAX_SIZE];
    taskPS tPSScheduled[MAX_SIZE];
    int tPSindex;
    float maxRespTimePS;
    float minRespTimePS;
    float avgRespTimePS;
    float maxWaitTimePS;
    float minWaitTimePS;
    float avgWaitTimePS;

    typedef struct FrameCE
    {
        int id;
        float startTime;
        float endTime;
        float currentFrameTime;
        float currentFrameTimeS;
        struct TaskPS tasksInFramePS[MAX_SIZE];
        struct TaskS tasksSinFramePS[MAX_SIZE];
        struct TaskA tasksAinFramePS[MAX_SIZE];
        int flag;
        int index;//will count number of tasks
        int flagIdle;
        int indexTasksSinFramePS;
        int indexTasksAinFramePS;
        int whichTask;

        int taskLoc;

        float slack;
        float slackAux;
        float slackS;
        //int frameTasks;
    }frameCE;
    frameCE fCE[MAX_SIZE];
    frameCE fCEScheduled[MAX_SIZE];
    frameCE fCEScheduledRelax[MAX_SIZE];
    //int taskJobArrayCurr;
    float currTotSlack;
    int numOfCS;

    float currentTimeCE;
    float hyperPeriodCE;
#endif
