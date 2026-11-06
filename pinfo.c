/**
* File: info.c
* Author: Charlie Malohn
* Data: 11/6/2026
* Brief: Prints out information about a specified process
* Compile with makefile
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <ctype.h>

int main(int argc, char* argv[])
{

    int pid;
    if (argc <= 1) 
    {
        pid = getpid();
    }
    else
    {
        for (int i = 0; argv[1][i] != '\0'; i++)
        {
            if (!isdigit((unsigned char)argv[1][i]))
            {
                printf("Invalid Process ID\n");
                exit(1);
            }
        }
        pid = atoi(argv[1]);
    }

    printf("Process ID: %d\n", pid);
    printf("Priority: %d\n", getpriority(pid, PRIO_PROCESS));

    //Scheduling Method
    int schedVal = sched_getscheduler(pid);
    char *schedStr;

    switch (schedVal) {
        case SCHED_OTHER:
            schedStr = "Other/Default\0";
            break;
        case SCHED_BATCH:
            schedStr = "Batch\0";
            break;
        case SCHED_IDLE:
            schedStr = "Idle\0";
            break;
        case SCHED_FIFO:
            schedStr = "FIFO\0";
            break;
        case SCHED_RR:
            schedStr = "Round Robin\0";
            break;
        default:
            schedStr = "Unknown\0";

    }

    printf("Scheduling Method: %s\n", schedStr);

    return 0;
}   