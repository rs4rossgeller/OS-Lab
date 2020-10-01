// Lab 2 - Process Hierarchy 1 (print parent and child ID) 
/*
     A (Main Program)
     |
   /---\
   B    C
*/

#include<stdlib.h>
#include<stdio.h> 

  
  
int main() 
{ 
    for(int i=0;i<2;i++)  
    { 
        if(fork() == 0) 
        { 
            printf("[child] pid %d from [parent] pid %d\n",getpid(),getppid()); 
            exit(0); 
        } 
    } 
    for(int i=0;i<2;i++) 
    wait(NULL); 
      
} 
