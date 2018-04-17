#include<stdio.h> 

void Iteration(int num,int remt[10],int current_time,int arrt[10], int bt[10]);

int main() 
{
	int Pno,j,num,currentTime,remainingProcess,flag,tq,wt,tat,arrt[10],bt[10],remt[10],iterate=1;
	flag = 0;
	wt = 0;
	tat = 0;
	printf("Enter number of processes... "); 
	scanf("%d",&num);
	remainingProcess = num;
	printf("\nEnter details of the processes\n");
	for(Pno = 0;Pno < num;Pno++) 
	{
		printf("\nProcess P%d\n\t",Pno+1);
		printf("Arrival time = "); 
		scanf("%d",&arrt[Pno]);
		printf("\tBurst time = "); 
		scanf("%d",&bt[Pno]); 
		remt[Pno]=bt[Pno];
	} 
	
	printf("\nIteration...\n"); 
	tq=6;
	currentTime=0;
	printf("Process id\t\t\t TurnAroundTime\\t\t\tWaiting Time\n\n");

	for(Pno=0;remainingProcess!=0;) 
	{
		if(remt[Pno]<=tq && remt[Pno]>0)	//Process can be executed before time quantum expires
		{ 
			currentTime+=remt[Pno]; 
			remt[Pno]=0; 
			flag=1; 
		} 
		else if(remt[Pno]>0)
		{ 
			remt[Pno]-=tq; 
			currentTime+=tq; 
		} 
		if(remt[Pno]==0 && flag==1)
		{ 
			remainingProcess--;
			printf("P%d",Pno+1); 
			printf("\t\t\t\t%d",currentTime-arrt[Pno]);
			printf("\t\t\t\t%d\n",currentTime-bt[Pno]-arrt[Pno]);
			wt+=currentTime-arrt[Pno]-bt[Pno]; 
			tat+=currentTime-arrt[Pno]; 
			flag=0; 
		} 
		if(Pno==num-1){
			iterate++;
			if(iterate==2){
				Pno=0;
				tq=10;
				printf("\nIteration completes...");
				printf("\nNext iteration starts... (time quantum 10)\n\n");
			}
			else{
				printf("\n\nIteration completes...");
				break;
			}
		}
		else if(currentTime >= arrt[Pno+1]){
			Pno++;
		}
		else{
			Pno=0;
		}
	}
	
	Iteration(num,remt,currentTime,arrt,bt);
	
	return 0;
}


void Iteration(int num,int remt[10],int current_time,int arrt[10], int bt[10]){
	
	float averagewt,averagetat;
    int i,j,n=num,temp,btime[20],Pno[20],wtime[20],tatime[20],total=0,loc;
    
    printf("\nIteration started...(least burst time)\n");
    
    for(i=0;i<n;i++)
    {
        btime[i]=remt[i];
        wtime[i]=current_time-arrt[i]-btime[i];
		Pno[i]=i+1;
    }
	
    for(i=0;i<n;i++)
    {
        loc=i;
        for(j=i+1;j<n;j++)
        {
            if(btime[j]<btime[loc]){
            	loc=j;
            }
        }
        temp=btime[i];
        btime[i]=btime[loc];
        btime[loc]=temp;
        temp=Pno[i];
        Pno[i]=Pno[loc];
        Pno[loc]=temp;
    }
    for(i=1;i<n;i++)
    {
        for(j=0;j<i;j++){
        	wtime[i]+=btime[j];
        }
        total+=wtime[i];
    }
 
    averagewt=(float)total/n;
    total=0;
    printf("\nProcess\t\tBurst time\t\tWaiting time\t\tTurnaround Time");
    for(i=0;i<n;i++)
    {
        tatime[i]=btime[i]+wtime[i];
        total=total + tatime[i];
        printf("\nP%d\t\t\t%d\t\t\t%d\t\t\t%d",Pno[i],btime[i],wtime[i],tatime[i]);
    }
    averagetat=(float)total/n;
    printf("\n\nAverage waiting time of execution = %f",averagewt);
    printf("\nAverage turnaround time of execution = %f\n",averagetat);
    
}
