/* Lab 2 -  Write two C programs: 
(i) to find the factorial of the given number and 
(ii) to determine whether a number is prime or not. 
Write a third program to create a process hierarchy as shown below : 

     A (Main Program)
     |
   /---\
   B    C

*/


#include <sys/types.h>      
#include <sys/wait.h>      
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>        

int main()
{
 pid_t pid;
 pid = fork(); // Create process
  
 if (pid < 0)
  {
   printf("A fork error has occurred.\n");
   exit(-1);
  }
 else 
  if (pid == 0) 
   {
    printf("Child process 1 - Factorial.\n");
    execlp("gcc -o factorial factorial.c","factorial.c",(char *) 0); // Call external program
    execlp("./factorial","factorial",(char *) 0);
    

    printf("The call to execlp() was not successful.\n");
    exit(127);
   }

  pid = fork();

    if (pid == 0) 
   {   
    printf("Child process 2 - Prime\n");
    execlp("gcc -o prime prime.c","prime.c",(char *) 0);
    execlp("./prime","prime",(char *) 0);

    printf("The call to execlp() was not successful.\n");
    exit(127);
  }
  else  
   {
    wait(0);              
    printf("Child Process Ended.\n");
    exit(0);
   }

 return(0);  
}
