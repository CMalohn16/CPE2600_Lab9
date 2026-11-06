/**
* File: info.c
* Author: Charlie Malohn
* Data: 11/4/2026
* Brief: Prints out system information
* Compile: $ gcc -Wall info.c -o info
*/

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>

#define SECONDS_PER_DAY 86400

int main(int argc, char* argv[])
{
    struct timespec time;
    clock_gettime(CLOCK_REALTIME, &time);
    double timeVal = time.tv_sec - (time.tv_nsec / 10e9);
    
    //Remove full days from the time so it only applies to today
    int days = timeVal / (SECONDS_PER_DAY);
    timeVal = timeVal - days * SECONDS_PER_DAY;

    timeVal = timeVal - 60 * 60 * 6; //6 hour offset

    printf("Time: %ldns\n", (long int)(timeVal * 10e9));

    struct utsname sysinfo;

    // Call uname() and check for errors
    if (uname(&sysinfo) != 0) {
        perror("uname failed");
        return 1;
    }

    //OS information
    char *name = sysinfo.sysname;
    char *host = sysinfo.nodename;
    char *release = sysinfo.release;
    char *version = sysinfo.version;
    char *machine = sysinfo.machine;
    
    if (name) 
    {
        printf("Operating System Name: %s\n", name);   // e.g. "Linux"
    }

    if (host) 
    {
        printf("Hostname: %s\n", host);
    }

    if (release) 
    {
        printf("OS Release: %s\n", release);    
    }

    if (version) 
    {
        printf("OS Version: %s\n", version);
    }

    if (machine) 
    {
        printf("Hardware: %s\n", machine); 
    }

    if (get_nprocs())
    {
        printf("System has %d CPUs\n", get_nprocs());
    }

    // Get number of physical pages
    long pages = sysconf(_SC_PHYS_PAGES);
    if (pages == -1) {
        perror("sysconf(_SC_PHYS_PAGES) failed");
        return 1;
    }
    // Get size of each page in bytes
    long page_size = sysconf(_SC_PAGE_SIZE);
    if (page_size == -1) {
        perror("sysconf(_SC_PAGE_SIZE) failed");
        return 1;
    }

    unsigned long long total_mem = (unsigned long long) pages * (unsigned long long) page_size;
    printf("Total physical memory: %llu bytes\n", total_mem);

    return 0;
}
