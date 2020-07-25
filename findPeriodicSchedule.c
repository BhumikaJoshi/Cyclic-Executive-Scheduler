#include "executive.h"

void create()
{
    front = rear = -1;
}

void insert_task_by_priority(task ti,int finalPosFSsizeNum)
{
	//printf("\ntask id insert_task_by_priority():%d",ti.id);
    if (rear >= MAX_SIZE - 1)
    {
        //printf("\nQueue overflow no more elements can be inserted");
        return;
    }
    if ((front == -1) && (rear == -1))
    {
        front++;
        rear++;
        pri_task_que[finalPosFSsizeNum][rear] = ti;
        //insert_task_jobs(ti,finalPosFSsizeNum);
        return;
    }    
    else
        check_task(ti,finalPosFSsizeNum);
    rear++;
}
 
/* Function to check priority and place element */
void check_task(task tc,int finalPosFSsizeNum)
{
    int i,j,x;
 	//x=1;
    for (i = 0; i <= rear; i++)
    {
    	//printf("\ntc.arrival=%f,pri_task_que[finalPosFSsizeNum][i].arrival=%f",tc.arrival,pri_task_que[finalPosFSsizeNum][i].arrival);
    	if(tc.arrival == pri_task_que[finalPosFSsizeNum][i].arrival)
    	{
	        if (tc.period < pri_task_que[finalPosFSsizeNum][i].period)//see for =
	        {
	            for (j = rear + 1; j > i; j--)
	            {
	                pri_task_que[finalPosFSsizeNum][j] = pri_task_que[finalPosFSsizeNum][j - 1];
	            }
	            pri_task_que[finalPosFSsizeNum][i] = tc;
	            //insert_task_jobs(tc,finalPosFSsizeNum);
	            return;
	        }
	        else if(tc.period == pri_task_que[finalPosFSsizeNum][i].period)//then check for ET and give first
	        // chance to that job with greatest ET
	        {
	        	if(tc.execTime > pri_task_que[finalPosFSsizeNum][i].execTime)
	        	{
	        		for (j = rear + 1; j > i; j--)
		            {
		                pri_task_que[finalPosFSsizeNum][j] = pri_task_que[finalPosFSsizeNum][j - 1];
		            }
		            pri_task_que[finalPosFSsizeNum][i] = tc;
		            //insert_task_jobs(tc,finalPosFSsizeNum);
		            return;
	        	}
	        	else if(tc.execTime == pri_task_que[finalPosFSsizeNum][i].execTime)//give priority to one with lesser deadline
	        	{
	        		if(tc.deadline < pri_task_que[finalPosFSsizeNum][i].deadline)
	        		{
	        			for (j = rear + 1; j > i; j--)
			            {
			                pri_task_que[finalPosFSsizeNum][j] = pri_task_que[finalPosFSsizeNum][j - 1];
			            }
			            pri_task_que[finalPosFSsizeNum][i] = tc;
			            //insert_task_jobs(tc,finalPosFSsizeNum);
			            return;
	        		}
	        	}
	        }
    	}
    	else if(tc.arrival > pri_task_que[finalPosFSsizeNum][i].arrival)
    	{
    			continue;
    	}
    }
    //printf("\ninside check_task():task=%d,i=%d,front=%d,rear=%d",tc.id,i,front,rear);
    if(i==rear+1)
    {
    	pri_task_que[finalPosFSsizeNum][rear+1] = tc;
    	//insert_task_jobs(tc,finalPosFSsizeNum);
    }
}
 
/* Function to delete an element from queue */
void delete_task_by_priority(task tdel,int finalPosFSsizeNum)
{
    int i;
    if ((front==-1) && (rear==-1))
    {
        printf("\nQueue is empty no elements to delete");
        return;
    }
    for (i = 0; i <= rear; i++)
    {
        if (tdel.id == pri_task_que[finalPosFSsizeNum][i].id)
        {
            for (; i < rear; i++)
            {
                pri_task_que[finalPosFSsizeNum][i] = pri_task_que[finalPosFSsizeNum][i + 1];
            }
        //pri_task_que[finalPosFSsizeNum][i] = NULL;
        rear--;
 
        if (rear == -1) 
            front = -1;
        return;
        }
    }
    printf("\ntask %d not found in queue to delete", tdel.id);
}
 
