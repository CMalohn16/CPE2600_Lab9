/**
* File: finfo.c
* Author: Charlie Malohn
* Data: 11/7/2026
* Class: CPE2600 - 121
* Brief: 
* Compile with makefile
*/

#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define SECONDS_PER_DAY 86400

void format_timespec(const struct timespec *ts, char *buffer, size_t buf_size);


int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("No file provided. Please specify a file when running\n");
        return 0;
    }

    char *path = argv[1];
    struct stat statBuffer;

    if (stat(path, &statBuffer) != 0)
    {
        printf("Invalid file\n");
        return 0;
    }

    int mode = statBuffer.st_mode;

    printf("\nFile type: ");
    if (S_ISDIR(mode))
    {
        printf("Directory\n");
    }
    else if (S_ISCHR(mode))
    {
        printf("Character device\n");
    }
    else if (S_ISBLK(mode))
    {
        printf("Block device\n");
    }
    else if (S_ISFIFO(mode))
    {
        printf("Named pipe\n");
    }
    else if (S_ISLNK(mode))
    {
        printf("Symbolic link\n");
    }
    else if (S_ISSOCK(mode))
    {
        printf("Socket\n");
    }
    else if (S_ISREG(mode)) 
    {
        printf("Regular\n");
    } 
    else
    {
        printf("Unrecognized");
    }


    printf("\nFile Permissions (1 for yes, 0 for no)\n");

    printf("Owner can:\n  Read: %d\n  Write: %d\n  Execute: %d\n", 
        (bool)(mode & S_IRUSR), (bool)(mode & S_IWUSR), (bool)(mode & S_IXUSR));
    printf("Group can:\n  Read: %d\n  Write: %d\n  Execute: %d\n", 
        (bool)(mode & S_IRGRP), (bool)(mode & S_IWGRP), (bool)(mode & S_IXGRP));
    printf("Others can:\n  Read: %d\n  Write: %d\n  Execute: %d\n", 
        (bool)(mode & S_IROTH), (bool)(mode & S_IWOTH), (bool)(mode & S_IXOTH));

    printf("\nOwner ID: %d\n", statBuffer.st_uid);

    printf("\nSize: %ld bytes\n", statBuffer.st_size);

    struct timespec modTime = statBuffer.st_mtim;

    char formatted[80];
    format_timespec(&modTime, formatted, sizeof(formatted));

    printf("\nLast Modified: %s\n", formatted);
    return 0;

}   


/**
* @brief Converts timespec into a readable string
* @param timespec Time to convert
* @param buffer String to store the result 
* @param buf_size Size of result buffer
*/
void format_timespec(const struct timespec *ts, char *buffer, size_t buf_size) {
    struct tm tm_info;

    // Convert seconds to local time (use gmtime() for UTC)
    localtime_r(&ts->tv_sec, &tm_info);

    char datetime[64];
    if (strftime(datetime, sizeof(datetime), "%Y-%m-%d %H:%M:%S", &tm_info) == 0) {
        snprintf(buffer, buf_size, "Error Formatting Time");
        exit(0);
    }

    // Append nanoseconds
    snprintf(buffer, buf_size, "%s.%09ld", datetime, ts->tv_nsec);
}

