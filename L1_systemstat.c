// Lab 1 - Print System Statistics 

#include <stdio.h>
#include <sys/sysinfo.h> // Sys Stats
#include<sys/utsname.h>  //Sys Info

int main ()
{
 const long minute = 60;
 const long hour = minute * 60;
 const long day = hour * 24;
 const double megabyte = 1024 * 1024;
 
 // System Stats 
 struct sysinfo si;
 sysinfo (&si);
 
 printf ("system uptime : %ld days, %ld:%02ld:%02ld\n", si.uptime / day, (si.uptime % day) / hour, (si.uptime % hour) / minute, si.uptime % minute);
 printf ("total RAM   : %5.1f MB\n", si.totalram / megabyte);
 printf ("free RAM   : %5.1f MB\n", si.freeram / megabyte);
 printf ("process count : %d\n", si.procs);
 
 // System info
 struct utsname uname_pointer;

 uname(&uname_pointer);

 printf("System name - %s \n", uname_pointer.sysname);
 printf("Nodename    - %s \n", uname_pointer.nodename);
 printf("Release     - %s \n", uname_pointer.release);
 printf("Version     - %s \n", uname_pointer.version);
 printf("Machine     - %s \n", uname_pointer.machine);
 printf("Domain name - %s \n", uname_pointer.__domainname);
 return 0;
}
