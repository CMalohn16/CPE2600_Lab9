/**
* File: pmod.c
* Author: Charlie Malohn
* Data: 11/7/2026
* Class: CPE2600 - 121
* Brief: Reduces the priority of its process, waits, then exits
* Compile with makefile
*/

#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char* argv[])
{

    printf("Starting pmod program\n");

    //Adding 10 to the niceness will REDUCE the priority:
    //The higher the number, the lower the priority
    nice(10);

    struct timespec delay;
    // 1,837,272,638 ns
    delay.tv_sec = 1;
    delay.tv_nsec = 837272638;

    nanosleep(&delay, NULL);

    printf("Exiting pmod program\n");

    return 0;

}   