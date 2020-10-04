//Program: CPU Scheduling Alogorithms

#include<stdio.h>

// mode
// 1 => FCFS
// 2 => SJF
// 3 => PS
// 4 => RR

//n -> No: of processes in the processes array.
int n;
//process -> Structure of a process
struct process{
    int id;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnAroundTime;
    int waitingTime;
    int priority;
    int balanceTime;
	int completed;
};

int rear = -1, front = -1;
float totalTAT, totalWT;
int totalBT = 0;

void enqueue(int data, int readyQueue[]) {
	rear++;
	readyQueue[rear] = data;
	if(front==-1)
		front=0;
}

int dequeue(int readyQueue[]) {
	int temp = readyQueue[front];
	if(front == rear) 
		front = rear = -1;
	else
		front++;
	return temp;
}

int readyQueueCheck(int data, int readyQueue[]) {
	int k;
	for(k = front; k <= rear; k++) {
		if(readyQueue[k] == data)
			return 1;
	}
	return 0;
}

//Function Name: swap
//Inputs: Process A, Process B
//Output: Void
//Logic: For swaping two proceesses.
void swap(struct process *a, struct process *b){
    struct process temp = *a;
    *a = *b;
    *b = temp;
}

//Function Name: sortProcesses
//Inputs: Array of processes, index, mode
//Output: Void
//Logic: For sorting the processes after each iteration.
void sortProcesses(struct process processes[], int index, int mode){
    for(int i=index+1; i < n; i++)
        for(int j=index+1; j < n-i; j++)
        	//SJF
        	if (mode==2)
        		if(processes[j].arrivalTime <= processes[index].completionTime && processes[j].burstTime > processes[j+1].burstTime)
        				swap(&processes[j], &processes[j+1]);
        	//PS
        	else if (mode==3
        		&& processes[j].arrivalTime <= processes[index-1].completionTime 
        		&& processes[j+1].arrivalTime <= processes[index-1].completionTime 
        		&& processes[j].priority > processes[j+1].priority)
        		swap(&processes[j], &processes[j+1]);
}

//Function Name: initSortProcesses
//Inputs: Array of processes, mode
//Output: Void
//Logic: For sorting the processes initially.
void initSortProcesses(struct process processes[], int mode){
    for(int i=0; i < n-1; i++)
        for(int j=0; j< n-i; j++)
        	//FCFS
            if (mode==1 && processes[j].arrivalTime> processes[j+1].arrivalTime)
		    	swap(&processes[j], &processes[j+1]);
		    //SJF
		    else if(mode==2 && processes[j].arrivalTime == processes[j+1].arrivalTime)
		    	if(processes[j].burstTime > processes[j+1].burstTime) 
		      		swap(&processes[j], &processes[j+1]);
		    //PS
		    else if(mode==3 && processes[j].arrivalTime == processes[j+1].arrivalTime)
      			if(processes[j].priority > processes[j+1].priority) 
      				swap(&processes[j], &processes[j+1]);
}

//Function Name: updateProcesses
//Inputs: Array of processes
//Output: Void
//Logic: For updating the Turn Around Time and Waiting Time of processes.
void updateProcesses(struct process processes[]){
	for(int i=0; i<n; i++){
		// Turn Around Time = Completion Time - Arrival Time
	    processes[i].turnAroundTime = processes[i].completionTime - processes[i].arrivalTime;
		// Waiting Time = Turn Around Time – Burst Time
		processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;
	}
}

//Function Name: printResult
//Inputs: Array of processes, size of the array
//Output: Void
//Logic: For printing the processes in a tabular form
void printResult(struct process processes[]){
	printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
	for(int i=0; i<n; i++)
		printf("%d\t%d\t%d\t%d\t%d\t%d\n", 
			processes[i].id+1, 
			processes[i].arrivalTime, 
			processes[i].burstTime, 
			processes[i].completionTime,
			processes[i].turnAroundTime,
			processes[i].waitingTime
       );
}

