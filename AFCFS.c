//  Gang Scheduling - Adapted First Come First Served Scheduling Algorithm. In this algorithm the job arriving first is given priority provided
//  the processors required by the job are available.
#include<stdio.h>
#include<stdlib.h>
int p;
// p indicates the number of processors.
int ousterhout[10000][33]={0};
// Ousterhout matrix is an optimal data structure used for implementing gang scheduling algorithms 
// The columns represent the number of processors and rows represent time slices.
struct job
{
	int n, burst_t,waiting_t,id,iscomp,arrival_t;
}obj[10000],temp;
// A job or a gang consists of many tasks or processes denoted by n. Each gang has a burst time associated with itself. All processes
// of a gang are executed simultaneously in different processors.
main()
{
	time_t t;
	srand((unsigned) time(&t));
	int i,no_of_jobs,ap,ti=0,j,completed=0,q,l,r;
	//no_of_jobs denote the number of gangs, ti represents time.
	p =random()%30+5;
	// This lower bounds the number of processors randomly generated to 5
	no_of_jobs = random()%50+10;
	// This lower bounds the number of jobs randomly generated to 10 
	printf("\nNumber of processors randomly generated = %d",p);
	printf("\nNumber of jobs randomly generated = %d",no_of_jobs);
	for(i=0;i<no_of_jobs;i++)
	{
		obj[i].id = i+1;
		// unique id is generated for each gang.
		obj[i].n = random()%p+1;
		// random generation of number of tasks in each gang.
		obj[i].arrival_t=random()%100+0; // Gangs may arrive at time 0
		obj[i].burst_t = random()%100+10;  // Lower bounds burst times of gangs to 10
		obj[i].iscomp=0;
		// iscomp=0 indicates the job is not completed yet.
	}
	printf("\nId\tNo. of tasks\tBurst Time");
	for(l=0;l<no_of_jobs;l++)
	{
        printf("\n%d\t\t%d\t\t%d\n",obj[l].id,obj[l].n,obj[l].burst_t);
	}
	// Sort the gangs in the increasing order arrival time.
	for(i=0;i<no_of_jobs-1;i++)
	{
		for(j=0;j<no_of_jobs-i-1;j++)
		{
			if(obj[j].arrival_t>obj[j+1].arrival_t)
			{
				temp = obj[j];
				obj[j] = obj[j+1];
				obj[j+1] = temp;
			}
		}
	}
	printf("\nAfter sorting in ascending order by arrival time\n");
	printf("\nId\tNo. of tasks\tBurst Time\tArrival Time");
	for(l=0;l<no_of_jobs;l++)
	{
        printf("\n%d\t\t%d\t\t%d\t\t%d\n",obj[l].id,obj[l].n,obj[l].burst_t,obj[l].arrival_t);
	}
	i=0;
	// completed denotes the number of gangs completed. Initially, its 0.
	while(completed<no_of_jobs)
	{
		int cnt=0; 
		int crave;
		int start=1;
		// This loop counts the number of free processors available at time ti
		for(j=1;j<=p;j++)
			if(ousterhout[ti][j]==0)
				cnt++;
		i=0;
		while(i<no_of_jobs&&cnt!=0&&obj[i].arrival_t<=ti)
		{
			// Will reach here if number of free processors is not 0, and the gang has arrived
			if(obj[i].iscomp==0&&cnt>=obj[i].n)
			{
				// Will reach here only if the gang has not been executed (iscomp=0 when it is not executed) and 
				//number of processors free is greater than or equal to 
				// processes in the gang
				j=1;
				while(ousterhout[ti][j]!=0)
				{
						start++;j++;
						// Start points to the first free processor at time ti
				}
				crave=0;
				for(q=ti;q<ti+obj[i].burst_t;q++)
				{
					crave=0;
					// The matrix will be initialised with process id for the burst time and the number of processors it requires.	
					for(r=1;r<=p&&crave<obj[i].n;r++)
                	{
                		if(ousterhout[q][r]==0)
                		{
                		    ousterhout[q][r]=obj[i].id;
                            crave++;
                            //crave counts free processors which need not be contiguously available
                            // The occupied processors are indicated by the gang ID, free by 0
					    }
                    }
				}
				// decrementing the number of free processor with the processors required by the current job.
				cnt-=obj[i].n;
				completed++;
				obj[i].iscomp=1;
				//Mark the gang completed, increment number of gangs that are executed, and decrease the number of free processors
				printf("\nID %d  Job execution started at time %d, ",obj[i].id,ti);
				printf("Waiting time = %d ",ti-obj[i].arrival_t);
				obj[i].waiting_t = ti-obj[i].arrival_t;
				//Waiting time will be the difference between time and arrival_time
			}
			i++;
		}
		ti++;
		//Increment time slice
		
	}
	int sum_wt=0,sum_tat=0;
	//Calculate average waiting and turn around times
	for(i=0;i<no_of_jobs;i++)
	{
		sum_wt+=obj[i].waiting_t;
		sum_tat+=obj[i].burst_t+obj[i].waiting_t;
	}
	printf("\nAverage waiting time = %f",(float)sum_wt/no_of_jobs);
	printf("\nAverage turn around time = %f",(float)sum_tat/no_of_jobs);
		
}
