// Lab 4 - Scheduling and Context Switching with Gannt Chart using C
/*
 Process    BurstTime
   P1         21
   P2         14
   P3         5
   P4         7
   P5         29
   
 Print scheduling, waiting time, turn-around time with a Gannt chart varying the time quantum from 3ms to 6ms. */
 
 
#include<stdio.h>
#include<float.h>
float turnaroundtime(int n,int bt[][2],int wt[],int tt[]){
float avg=0;
for(int i=0;i<n;i++){
  tt[i]=wt[i]+bt[i][1];
  avg+=tt[i];
  }
return avg;
}

int main(){
  int n;
  printf("Enter the no. of processes: ");
  scanf("%d",&n);
  int bt[n][2],temp[n][2],wt[n],tt[n];
  double avg_waiting[4],avg_turnaround[4];
  for(int i=0;i<n;i++){
    printf("Enter process no: ");
    scanf("%d",&bt[i][0]);
    printf("Enter burst time: ");
    scanf("%d",&bt[i][1]);
    temp[i][0]=bt[i][0];
    temp[i][1]=bt[i][1];
  }
  for(int q=3;q<=6;q++){
    int start=0,flag=0,cont_switch=0;
    printf("\nTime quantum:%d \n\nGantt chart:\n\n%d ",q,start);
    while(flag!=n){
      for(int i=0;i<n;i++){
      if(bt[i][1]>0 && bt[i][1]<=q){
        wt[i]=start-temp[i][1]+bt[i][1];
        start+=bt[i][1];
        printf("<--- p%d ---> %d ",i+1,start);
        bt[i][1]=0;
        flag++;
        cont_switch++;
        }
      else if(bt[i][1]>q){
        start+=q;
        printf("<--- p%d ---> %d ",i+1,start);
        bt[i][1]-=q;
        cont_switch++;
        }
      }
    }
  printf("\n\n");
  for(int i=0;i<n;i++){
    bt[i][0]=temp[i][0];
    bt[i][1]=temp[i][1];
    avg_waiting[q-3]+=wt[i];
    }
  avg_turnaround[q-3]=turnaroundtime(n,bt,wt,tt)/n;
  avg_waiting[q-3]=avg_waiting[q-3]/n;
  printf("p.no BurstTime WaitingTime TurnaroundTime\n");
  for(int i=0;i<n;i++){
    printf("%4d %9d %10d %14d\n\n",bt[i][0],bt[i][1],wt[i],tt[i]);
    printf("Average waiting time: %.2f ms\n",avg_waiting[q-3]);
    printf("Average turnaround time: %.2f ms\n",avg_turnaround[q-3]);
    printf("Number of context switches for time quantum %d ms : %d\n\n",q,cont_switch-1);
    printf("\n");
    }
  double min_time=100000;
  int flag=0;
  for(int i=0;i<4;i++){
    if(min_time>avg_waiting[i]){
      min_time=avg_waiting[i];
      flag=i+3;
      }
    }
  printf("The optimal quantum for the given case is %d with average waiting time %.2f ms and average turnaround time %.2f ms
  \n",flag,avg_waiting[flag-3],avg_turnaround[flag-3]);
  return 0;
  }