//Function Name: FCFS
//Inputs: Array of processes
//Output: Void
//Logic: First Come First Serve
void FCFS(struct process processes[]){
    int totalTime = 0;
    for(int i=0; i<n; i++){
    	if (processes[i].arrivalTime > totalTime)
    		totalTime = processes[i].arrivalTime;
        totalTime += processes[i].burstTime;
        processes[i].completionTime = totalTime;
    }
    updateProcesses(processes);
    printResult(processes);
}

//Function Name: SJF_PS
//Inputs: Array of processes, mode
//Output: Void
//Logic: Shortest Job First if mode is 2, Priority Scheduling if mode=3
void SJF_PS(struct process processes[], int mode){
	initSortProcesses(processes, mode);
    int totalTime = processes[0].arrivalTime;
	processes[0].completionTime = totalTime + processes[0].burstTime;
	printResult(processes);
	for(int i=1; i<n; i++) {
		if(processes[i].arrivalTime <= processes[i-1].completionTime) {
			sortProcesses(processes, i-1, mode);
			totalTime = processes[i-1].completionTime;
		}
		else if (processes[i].arrivalTime > processes[i-1].completionTime) {
			totalTime = processes[i].arrivalTime;
		}
		processes[i].completionTime = totalTime + processes[i].burstTime;
		printResult(processes);
	}
	updateProcesses(processes);
	printResult(processes);
}

//Function Name: RR
//Inputs: Array of processes
//Output: Void
//Logic: Round Robin
void RR(struct process processes[]) {
	initSortProcesses(processes, 1);
	int tq = 0;
	printf("Time quantum: ");
	scanf("%d",&tq);
	int totalTime = 0;
	int i, j;
	int readyQueue[n];
	enqueue(0, readyQueue) ;
	for(totalTime= processes[0].arrivalTime; totalTime<totalBT;  ) {
		i = dequeue(readyQueue);
		if(processes[i].balanceTime <= tq)  {
			totalTime += processes[i].balanceTime;
  			processes[i].balanceTime = 0;
  			printf(" %d ",processes[i].id);
			processes[i].completed = 1;
			processes[i].completionTime = totalTime;          
            processes[i].waitingTime = totalTime - processes[i].arrivalTime - processes[i].burstTime;
            processes[i].turnAroundTime = totalTime - processes[i].arrivalTime;  
            totalTAT += processes[i].turnAroundTime;
			totalWT += processes[i].waitingTime;
            for(j=0;j<n;j++) {
            	if(processes[j].arrivalTime <= totalTime && processes[j].completed != 1 && readyQueueCheck(j, readyQueue) != 1) {
            		enqueue(j, readyQueue);
                }
           	}
        }
        else  {
     		totalTime += tq;
     		processes[i].balanceTime -= tq;
    		for(j=0; j<n; j++) {
        		if(processes[j].arrivalTime <= totalTime && processes[j].completed != 1 && i != j && readyQueueCheck(j, readyQueue) != 1) {
            		enqueue(j, readyQueue);
        		}
    			enqueue(i, readyQueue);
          	}
  		}
	}
	printResult(processes);
}

void main(){
	int ch = 0;
	while(ch != 5) {
		printf("CPU Scheduler\n");
		printf("1. FCFS\n2. SJF\n3. Priority\n4. Round Robin\n5. Exit\n");
		printf("Enter choice : ");
		scanf("%d", &ch);
		if (ch == 5){
			break;
		}
	    printf("Enter the no: of Processes: ");
	    scanf("%d", &n);
	    struct process processes[n];
	    for(int i=0; i<n; i++){
	        processes[i].id = i;
	        printf("Enter the Arrival and Burst Times of P%d: ", processes[i].id+1);
	        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
	        totalBT += processes[i].burstTime;
			processes[i].completionTime = 0;
			processes[i].completed = 0;
	    }
	    initSortProcesses(processes, 1);
		if(ch == 1) {
			FCFS(processes);
		}
		else if(ch == 2) {
			SJF_PS(processes, 2);
		}
		else if(ch == 3) {
			for(int i=0; i<n; i++){
		        printf("Enter the Priority of P%d: ", processes[i].id+1);
		        scanf("%d", &processes[i].priority);
		    }
			SJF_PS(processes, 3);
		}
		else if(ch==4){
			RR(processes);
		}
	}
}