// Lab 2 - Process Hierarchy 2 (print parent and child ID) 

/*
     A (Main Program)
     |
   /---\
   B    C
 /---\
 D   E

*/

#include<stdlib.h>
#include<stdio.h>
  
int main() 
{ 
        if(fork() == 0) { 
            printf("[child] pid %d from [parent] pid %d\n",getpid(),getppid()); 


              if(fork() == 0) { 
            printf("[child] pid %d from [parent] pid %d\n",getpid(),getppid()); 
            exit(0); }
            if(fork() == 0) { 
            printf("[child] pid %d from [parent] pid %d\n",getpid(),getppid()); 
            exit(0); } 
        
        if(fork() == 0) { 
            printf("[child] pid %d from [parent] pid %d\n",getpid(),getppid()); 
            }   
             exit(0);  

    } 
    wait(NULL); 
   
      
} 
