#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#define MAX_SIZE 60
#define GRANULARITY 0.5

#ifndef EXECUTIVE_H
    #define EXECUTIVE_H

    typedef struct TaskJob
    {
        int taskNo;
        int jobNo;
        float arrival;
        float period;
        float execTime;
        float deadline;//absolute
        float utilization;
        float remTime;
        float slack;
        int scheduleInFrame;
        float startSchTime;
        float endSchTime;
    }TaskJob;    

    typedef struct Task
    {
        int id;
        float arrival;
        float period;
        float execTime;
        float deadline;//relative
        float utilization;
        int job;
        float nextArrival;  //next arrival
        float nextDeadline;  //next deadline
        int flagE3;
        int totJobs;
        struct TaskJob taskJob[MAX_SIZE];
        int taskSplitID;
        int numOfTaskSplits;
        int frameID;
        float execTimeAux;
        int flagSplit;
    }task;

    int taskJobArrayCurr;

    typedef struct Frame
    {
        int id;
        float startTime;
        float endTime;
        float currentFrameTime;
        float remFrameSize;
        float remFrameSizeAux;
        struct Task tasksInFrame[MAX_SIZE][MAX_SIZE];
        int flag;
        int frameTasks;
        //TaskJob jobsInFrame[MAX_SIZE];//no need as job num associated with task present in frame will come automatically
    }frame;

    int n;   //number of tasks
    task t[MAX_SIZE];
    float a,p,e,d;    //temporary variables to store while reading from file.
    float totalUtilization;
    float hyperPeriod;
    float totalET;
    float currentTime;
    int currentTask;
    int currentFrame;
    int sameSlackTasks [10];
    int newJob;
    float minPandD(float p,float d);

    int nBeforeSplitting;
    int nAfterSplitting;

    frame f[MAX_SIZE];
    float st,et;

    float maxExecT;
    int factorsHP[MAX_SIZE];
    int validfactorsHP[MAX_SIZE];
    int finalvalidfactorsHP[MAX_SIZE];
    int possibleFSs[MAX_SIZE];
    int finalpossibleFSs[MAX_SIZE];
    int bestFS;

    unsigned int factorsHPsize;
    unsigned int validfactorsHPsize;
    unsigned int finalvalidfactorsHPsize;
    unsigned int possibleFSsSize;
    unsigned int finalpossibleFSsSize;
    void getTasks(char *f_name);
    int gcd(int x, int y);
    int lcm(int x, int y);
    void findHyperPeriod(char *f_name);
    void findBestFrameSize(void);
    void findPeriodicSchedule(char *f_name);
    //float CalculateParameters(float currentTime);
    void printResult();

    int numOfFrames;
    int totalJobs;

    void jobsArriving(float currTime,int finalPosFSsizeNum);
    task pri_que[MAX_SIZE][MAX_SIZE];
    task pri_task_que[MAX_SIZE][MAX_SIZE];
    int front, rear;
    void priorityTaskReadyQueue(task tp,int finalPosFSsizeNum);
    void create();
    void insert_by_priority(task ti,int finalPosFSsizeNum);
    void delete_by_priority(task tdel,int finalPosFSsizeNum);
    void check(task tc,int finalPosFSsizeNum);
    void display_pqueue(int finalPosFSsizeNum);

    void insert_task_by_priority(task ti,int finalPosFSsizeNum);
    void delete_task_by_priority(task tdel,int finalPosFSsizeNum);
    void check_task(task tc,int finalPosFSsizeNum);
    void display_task_pqueue(int finalPosFSsizeNum);
    float obtainedFlow;
    int size,flagSchFrame;
    void displayFrameTableInFile(char *f_name,int i,int size);
    int bestPossibleFS;
    int bestNumOfFrames;

    int ar[MAX_SIZE], aux[MAX_SIZE],remFSsorted[MAX_SIZE];
    int flagET;
    void graphMapping();
    int finalpossibleFSsSizeID;

    int taskSplittedID;
    int taskSplittedFlag;

    void findFinalPeriodicSchedule();
    
#endif