/* Function to display queue elements */
void display_task_pqueue(int finalPosFSsizeNum)
{
	int x;
	x=front;
    if ((front == -1) && (rear == -1))
    {
        //printf("\nQueue is empty");
        return;
    }
 	//printf("\ndisplay queue task:\n");
    for (; front <= rear; front++)
    {
        //printf("task %d #job %d\n", pri_task_que[finalPosFSsizeNum][front].id,pri_task_que[finalPosFSsizeNum][front].job);
    }
    front = x;
}

void priorityTaskReadyQueue(task tp,int finalPosFSsizeNum)//since given in question to assume that arrival time jitter is zero (but even
//it is not correct to find the whole priority ready queue before hand as queue will change acc to arrival of
//tasks and that can be done by performing scheduling also simultaneously at every time instant)
{
	insert_task_by_priority(tp,finalPosFSsizeNum);
}
	
// Merges two subarrays of arr[]. 
// First subarray is arr[l..m] 
// Second subarray is arr[m+1..r] 
void merge(int arr[], int l, int m, int r) 
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
        if (f[L[i]].remFrameSize >= f[R[j]].remFrameSize) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else if(f[L[i]].remFrameSize < f[R[j]].remFrameSize)
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
void mergeSort(int arr[], int l, int r) 
{ 
    if (l < r) 
    { 
        // Same as (l+r)/2, but avoids overflow for 
        // large l and h 
        int m = l+(r-l)/2; 
  
        // Sort first and second halves 
        mergeSort(arr, l, m); 
        mergeSort(arr, m+1, r); 
  
        merge(arr, l, m, r); 
    } 
} 

