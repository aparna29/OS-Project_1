/*Gang Scheduling: largest gang First Served. In this the jobs are sorted in decreasing order of their gang size(number of tasks in the job).
if processors required by that job are less than or equal to the number of available free processors, then that job is executed otherwise next job is picked up. 
*/
#include<stdio.h>
#include<stdlib.h>
int p;
int ousterhout[10000][33]={0};
/* Ousterhout matrix is used for gang scheduling. The columns indicates the processors and the rows indicate time slice. The matrix is initialised to zero indicating all the processors are free.
*/
struct job
{
	int n, burst_t,waiting_t,id,iscomp,arrival_t;
}obj[10000],temp;
main()
{
	int i,no_of_jobs,ap,tim=0,j,completed=0,q,l,r;
	float sum_wait=0,sum_tat=0;
	time_t t;
	srand((unsigned) time(&t));
	p =random()%30 + 5;
	// Number of processors generated randomly. Minimum allowed is 5.
	no_of_jobs = random()%50+ 10;
	// Number of jobs generated randomly. Minimum allowed is 10.
	printf("\nNumber of processors randomly generated = %d",p);
	printf("\nNumber of jobs randomly generated = %d",no_of_jobs);
	for(i=0;i<no_of_jobs;i++)
	{
		obj[i].id = i+1;
		// Unique id is assigned to each process.
		obj[i].n = rand()%p+1;
		// n is number of tasks in a job.
		obj[i].arrival_t=random()%100+0; // Gangs may arrive at time 0
		obj[i].burst_t = random()%100+10;  // Lower bounds burst times of gangs to 10
		obj[i].iscomp=0;
		// iscomp=0 indicates the job has not been executed yet.
	}
	printf("\nID\tNo. of tasks\tBurst Time");
	for(l=0;l<no_of_jobs;l++)
	{
        printf("\n%d         %d            %d",obj[l].id,obj[l].n,obj[l].burst_t);
	}
	// Sorting the jobs in decreasing order of gang size (Number of tasks)
	for(i=0;i<no_of_jobs-1;i++)
	{
		for(j=0;j<no_of_jobs-i-1;j++)
		{
			if(obj[j].n<obj[j+1].n)
			{
				temp = obj[j];
				obj[j] = obj[j+1];
				obj[j+1] = temp;
			}
		}
	}
	printf("\n After sorting in descending order by number of tasks (Gang size) : \n");
	printf("\nId\tNo. of tasks\tBurst Time\tArrival Time");
	for(l=0;l<no_of_jobs;l++)
	{
        printf("\n%d\t\t%d\t\t%d\t\t%d\n",obj[l].id,obj[l].n,obj[l].burst_t,obj[l].arrival_t);
	}
	i=0;
	while(completed<no_of_jobs)
	{
		int cnt=0;
		// cnt indicate number of free processors.
		int crave;
		int start=1;
		// Counting the number of processors available.
		for(j=1;j<=p;j++)
			if(ousterhout[tim][j]==0)
				cnt++;
		i=0;
		// Checking which jobs can be assigned to the processor at that particular time slice.
		while(i<no_of_jobs&&cnt!=0)
		{
			// Checking if the job has not been executed and if it requires less or equal processor than those available.
			// and the job has arrived already.			
			if(obj[i].iscomp==0&&cnt>=obj[i].n&&obj[i].arrival_t<=tim)
			{
				j=1;
				// The variable start finds the first available processor.
				while(ousterhout[tim][j]!=0)
				{
						start++;j++;
				}
				crave=0;
			// If the availble processors aren't continuous, crave will count till the no. of processors required by the job.
			// The matrix will be updated with process id of the process executing for the burst time and the number of processors it 
			//	requires.			
				for(q=tim;q<tim+obj[i].burst_t;q++)
				{
					crave=0;
					for(r=1;r<=p&&crave<obj[i].n;r++)
                       		 {
                            if(ousterhout[q][r]==0)
                            {
								//initialise the matrix with job id.                                
								ousterhout[q][r]=obj[i].id;
                                crave++;
                            }
                        }
				}
				// Decrementing the number of free processor with the processors required by the current job.
				cnt-=obj[i].n;
				// Incrementing the number of completed jobs.
				completed++;
				obj[i].iscomp=1;
				// Marking the job complete.
				obj[i].waiting_t = tim;
				printf("\nID  %d  Waiting Time %d  turn around time %d",obj[i].id,obj[i].waiting_t,tim+obj[i].burst_t);
				// Calculating sum of waiting times.
				sum_wait+=obj[i].waiting_t;
				// Calculating the sum of turn around times.
				sum_tat+=(obj[i].waiting_t+obj[i].burst_t);
			}
			i++;
		}
		// Proceeding to the next time slice.
		tim++;
		
	}
	printf("\n\n Average waiting time:  %f\n",sum_wait/(float)(no_of_jobs));
	printf("\n Average Turn around time:  %f\n",sum_tat/(float)(no_of_jobs));

}
