#include "cyclicexe.h"

void mergeA(int arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    /* create temp arrays */
    int L[n1], R[n2]; 
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = l; // Initial index of merged subarray 
    while (i < n1 && j < n2) 
    { 
        if (tA[L[i]].arrival <= tA[R[j]].arrival) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else if(tA[L[i]].arrival > tA[R[j]].arrival)
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
    /* Copy the remaining elements of L[], if there 
       are any */
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
    /* Copy the remaining elements of R[], if there 
       are any */
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 
  
/* l is for left index and r is right index of the 
   sub-array of arr to be sorted */
void mergeSortA(int arr[], int l, int r) 
{ 
    if (l < r) 
    { 
        // Same as (l+r)/2, but avoids overflow for 
        // large l and h 
        int m = l+(r-l)/2; 
        // Sort first and second halves 
        mergeSortA(arr, l, m); 
        mergeSortA(arr, m+1, r); 
        mergeA(arr, l, m, r); 
    } 
}

void sortAperiodic()
{
    for(int k=0;k<nA;k++)
    {
        aA[k]=k;
    }
    mergeSortA(aA, 0, nA - 1);
    for(int k=0;k<nA;k++)
        printf("\naA[%d]=%d",k,aA[k]);
}

void mergeS(int arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
    int L[n1], R[n2]; 
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
    i = 0; 
    j = 0;
    k = l;
    while (i < n1 && j < n2) 
    { 
        if (tS[L[i]].arrival <= tS[R[j]].arrival) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else if(tS[L[i]].arrival > tS[R[j]].arrival)
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 

void mergeSortS(int arr[], int l, int r) 
{ 
    if (l < r) 
    { 
        int m = l+(r-l)/2;  
        mergeSortS(arr, l, m); 
        mergeSortS(arr, m+1, r); 
        mergeS(arr, l, m, r); 
    } 
}

void sortSporadic()//if arrive at same time then lets just give priority to least id-merge sort does
{
    for(int k=0;k<nS;k++)
    {
        aS[k]=k;
    }
    mergeSortS(aS, 0, nS - 1);
    for(int k=0;k<nS;k++)
        printf("\naS[%d]=%d",k,aS[k]);
}
void createA()
{
    frontA = rearA = -1;
}
void createA_sched()
{
    frontA_sched = rearA_sched = -1;
}
void createS()
{
    frontS = rearS = -1;
}
void createS_sched()
{
    frontS_sched = rearS_sched = -1;
}
/* Function to insert value into priority queue */
void insert_by_priorityA(taskA ti)
{
    if (rearA >= MAX_SIZE - 1)
    {
        printf("\nQueue overflow no more elements can be inserted");
        return;
    }
    if ((frontA == -1) && (rearA == -1))
    {
        frontA++;
        rearA++;
        pri_queue_tA[rearA] = ti;
        return;
    }    
    else
    {
        rearA++;
        pri_queue_tA[rearA] = ti;
    }
}

int acceptanceTestSporadic(taskS tc)
{
    int i,j;
    float execForInAT,slackAT;
    slackAT=0;
    for (i = 0; i < numOfFramesCE; i++)
    {
        printf("\nfCE[%d].slack=%f",i,fCE[i].slackS);
        if(tS[tc.id].remTimeAuxS>0)
        {
            if(tc.arrival<=fCE[i].startTime && fCE[i].slackS>0)
            {
                if(tc.deadline<=fCE[i].endTime && tc.deadline>fCE[i].currentFrameTimeS)
                {
                    execForInAT=tc.deadline-fCE[i].currentFrameTimeS;
                    if(tS[tc.id].remTimeAuxS<=execForInAT)//included <=slack
                    {
                        //slackAT+=
                        fCE[i].currentFrameTimeS+=tS[tc.id].remTimeAuxS;
                        fCE[i].slackS-=tS[tc.id].remTimeAuxS;
                        tS[tc.id].remTimeAuxS-=tS[tc.id].remTimeAuxS;
                        printf("\nbefore return 1");
                        return 1;
                    }
                    else
                    {
                        printf("\nbefore return 0");
                        return 0;
                    }
                }
                else if(tc.deadline>fCE[i].endTime)
                {
                    if(tc.remTimeAuxS<=fCE[i].slackS)
                    {
                        //slackAT
                        fCE[i].currentFrameTimeS+=tS[tc.id].remTimeAuxS;
                        fCE[i].slackS-=tS[tc.id].remTimeAuxS;//else sum slack and compare with et
                        tS[tc.id].remTimeAuxS-=tS[tc.id].remTimeAuxS;
                        printf("\nbefore 2nd return 1");
                        return 1;
                    }
                    else
                    {
                        //slackAT
                        fCE[i].currentFrameTimeS+=fCE[i].slackS;
                        tS[tc.id].remTimeAuxS-=fCE[i].slackS;
                        fCE[i].slackS-=fCE[i].slackS;
                    }
                }
            }
        }
    }
    //return;
    if(tc.remTimeAuxS==0)// or tc.remTimeAuxS<=slackAT
    {
        printf("\nbefore 3rd return 1");
        return 1;
    }
    else
    {
        printf("\nbefore 2nd return 0");
        return 0;
    }
}

void insert_by_priorityS(taskS ti)
{
    int i;
    if (rearS >= MAX_SIZE - 1)
    {
        printf("\nQueue overflow no more elements can be inserted");
        return;
    }
    i=acceptanceTestSporadic(ti);
    if(i==1)
    {
        if ((frontS == -1) && (rearS == -1))
        {
            
            frontS++;
            rearS++;
            
            pri_queue_tS[rearS] = ti;
            tS[ti.id].flagAT=1;
            //return;
        }   
        else
        {
            rearS++;
            pri_queue_tS[rearS] = ti;
            tS[ti.id].flagAT=1;
        }
    }
}
 
/* Function to delete an element from queue *///see while scheduling
// void delete_by_priorityA(task tdel)
// {
//     int i;
 
//     if ((frontA==-1) && (rearA==-1))
//     {
//         printf("\nQueue is empty no elements to delete");
//         return;
//     }
 
//     for (i = 0; i <= rearA; i++)
//     {
//         if (tdel. == pri_que[i].id)
//         {
//             for (; i < rearA; i++)
//             {
//                 pri_que[finalPosFSsizeNum][i] = pri_que[finalPosFSsizeNum][i + 1];
//             }
 
//         //pri_que[finalPosFSsizeNum][i] = NULL;
//         rearA--;
 
//         if (rearA == -1) 
//             frontA = -1;
//         return;
//         }
//     }
//     printf("\ntask %d not found in queue to delete", tdel.id);
// }
 
/* Function to display queue elements */
void display_pqueueA()
{
    if ((frontA == -1) && (rearA == -1))
    {
        //printf("\nQueue is empty");
        return;
    }
 	printf("\ndisplay queue:\n");
    for (; frontA <= rearA; frontA++)
    {
        printf("taskA %d \n", pri_queue_tA[frontA].id);
        printf("rearAaux=%d taskA aux %d \n", rearAaux,pri_queue_tAaux[frontA].id);
    }
 
    frontA = 0;
}

void display_pqueueS()
{
    if ((frontS == -1) && (rearS == -1))
    {
        //printf("\nQueue is empty");
        return;
    }
    printf("\ndisplay queue:\n");
    for (; frontS <= rearS; frontS++)
    {
        printf("taskS %d \n", pri_queue_tS[frontS].id);
        printf("taskS aux %d \n", pri_queue_tSaux[frontS].id);
    }
    frontS = 0;
}

void queueA()
{
    //priority queue formation
    createA();
    for(int i=0;i<nA;i++)
        insert_by_priorityA(tA[i]);
    frontAaux=frontA;
    rearAaux=rearA;
    for(int i=0;i<=rearA;i++)
        pri_queue_tAaux[i] = pri_queue_tA[i];
    display_pqueueA();
}

void queueS()//formed by performing acceptanceTestSporadic
{
    //priority queue formation
    createS();
    for(int i=0;i<nS;i++)
        insert_by_priorityS(tS[aS[i]]);
    frontSaux=frontS;
    rearSaux=rearS;
    for(int i=0;i<=rearS;i++)
        pri_queue_tSaux[i] = pri_queue_tS[i];
    display_pqueueS();
}

void mergeInc(float arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
    float L[n1], R[n2]; 
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
    i = 0; 
    j = 0;  
    k = l;  
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++;
    } 
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 

void mergeSortInc(float arr[], int l, int r)
{
     if (l < r) 
    { 
        int m = l+(r-l)/2; 
        // Sort first and second halves 
        mergeSortInc(arr, l, m); 
        mergeSortInc(arr, m+1, r); 
        mergeInc(arr, l, m, r); 
    } 
}

void serverPS(int k)
{
    fCEScheduled[k].id=fCE[k].id;
    fCEScheduled[k].flag=fCE[k].flag;
    fCEScheduled[k].startTime=fCE[k].startTime;
    fCEScheduled[k].endTime=fCE[k].endTime;
    fCEScheduled[k].index=fCE[k].index;
    fCEScheduled[k].currentFrameTime=fCE[k].currentFrameTime;
    fCEScheduled[k].currentFrameTimeS=fCE[k].currentFrameTimeS;
    fCEScheduled[k].flagIdle=fCE[k].flagIdle;
    fCEScheduled[k].slack=fCE[k].slack;
    fCEScheduled[k].slackS=fCE[k].slackS;
    fCEScheduled[k].slackAux=fCE[k].slackAux;
    int x,y,tidO;
    x=0;
    while(x<fCE[k].index)
    {
        //fCEScheduled[k].tasksInFramePS[x].id//to know which task
        //fCEScheduled[k].tasksInFramePS[x].jobID//to know which job
        //no need to initialize tasks and jobs again here to find rt and wt as this is original one, just calc with original
        y=fCE[k].tasksInFramePS[x].jobID;
        //these done inside frame only
        fCE[k].tasksInFramePS[x].taskJobPS[y].respTime=fCE[k].tasksInFramePS[x].taskJobPS[y].endSchTime-
        fCE[k].tasksInFramePS[x].taskJobPS[y].arrival;
        fCE[k].tasksInFramePS[x].taskJobPS[y].waitTime=fCE[k].tasksInFramePS[x].taskJobPS[y].endSchTime-
        fCE[k].tasksInFramePS[x].taskJobPS[y].arrival-fCE[k].tasksInFramePS[x].taskJobPS[y].execTime;

        //for changing task parameters itself
        tidO=fCE[k].tasksInFramePS[x].id;
        printf("\nt=%d,j=%d",tidO,y);
        tPS[tidO].taskJobPS[y].respTime=tPS[tidO].taskJobPS[y].endSchTime-
        tPS[tidO].taskJobPS[y].arrival;
        tPS[tidO].taskJobPS[y].waitTime=tPS[tidO].taskJobPS[y].endSchTime-
        tPS[tidO].taskJobPS[y].arrival-tPS[tidO].taskJobPS[y].execTime;

        //add task to frame at last
        fCEScheduled[k].tasksInFramePS[x]=fCE[k].tasksInFramePS[x];
        //fCEScheduled[k].tasksInFramePS[x].totJobs++;
        x++;
    }
}

void delete_by_prioritySaux(taskS tdel,int k)
{
    int i;
    if ((frontSaux==-1) && (rearSaux==-1))
    {
        printf("\nQueue is empty no elements to delete");
        return;
    }
    for (i = 0; i <= rearSaux; i++)
    {
        if (tdel.id == pri_queue_tSaux[i].id)
        {
            for (; i < rearSaux; i++)
            {
                pri_queue_tSaux[i] = pri_queue_tSaux[i + 1];
            }
        rearSaux--;
        if (rearSaux == -1) 
            frontSaux = -1;
        return;
        }
    }
    printf("\ntask %d not found in queue to delete", tdel.id);
}

void delete_by_priorityS_sched(taskS tdel,int k)
{
    int i;
    if ((frontS_sched==-1) && (rearS_sched==-1))
    {
        printf("\nQueue is empty no elements to delete");
        return;
    }
    for (i = 0; i <= rearS_sched; i++)
    {
        if (tdel.id == pri_queue_tS_sched[i].id)
        {
            for (; i < rearS_sched; i++)
            {
                pri_queue_tS_sched[i] = pri_queue_tS_sched[i + 1];
            }
        rearS_sched--;
        if (rearS_sched == -1) 
            frontS_sched = -1;
        return;
        }
    }
    printf("\ntask %d not found in queue to delete", tdel.id);
}

void check_taskS_sched(taskS tc,int k)
{
    int i,j,x;
    for (i = 0; i <= rearS_sched; i++)
    {
        if(tc.deadline < pri_queue_tS_sched[i].deadline)
        {
            for (j = rearS_sched + 1; j > i; j--)
            {
                pri_queue_tS_sched[j] = pri_queue_tS_sched[j - 1];
            }
            pri_queue_tS_sched[i] = tc;
            delete_by_prioritySaux(tc,k);
            return;
        }
        else if(tc.deadline >= pri_queue_tS_sched[i].deadline)
        {
            continue;
        }
    }
    if(i==rearS_sched+1)
    {
        pri_queue_tS_sched[rearS_sched+1] = tc;
        delete_by_prioritySaux(tc,k);
    }
}

void insert_by_priorityS_sched(taskS ti,int k)
{
    if(rearS_sched>=MAX_SIZE-1)
    {
        return;
    }
    if ((frontS_sched == -1) && (rearS_sched == -1))//first element to be inserted
    {
        frontS_sched++;
        rearS_sched++;
        pri_queue_tS_sched[rearS_sched] = ti;
        //delete from pri_queue_tSaux
        delete_by_prioritySaux(ti,k);
        return;
    }    
    else
        check_taskS_sched(ti,k);//check deadline-now arrival time does not matter as at frame boundary these are present
    rearS_sched++;
}

void scheduleATs(int k,taskS tc,float ctCE)
{
    //schedule from pri_queue_tS_sched within frame
    printf("\nfCEScheduled[%d].slack=%f",k,fCEScheduled[k].slack);
    while(fCEScheduled[k].currentFrameTime < (ctCE+bestFSpossibleCE))
    {
        if(tS[tc.id].remTimeAux>0 && fCEScheduled[k].slack>0)
        {        
            if(tc.deadline<=fCEScheduled[k].endTime && tc.deadline>fCEScheduled[k].currentFrameTime)
            {
                tS[tc.id].startSchTime=fCEScheduled[k].currentFrameTime;
                if(tS[tc.id].remTimeAux==tS[tc.id].execTime)//take start time then
                {
                    tS[tc.id].flagStartSchTime=1;
                    tS[tc.id].finalST=tS[tc.id].startSchTime;
                }
                fCEScheduled[k].currentFrameTime+=tS[tc.id].remTimeAux;
                tS[tc.id].endSchTime=fCEScheduled[k].currentFrameTime;
                printf("\nk=%d tS=%d j= endSchTime=%f",k,tS[tc.id].id,tS[tc.id].endSchTime);
                fCEScheduled[k].slack-=tS[tc.id].remTimeAux;
                tS[tc.id].remTimeAux-=tS[tc.id].remTimeAux;
                if(tS[tc.id].remTimeAux==0)
                {
                    tS[tc.id].flagEndSchTime=2;//take end time then
                    tS[tc.id].finalET=tS[tc.id].endSchTime;
                }
             //   printf("\nbefore return 1");
                //end tc-delete from pri_queue_tS_sched
                //also firstly add to frame
                tS[tc.id].scheduleInFrame=k+1;
                fCEScheduled[k].tasksSinFramePS[fCEScheduled[k].indexTasksSinFramePS]=tc;
                fCEScheduled[k].indexTasksSinFramePS++;
                numOfCS++;
                delete_by_priorityS_sched(tc,k);
                return;
            }
            else if(tc.deadline>fCEScheduled[k].endTime)
            {
                if(tc.remTimeAux<=fCEScheduled[k].slack)
                {
                    //slackAT
                    tS[tc.id].startSchTime=fCEScheduled[k].currentFrameTime;
                    if(tS[tc.id].remTimeAux==tS[tc.id].execTime)//take start time then
                    {
                        tS[tc.id].flagStartSchTime=1;
                        tS[tc.id].finalST=tS[tc.id].startSchTime;
                    }
                    fCEScheduled[k].currentFrameTime+=tS[tc.id].remTimeAux;
                    tS[tc.id].endSchTime=fCEScheduled[k].currentFrameTime;
                    printf("\nk=%d tS=%d j= endSchTime=%f",k,tS[tc.id].id,tS[tc.id].endSchTime);
                    fCEScheduled[k].slack-=tS[tc.id].remTimeAux;//else sum slack and compare with et
                    tS[tc.id].remTimeAux-=tS[tc.id].remTimeAux;
                    if(tS[tc.id].remTimeAux==0)
                    {
                        tS[tc.id].flagEndSchTime=2;//take end time then
                        tS[tc.id].finalET=tS[tc.id].endSchTime;
                    }
                  //  printf("\nbefore 2nd return 1");
                    fCEScheduled[k].tasksSinFramePS[fCEScheduled[k].indexTasksSinFramePS]=tc;
                    fCEScheduled[k].indexTasksSinFramePS++;
                    numOfCS++;
                    delete_by_priorityS_sched(tc,k);
                    return;
                }
                else
                {
                    //slackAT
                    tS[tc.id].startSchTime=fCEScheduled[k].currentFrameTime;
                    if(tS[tc.id].remTimeAux==tS[tc.id].execTime)//take start time then
                    {
                        tS[tc.id].flagStartSchTime=1;
                        tS[tc.id].finalST=tS[tc.id].startSchTime;
                    }
                    fCEScheduled[k].currentFrameTime+=fCEScheduled[k].slack;
                    //not ended-but current part end time
                    tS[tc.id].endSchTime=fCEScheduled[k].currentFrameTime;
                    printf("\nk=%d tS=%d j= endSchTime=%f",k,tS[tc.id].id,tS[tc.id].endSchTime);
                    tS[tc.id].remTimeAux-=fCEScheduled[k].slack;
                    if(tS[tc.id].remTimeAux==0)
                    {
                        tS[tc.id].flagEndSchTime=2;//take end time then
                        tS[tc.id].finalET=tS[tc.id].endSchTime;
                    }
                    fCEScheduled[k].slack-=fCEScheduled[k].slack;
                    fCEScheduled[k].tasksSinFramePS[fCEScheduled[k].indexTasksSinFramePS]=tc;
                    fCEScheduled[k].indexTasksSinFramePS++;
                    numOfCS++;
                }
            }
                
        }
        //return;
        if(tc.remTimeAux==0)// or tc.remTimeAux<=slackAT
        {
           // printf("\nbefore 3rd return 1");
            delete_by_priorityS_sched(tc,k);
            return;
        }
    }
}

void serverS(int k,float ctCE)//ctCE=start of frame k
{
    //no need to check utilization
    for(int i=0;i<=rearSaux;i++)
    {
        //for frame k, which sporadic tasks are available
        if(pri_queue_tSaux[i].arrival<=ctCE)
        {
            insert_by_priorityS_sched(pri_queue_tSaux[i],k);
        }
    }
    for(int i=0;i<=rearS_sched;i++)
    {
       // printf("\nk=%d ctCE=%f pri_queue_tS_sched[%d].id=%d",k,ctCE,i,pri_queue_tS_sched[i].id);
    }
    for(int i=0;i<=rearS_sched;i++)
    {
        scheduleATs(k,pri_queue_tS_sched[i],ctCE);
    }
}

void delete_by_priorityAaux(taskA tdel,int k)
{
    int i;
    if ((frontAaux==-1) && (rearAaux==-1))
    {
        printf("\nQueue is empty no elements to delete");
        return;
    }
    for (i = 0; i <= rearAaux; i++)
    {
        if (tdel.id == pri_queue_tAaux[i].id)
        {
            for (; i < rearAaux; i++)
            {
                pri_queue_tAaux[i] = pri_queue_tAaux[i + 1];
            }
        rearAaux--;
        if (rearAaux == -1) 
            frontAaux = -1;
        return;
        }
    }
    printf("\ntask %d not found in queue to delete", tdel.id);
}

void delete_by_priorityA_sched(taskA tdel,int k)
{
    int i;
    if ((frontA_sched==-1) && (rearA_sched==-1))
    {
        printf("\nQueue is empty no elements to delete");
        return;
    }
    for (i = 0; i <= rearA_sched; i++)
    {
        if (tdel.id == pri_queue_tA_sched[i].id)
        {
            for (; i < rearA_sched; i++)
            {
                pri_queue_tA_sched[i] = pri_queue_tA_sched[i + 1];
            }
        rearA_sched--;
        if (rearA_sched == -1) 
            frontA_sched = -1;
        return;
        }
    }
    printf("\ntask %d not found in queue to delete", tdel.id);
}

// void check_taskA_sched(taskA tc,int k)//not needed as pri_queue_tAaux was already sorted by arrival time

void insert_by_priorityA_sched(taskA ti,int k)
{
    if(rearA_sched>=MAX_SIZE-1)
    {
        return;
    }
    if ((frontA_sched == -1) && (rearA_sched == -1))//first element to be inserted
    {
        frontA_sched++;
        rearA_sched++;
        pri_queue_tA_sched[rearA_sched] = ti;
        //delete from pri_queue_tSaux
        delete_by_priorityAaux(ti,k);
        return;
    }    
    else
    {
        pri_queue_tA_sched[rearA_sched+1] = ti;
        delete_by_priorityAaux(ti,k);
    }
    rearA_sched++;
}

void scheduleATa(int k,taskA tc,float ctCE)
{
    //schedule from pri_queue_tS_sched within frame
    printf("\nfCEScheduled[%d].slack=%f",k,fCEScheduled[k].slack);
    while(fCEScheduled[k].currentFrameTime < (ctCE+bestFSpossibleCE))
    {
        if(tA[tc.id].remTimeAux>0 && fCEScheduled[k].slack>0)
        {        
            // if(tc.deadline<=fCEScheduled[k].endTime && tc.deadline>fCEScheduled[k].currentFrameTime)
            // {
                //execForInAT=tc.deadline-fCEScheduled[k].currentFrameTime;
                //if(tA[tc.id].remTimeAux<=execForInAT)//included <=slack//will be true by default as has already been checked
                //{

                    // tA[tc.id].startSchTime=fCEScheduled[k].startTime;
                    // if(tA[tc.id].remTimeAux==tA[tc.id].execTime)//take start time then
                    // {
                    //     tA[tc.id].flagStartSchTime=1;
                    //     tA[tc.id].finalST=tA[tc.id].startSchTime;
                    // }

                    // fCEScheduled[k].currentFrameTime+=tA[tc.id].remTimeAux;

                    // tA[tc.id].endSchTime=fCEScheduled[k].currentFrameTime;
                    // printf("\nk=%d tA=%d j= endSchTime=%f",k,tA[tc.id].id,tA[tc.id].endSchTime);
                    // fCEScheduled[k].slack-=tA[tc.id].remTimeAux;
                    // tA[tc.id].remTimeAux-=tA[tc.id].remTimeAux;
                    // if(tA[tc.id].remTimeAux==0)
                    // {
                    //     tA[tc.id].flagEndSchTime=2;//take end time then
                    //     tA[tc.id].finalET=tA[tc.id].endSchTime;
                    // }
                    // printf("\nbefore return 1");
                    // //end tc-delete from pri_queue_tS_sched
                    // //also firstly add to frame
                    // fCEScheduled[k].tasksAinFramePS[fCEScheduled[k].indexTasksAinFramePS]=tc;
                    // fCEScheduled[k].indexTasksAinFramePS++;
                    // numOfCS++;
                    // delete_by_priorityA_sched(tc,k);
                    // return;
                //}
            //}
            // else if(tc.deadline>fCEScheduled[k].endTime)
            // {
                    if(tc.remTimeAux<=fCEScheduled[k].slack)
                    {
                        //slackAT
                        tA[tc.id].startSchTime=fCEScheduled[k].startTime;
                        if(tA[tc.id].remTimeAux==tA[tc.id].execTime)//take start time then
                        {
                            tA[tc.id].flagStartSchTime=1;
                            tA[tc.id].finalST=tA[tc.id].startSchTime;
                        }

                        fCEScheduled[k].currentFrameTime+=tA[tc.id].remTimeAux;

                        tA[tc.id].endSchTime=fCEScheduled[k].startTime+tA[tc.id].remTimeAux;

                       // printf("\nk=%d tA=%d j= endSchTime=%f",k,tA[tc.id].id,tA[tc.id].endSchTime);

                        fCEScheduled[k].slack-=tA[tc.id].remTimeAux;//else sum slack and compare with et

                        tA[tc.id].remTimeAux-=tA[tc.id].remTimeAux;
                        if(tA[tc.id].remTimeAux==0)
                        {
                            tA[tc.id].flagEndSchTime=2;//take end time then
                            tA[tc.id].finalET=tA[tc.id].endSchTime;
                        }
                     //   printf("\nbefore 2nd return 1");

                        fCEScheduled[k].tasksAinFramePS[fCEScheduled[k].indexTasksAinFramePS]=tc;
                        fCEScheduled[k].indexTasksAinFramePS++;
                        numOfCS++;

                        //for other tasks in frame
                        //periodic

                        //sporadic

                        delete_by_priorityA_sched(tc,k);
                        return;
                    }
                    else
                    {
                        //slackAT
                        tA[tc.id].startSchTime=fCEScheduled[k].startTime;

                        if(tA[tc.id].remTimeAux==tA[tc.id].execTime)//take start time then
                        {
                            tA[tc.id].flagStartSchTime=1;
                            tA[tc.id].finalST=tA[tc.id].startSchTime;
                        }

                        fCEScheduled[k].currentFrameTime+=fCEScheduled[k].slack;

                        //not ended-but current part end time
                        tA[tc.id].endSchTime=fCEScheduled[k].startTime+fCEScheduled[k].slack;

                        printf("\nk=%d tA=%d j= endSchTime=%f",k,tA[tc.id].id,tA[tc.id].endSchTime);
                        tA[tc.id].remTimeAux-=fCEScheduled[k].slack;
                        if(tA[tc.id].remTimeAux==0)
                        {
                            tA[tc.id].flagEndSchTime=2;//take end time then
                            tA[tc.id].finalET=tA[tc.id].endSchTime;
                        }

                        fCEScheduled[k].slack-=fCEScheduled[k].slack;

                        fCEScheduled[k].tasksAinFramePS[fCEScheduled[k].indexTasksAinFramePS]=tc;
                        fCEScheduled[k].indexTasksAinFramePS++;
                        numOfCS++;
                    }
                //}
                
        }
        //return;
        if(tc.remTimeAux==0)// or tc.remTimeAux<=slackAT
        {
           // printf("\nbefore 3rd return 1");
            //numOfCS++;
            delete_by_priorityA_sched(tc,k);
            return;
        }
    }
}

void serverA(int k,float ctCE)
{
    //no need to check utilization
   // printf("\n rearaux above=%d",rearAaux);
    for(int i=0;i<=rearAaux;i++)
    {
        //for frame k, which sporadic tasks are available
        if(pri_queue_tAaux[i].arrival<=ctCE)
        {
            insert_by_priorityA_sched(pri_queue_tAaux[i],k);
            //printf("\nrearAaux=%d rearA_sched=%d i=%d idA=%d ctCE=%f\n",rearAaux,rearA_sched,i,pri_queue_tA_sched[i].id,ctCE);
        }
    }

    for(int i=0;i<=rearA_sched;i++)
    {
        //printf("\nk=%d ctCE=%f pri_queue_tA_sched[%d].id=%d",k,ctCE,i,pri_queue_tA_sched[i].id);
    }

    for(int i=0;i<=rearA_sched;i++)
    {
        //scheduleATa(k,pri_queue_tA_sched[i],ctCE);
    }
}

void rtWTps()
{
    int x,y,fNum;
        float ftRT,ftWT;
        int inPS;
        inPS=0;
        float maxRTall[nPS],minRTall[nPS],avgRTall[nPS],maxWTall[nPS],minWTall[nPS],avgWTall[nPS];
        float fRT,fWT;
        fRT=0;
        fWT=0;
        for(int i=0;i<MAX_SIZE;i++)
        {
            ftRT=0;
            ftWT=0;
            if(tPS[i].flag==1)
            {
                for(int j=0;j<tPS[i].totJobs;j++)
                {
                    fNum=tPS[i].taskJobPS[j].scheduleInFrame-1;
                    tPS[i].msRtPS[j]=tPS[i].taskJobPS[j].respTime;
                    tPS[i].msWtPS[j]=tPS[i].taskJobPS[j].waitTime;
                    ftRT+=tPS[i].msRtPS[j];
                    ftWT+=tPS[i].msWtPS[j];
                }
                mergeSortInc(tPS[i].msRtPS,0,tPS[i].totJobs-1);
                tPS[i].maxRespTime=tPS[i].msRtPS[tPS[i].totJobs-1];
                tPS[i].minRespTime=tPS[i].msRtPS[0];
                tPS[i].avgRespTime=ftRT/tPS[i].totJobs;
                mergeSortInc(tPS[i].msWtPS,0,tPS[i].totJobs-1);
                tPS[i].maxWaitTime=tPS[i].msWtPS[tPS[i].totJobs-1];
                tPS[i].minWaitTime=tPS[i].msWtPS[0];
                tPS[i].avgWaitTime=ftWT/tPS[i].totJobs;
                maxRTall[inPS]=tPS[i].maxRespTime;
                minRTall[inPS]=tPS[i].minRespTime;
                avgRTall[inPS]=tPS[i].avgRespTime;
                fRT+=tPS[i].avgRespTime;
                maxWTall[inPS]=tPS[i].maxWaitTime;
                minWTall[inPS]=tPS[i].minWaitTime;
                avgWTall[inPS]=tPS[i].avgWaitTime;
                fWT+=tPS[i].avgWaitTime;
                inPS++;
            }
        }
        //for(int i=0;i<nPS;i++)
        //{ 
            mergeSortInc(maxRTall,0,nPS-1);
            maxRespTimePS=maxRTall[nPS-1];
            minRespTimePS=minRTall[0];
            avgRespTimePS=fRT/nPS;
            mergeSortInc(maxWTall,0,nPS-1);
            maxWaitTimePS=maxWTall[nPS-1];
            minWaitTimePS=minWTall[0];
            avgWaitTimePS=fWT/nPS;
        //}
            printf("\n maxRespTimePS=%f",maxRespTimePS);
            printf("\n minRespTimePS=%f",minRespTimePS);
            printf("\n avgRespTimePS=%f",avgRespTimePS);
            printf("\n maxWaitTimePS=%f",maxWaitTimePS);
            printf("\n minWaitTimePS=%f",minWaitTimePS);
            printf("\n avgWaitTimePS=%f",avgWaitTimePS);

}

void schedulerCE()
{
    int k;
    currentTimeCE=0;
    k=0;//upto numOfFramesCE-1
    while(currentTimeCE < hyperPeriodCE)//executing for just 1 hp else can do forever loop if want to show more further
        {
            if(currentTimeCE==(k*bestFSpossibleCE))
            {
                //schedule(i);
                serverPS(k);
                serverS(k,currentTimeCE);
                //serverA(k,currentTimeCE);
                printf("\nframe %d end",k);
                k++;
            }
            //printf("\nbct=%f",currentTimeCE);
            currentTimeCE+=GRANULARITY;
            //printf("\nact=%f",currentTimeCE);
        }
        //wt
        //rt
        rtWTps();
}

void findFinalPeriodicSchedule(char *fName1,char *fName2,char *fName3,char *fName4)
{
    createS_sched();
    createA_sched();
    utilizationCE=0;
    numOfCS=0;
    getAperiodic(fName1);
    getSporadic(fName2);
    getPS(fName3);

    sortAperiodic();//why mergesort-as may already be in sorted order-get aA[]//quick when in sorted order 
    //gives O(sq(n)). So merge sort is better here

    queueA();
    sortSporadic();
    queueS();

    schedulerCE();

    FILE *fp4=fopen(fName4,"w"); //finalPeriodicSchedule.txt
    if (fp4 == NULL)
    {
      printf("\nCannot open file \n");
      exit(1);
    }
    fprintf(fp4,"Number of frames: %d    Best frame size possible: %d\n",numOfFramesCE,bestFSpossibleCE);
    taskPS dis;
    int s,tNum,jNum;
    for(int i=0;i<numOfFramesCE;i++)
    {
        fprintf(fp4,"Frame : %d\n",fCEScheduled[i].id);
        //printf("\nFrame %d: ,frame start time=%f tot tasks in it=%d\n",i,fCEScheduled[i].startTime,fCEScheduled[i].frameTasks);
            //if periodic

            for(int j=0;j<fCEScheduled[i].index;j++)//for number of tasks in frame
            {
                for(int k=0;k<fCEScheduled[i].tasksInFramePS[j].totJobs;k++)//for job of task present in frame
                {
                    if(fCEScheduled[i].tasksInFramePS[j].taskJobPS[k].scheduleInFrame==i+1)//i.e. kth job is scheduled in ith frame
                    {
                        tNum=fCEScheduled[i].tasksInFramePS[j].id;
                        jNum=k;

                        fprintf(fp4, "task : %d,job : %d    %f to %f    Arrival : %f\n", tNum,jNum,tPS[tNum].taskJobPS[k].startSchTime,tPS[tNum].taskJobPS[k].endSchTime,tPS[tNum].taskJobPS[k].arrival);
                    }
                }
            }
            int j;
            for(j=0;j<fCEScheduled[i].indexTasksSinFramePS;j++)
            {
                //if sporadic
                tNum=fCEScheduled[i].tasksSinFramePS[j].id;
                //printf("\n%d",tNum);
                //jNum=k;

                fprintf(fp4, "task : %d            %f to %f    Arrival : %f\n", tNum,tS[tNum].startSchTime,tS[tNum].endSchTime,tS[tNum].arrival);
               }
                //if idle
                if(j==fCEScheduled[i].indexTasksSinFramePS  && tS[tNum].endSchTime<fCEScheduled[i].endTime)
                {
                    //printf("\nIDLE currentFrameTime start=%f frame end=%f\n",f[i].currentFrameTime,f[i].endTime);
                    fprintf(fp4, "IDLE :              %f to %f\n", fCEScheduled[i].currentFrameTimeS,fCEScheduled[i].endTime);
                }
            
    }
    fclose(fp4);
}