void schedule(int finalPosFSsizeNum)
{
	task fetch;
	int tNum,jNum,x,y,i,currNumOfFramesFilled,z,bt;
	
	flagET=0;
	z=0;
	if ((front == -1) && (rear == -1))
    {
        //printf("\nQueue is empty");
        return;
    }
    fetch=pri_task_que[finalPosFSsizeNum][front];
    //loop for all tasks
    for(int j=0;j<n;j++)
   	{
   		//printf("\n\ntask=%d",fetch.id);//job cannot do and even not needed as jost have to check for task and not for job
   		if(fetch.execTime<=finalpossibleFSs[finalPosFSsizeNum]&&(z==0||z==1))//i.e. only can split for 1 task
    	{
	   		y=0;
	   		i=0;
	   		while(y<fetch.totJobs)
	   		{
		    	for(;i<numOfFrames;)
		    	{
		    		//printf("\n\ntask=%d fetch.taskJob[%d].jobNo=%d y=%d fetch.taskJob.arrival=%f f[%d].startTime=%f",
		    			//fetch.id,y,fetch.taskJob[y].jobNo,y,fetch.taskJob[y].arrival,i,f[i].startTime);
				    if(fetch.taskJob[y].arrival<=f[i].startTime)//decision points are just frame boundaries;that too mainly start of frame
				    {
				    	currNumOfFramesFilled=0;
				    	if(fetch.taskJob[y].execTime<=f[i].remFrameSize)//
				    	{
				    		if(f[i].flag==0)
				    			f[i].flag=1;
				    		f[i].frameTasks+=1;
					    	tNum=fetch.id;
					    	jNum=fetch.taskJob[y].jobNo;

					    	f[i].remFrameSize-=fetch.execTime;
					    	f[i].remFrameSizeAux-=fetch.execTime;
					    	//printf("\ntask %d job %d put in %d frame and remFrameSize %f",tNum,jNum,i,f[i].remFrameSize);
					    	//t[tNum].startSchTime=f[i].startTime
					    	t[tNum].taskJob[y].startSchTime=f[i].currentFrameTime;
					    	//printf("\nt[%d].taskJob[%d].startSchTime=%f,f[%d].currentFrameTime=%f",tNum,y,
					    		//t[tNum].taskJob[y].startSchTime,i,f[i].currentFrameTime);
					    	f[i].currentFrameTime=f[i].currentFrameTime+fetch.execTime;
					    	t[tNum].taskJob[y].endSchTime=f[i].currentFrameTime;
					    	//printf("\nt[%d].taskJob[%d].endSchTime=%f,f[%d].currentFrameTime=%f",tNum,y,
					    		//t[tNum].taskJob[y].endSchTime,i,f[i].currentFrameTime);

					    	f[i].tasksInFrame[finalPosFSsizeNum][f[i].frameTasks-1]=t[tNum];
			    			f[i].tasksInFrame[finalPosFSsizeNum][f[i].frameTasks-1].taskJob[jNum].scheduleInFrame=i+1;
					    	
					    	i++;
					    	break;
				    	}
				    }
				    //printf("\nremFrameSize for %d=%f\n",i,f[i].remFrameSize);
				    i++;
				}
				y++;
			}
			if(y==fetch.job)
				delete_task_by_priority(fetch,finalPosFSsizeNum);
			if(front==-1&&rear==-1)
				return;
		    fetch=pri_task_que[finalPosFSsizeNum][front];
		}
		else if(fetch.execTime>finalpossibleFSs[finalPosFSsizeNum]&&z==0)
		{
			z+=1;
			for(int k=0;k<numOfFrames;k++)
			{
				ar[k]=k;
				aux[k]=0;
			}
			//sort frames by decreasing order of their remaining times, by starting with ith frame itself
			//firstly an array of id is taken and using that sorting is done
			// for(int m=0;m<numOfFrames;m++)
			// {
			// 	printf("\nar[%d]=%d",m,ar[m]);
			// 	printf("\naux[%d]=%d",m,aux[m]);
			// }
			// printf("\n");
			// for(int pq=0;pq<numOfFrames;pq++)
			// {
			// 	printf("f[%d].remFrameSize=%f",pq,f[pq].remFrameSize);
			// }
			mergeSort(ar, 0, numOfFrames - 1); 
			// for(int m=0;m<numOfFrames;m++)
			// {
			// 	printf("\nar[%d]=%d",m,ar[m]);
			// 	printf("\naux[%d]=%d",m,aux[m]);
			// }
			//now split job by checking rem fs from dec sorted array ar
			//first check if can be put in that frame then if yes then form new tasks
			int fET,totalNumOfJobs;
			fET=fetch.execTime;
			totalNumOfJobs=fetch.totJobs;

			for(int k=0;k<numOfFrames;k++)//have not allocated tasks to frames yet, now are just checking i.e.
			// splitting into min #tasks
			{//better to check fetch.execTimeAux==0 as then will only be valid for equal to zero
				if(fetch.arrival<=f[ar[k]].startTime && f[ar[k]].remFrameSizeAux>0 && fetch.execTimeAux>0 && fetch.flagSplit==0)//decision points are just frame boundaries;that too mainly start of frame
				{
					//if(fetch.execTimeAux==f[ar[k]].remFrameSize)
					printf("\nnAfterSplitting=%d",nAfterSplitting);
					taskSplittedID=fetch.id;
					taskSplittedFlag=1;
					//nAfterSplitting++;//then final will be nAfterSplitting-1 as 1 is splitted
					t[nAfterSplitting].id=nAfterSplitting;
					t[nAfterSplitting-1].taskSplitID=fetch.id+1;

					t[nAfterSplitting].frameID=f[ar[k]].id;
					t[fetch.id].numOfTaskSplits+=1;

			        t[nAfterSplitting].arrival=fetch.arrival;
			        t[nAfterSplitting].period=fetch.period;
			        if(fetch.execTimeAux>=f[ar[k]].remFrameSizeAux)
			        {  
			        	t[nAfterSplitting].execTime=f[ar[k]].remFrameSizeAux;
			        	t[nAfterSplitting].execTimeAux-=f[ar[k]].remFrameSizeAux; 
			        }
			    	else
			    	{
			    		t[nAfterSplitting].execTime=fetch.execTimeAux;
			    		t[nAfterSplitting].execTimeAux-=fetch.execTimeAux; 
			    	}  
			        t[nAfterSplitting].deadline=fetch.deadline;

			        t[nAfterSplitting].totJobs=fetch.totJobs;
			        t[fetch.id].flagSplit=1;

		     		for(int ft=0;ft<fetch.totJobs;ft++)
		     		{
		     			t[nAfterSplitting].taskJob[ft].jobNo=ft;
		     			t[nAfterSplitting].taskJob[ft].remTime=fetch.taskJob[ft].execTime;
		     			t[nAfterSplitting].taskJob[ft].slack=0;
		     			t[nAfterSplitting].taskJob[ft].taskNo=fetch.id+1;//
				        t[nAfterSplitting].taskJob[ft].arrival=fetch.taskJob[ft].arrival;
				        t[nAfterSplitting].taskJob[ft].period=fetch.taskJob[ft].period;
				        if(fetch.execTimeAux>=f[ar[k]].remFrameSizeAux)
				        	t[nAfterSplitting].taskJob[ft].execTime=f[ar[k]].remFrameSizeAux;
				        else
				        	t[nAfterSplitting].taskJob[ft].execTime=fetch.execTimeAux;
				        t[nAfterSplitting].taskJob[ft].deadline=fetch.taskJob[ft].deadline;
		     		}

			        //printf("\nt[%d].id=%d",nAfterSplitting,t[nAfterSplitting].id);
			        //printf("\nbefore fetch.execTimeAux=%f f[%d].remFrameSizeAux=%f",fetch.execTimeAux,ar[k],
			        	//f[ar[k]].remFrameSizeAux);
			        if(fetch.execTimeAux>=f[ar[k]].remFrameSizeAux)
			        {
			        	fetch.execTimeAux-=f[ar[k]].remFrameSizeAux;//let it be zero so as not to take it into consideration 
			        	f[ar[k]].remFrameSizeAux-=f[ar[k]].remFrameSizeAux;
			        }
			        else
			        {
			        	f[ar[k]].remFrameSizeAux-=fetch.execTimeAux;
			        	fetch.execTimeAux-=fetch.execTimeAux;//let it be zero so as not to take it into consideration 
			        }
			        //further when perform scheduling

			        //printf("\nafter fetch.execTimeAux=%f f[%d].remFrameSizeAux=%f",fetch.execTimeAux,ar[k],
			        	//f[ar[k]].remFrameSizeAux);

			        nAfterSplitting++;
				}
			}
//now performing scheduling
			y=0;
			while(y<totalNumOfJobs)
			{
		   		for(bt=n;bt<nAfterSplitting;bt++)
		   		{
			    	for(int i=0;i<numOfFrames;i++)
			    	{
			    		//printf("\n\ntask=%d t[%d].taskJob[%d].jobNo=%d y=%d t[bt].taskJob.arrival=%f f[%d].startTime=%f",
			    			//t[bt].id,bt,y,t[bt].taskJob[y].jobNo,y,t[bt].taskJob[y].arrival,ar[i],f[ar[i]].startTime);
					    if(t[bt].taskJob[y].arrival<=f[ar[i]].startTime)//decision points are just frame boundaries;that too mainly start of frame
					    {
					    	//printf("\nt[%d].execTime=%f f[%d].remFrameSize=%f",
					    		//bt,t[bt].execTime,ar[i],f[ar[i]].remFrameSize);
					    	if(t[bt].execTime<=f[ar[i]].remFrameSize)//
					    	{
					    		if(f[ar[i]].flag==0)
					    			f[ar[i]].flag=1;
					    		f[ar[i]].frameTasks+=1;
						    	tNum=t[bt].id;
						    	jNum=t[bt].taskJob[y].jobNo;
						    	f[ar[i]].remFrameSize-=t[bt].execTime;
						    	//printf("\ntask %d job %d put in %d frame and remFrameSize %f",tNum,jNum,ar[i],f[ar[i]].remFrameSize);
						    	t[bt].taskJob[y].startSchTime=f[ar[i]].currentFrameTime;
						    	//printf("\nt[%d].taskJob[%d].startSchTime=%f,f[%d].currentFrameTime=%f",bt,y,
						    		//t[bt].taskJob[y].startSchTime,ar[i],f[ar[i]].currentFrameTime);
						    	f[ar[i]].currentFrameTime=f[ar[i]].currentFrameTime+t[bt].execTime;
						    	t[bt].taskJob[y].endSchTime=f[ar[i]].currentFrameTime;
						    	//printf("\nt[%d].taskJob[%d].endSchTime=%f,f[%d].currentFrameTime=%f",bt,y,
						    		//t[bt].taskJob[y].endSchTime,ar[i],f[ar[i]].currentFrameTime);

						    	f[ar[i]].tasksInFrame[finalPosFSsizeNum][f[ar[i]].frameTasks-1]=t[bt];
				    			f[ar[i]].tasksInFrame[finalPosFSsizeNum][f[ar[i]].frameTasks-1].taskJob[jNum].scheduleInFrame=ar[i]+1;

						    	break;
					    	}
					    }
					    //printf("\nremFrameSize for %d=%f\n",ar[i],f[ar[i]].remFrameSize);
					}
				}
				y++;
			}
			nAfterSplitting=0;
			int numTasks;
			if(taskSplittedFlag==1)
			numTasks=t[taskSplittedID].numOfTaskSplits;
			for(int k=0;k<numTasks;k++)
			{
				printf("\n\ntask=%d split to numTasks=%d task[%d] et=%f frame=%d",taskSplittedID,numTasks,
					nBeforeSplitting+k,t[nBeforeSplitting+k].execTime,t[nBeforeSplitting+k].frameID);
			}
		}
	}
}

void jobsArriving(float currTime,int finalPosFSsizeNum)     //updates remaining time and slack of the new job
{
	int y;
    for(int i=0;i<n;i++)
    {
        if((t[i].arrival == currTime) || (t[i].nextArrival == currTime && t[i].job>=0 && t[i].job<t[i].totJobs))
        {
        	//printf("job arrived=%d",i);
            t[i].job+=1;
           	t[i].taskJob[t[i].job-1].jobNo=t[i].job-1;
           	y=t[i].taskJob[t[i].job-1].jobNo;
          
            t[i].taskJob[y].arrival=t[i].nextArrival;
            t[i].taskJob[y].deadline=t[i].nextDeadline;
            
            t[i].nextArrival=currTime+t[i].period;
            t[i].nextDeadline=currTime+t[i].deadline;
        }
    }
}

void graphMapping()//performing scheduling as time increments
{
	flagSchFrame=0;
	for(int i=0;i<finalpossibleFSsSize;i++)//for each iteration i.e. for each possible frame size
	{
		nAfterSplitting=n;
		nBeforeSplitting=n;
		size=0;
		obtainedFlow=0;
		create();
		for(int j=0;j<n;j++)
		{
     		t[j].nextArrival=0;
     		t[j].nextDeadline=0;
     		t[j].job=0;
     		t[j].execTimeAux=t[j].execTime;
     		t[j].numOfTaskSplits=0;
		    t[i].flagSplit=0;
     		for(int k=0;k<t[j].totJobs;k++)
     		{
     			t[j].taskJob[k].jobNo=k;
     			t[j].taskJob[k].remTime=t[j].execTime;
     			t[j].taskJob[k].slack=0;
     			t[i].taskJob[k].taskNo=j;
		        t[j].taskJob[k].arrival=t[j].arrival;
		        t[j].taskJob[k].period=t[j].period;
		        t[j].taskJob[k].execTime=t[j].execTime;
		        t[j].taskJob[k].deadline=t[j].deadline;
     		}
		}
		currentTask=-1;
    	currentTime = 0;
    	currentFrame=0;
		numOfFrames=hyperPeriod/finalpossibleFSs[i];
		st=0;
		et=finalpossibleFSs[i];
		for(int j=0;j<numOfFrames;j++)
		{
			f[j].flag=0;
			f[j].id=j;
			f[j].startTime=st;
			f[j].endTime=et;
			f[j].remFrameSize=finalpossibleFSs[i];
			f[j].remFrameSizeAux=finalpossibleFSs[i];
			f[j].frameTasks=0;
			f[j].currentFrameTime=st;
			st+=finalpossibleFSs[i];
			et+=finalpossibleFSs[i];
		}
		//printf("\nnumOfFrames=%d",numOfFrames);
		//printf("\nst=%f",st);
		//printf("\net=%f",et);
		while(currentTime <= hyperPeriod)
	 	{
        	jobsArriving(currentTime,i);    //first time the job arrives
			currentTime+=GRANULARITY;
		}
		//display_task_pqueue(i);//no effect as has not been entered to queue yet
		for(int j=0;j<n;j++)//inserting tasks (and not jobs) to priority queue
		{
			priorityTaskReadyQueue(t[j],i);
		}
		//display_task_pqueue(i);
		schedule(i);

		for(int j=0;j<numOfFrames;j++)
			if(f[j].flag==1)
			{
				size+=1;
			}
		for(int j=0;j<size;j++)//if to be applied for remFrameSizeAux
        	obtainedFlow=obtainedFlow+finalpossibleFSs[i]-f[j].remFrameSizeAux;//for now remFrameSizeAux
        //on basis of flow obtained it is decided whether valid frame size or not
        printf("\ntotalET=%f\n",totalET);
        printf("\nobtainedFlow=%f\n",obtainedFlow);
		if(obtainedFlow==totalET)
		{
			flagSchFrame=1;
			bestPossibleFS=finalpossibleFSs[i];
			finalpossibleFSsSizeID=i;
			//printf("\nbestPossibleFS=%d",bestPossibleFS);
			//displayFrameTable(i,size);
			break;
		}
	}
}

void totalNumberOfJobs()
{
	totalJobs=0;
	for(int i=0;i<n;i++)
	{
		t[i].totJobs=hyperPeriod/t[i].period;
		//printf("\nt[%d].totJobs=%d t[%d].execTime=%f",i,t[i].totJobs,i,t[i].execTime);
		totalJobs+=hyperPeriod/t[i].period;
		//printf("\ntotalJobs after i=%d is %d",i,totalJobs);
		totalET+=t[i].totJobs*t[i].execTime;
		//printf("\ntotalET=%f",totalET);
	}
}

void findPeriodicSchedule(char *fName)
{
	taskSplittedFlag=0;
	const char *text1 = "Total number of input tasks=";
	const char *text2 = "Periodic Schedule obtained consists of total tasks=";
	taskJobArrayCurr=0;
	totalET=0;
	totalNumberOfJobs();
	graphMapping();
	if(flagSchFrame==0)
	{
		printf("\nSchedule not possible for any frame size\n");
		exit(0);
	}
	printf("\nbestPossibleFS=%d\n",bestPossibleFS);
	bestNumOfFrames=hyperPeriod/bestPossibleFS;

	FILE *fp=fopen(fName,"w"); //file name taken from the command line
    if (fp == NULL)
    {
      printf("Cannot open file \n");
      exit(1);
    }
    fprintf(fp,"Number of frames: %d    Best frame size possible: %d\n",bestNumOfFrames,bestPossibleFS);
    task dis;
	int s,tNum,jNum;
    for(int i=0;i<bestNumOfFrames;i++)
    {
    	fprintf(fp,"Frame : %d\n",f[i].id);
    	//printf("\nFrame %d: ,frame start time=%f tot tasks in it=%d\n",i,f[i].startTime,f[i].frameTasks);
	    	for(int j=0;j<f[i].frameTasks;j++)//for number of tasks in frame
	    	{
	    		for(int k=0;k<f[i].tasksInFrame[finalpossibleFSsSizeID][j].totJobs;k++)//for job of task present in frame
	    		{
		    		if(f[i].tasksInFrame[finalpossibleFSsSizeID][j].taskJob[k].scheduleInFrame==i+1)//i.e. kth job is scheduled in ith frame
		    		{
				    	tNum=f[i].tasksInFrame[finalpossibleFSsSizeID][j].id;
					    jNum=k;
					    //printf("\nf[i=%d].tasksInFrame[finalpossibleFSsSizeID][j=%d].taskJob[k=%d].endSchTime=%f f[i].endTime=%f",i,j,k,
					    	//f[i].tasksInFrame[finalpossibleFSsSizeID][j].taskJob[k].endSchTime,f[i].endTime);
			    		//printf("\n|task=%d,job=%d|,startTime=%f,endTime=%f\n",tNum,jNum,t[tNum].taskJob[k].startSchTime,
			    			//t[tNum].taskJob[k].endSchTime);

			    		fprintf(fp, "task : %d,job : %d    %f to %f    Arrival : %f\n", tNum,jNum,t[tNum].taskJob[k].startSchTime,t[tNum].taskJob[k].endSchTime,t[tNum].taskJob[k].arrival);

			    		if(j==f[i].frameTasks-1  && f[i].tasksInFrame[finalpossibleFSsSizeID][j].taskJob[k].endSchTime<f[i].endTime)
			    		{
			    			//printf("\nIDLE currentFrameTime start=%f frame end=%f\n",f[i].currentFrameTime,f[i].endTime);
			    			fprintf(fp, "IDLE :              %f to %f\n", f[i].currentFrameTime,f[i].endTime);
			    		}
		    		}
		    	}
	    	}
    }                                                   
    fclose(fp);
}
