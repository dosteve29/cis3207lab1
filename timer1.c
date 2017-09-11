#include <stdio.h> //library for basic operation
#include <unistd.h> //library for pid
#include <sys/types.h> 
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h> //library for time
#include <stdlib.h> //exit()

int main(void){
    pid_t childPID; 

    //getting time
    struct timeval time1;
    gettimeofday(&time1, NULL);
    long time_record = (long) time1.tv_usec;

    //writing time to file
    FILE * time; //file pointer to time1.txt
    if ((time = fopen("time1.txt", "a+")) == NULL){ //if file pointer fails to open
        puts("Failed creating/opening the file");
        exit(1);
    }
    fprintf(time, "%d", time_record); //print the time_record before fork() to time1.txt
    fclose(time); //ALWAYS CLOSE FILE POINTER

    //CREATE NEW PROCESS
    childPID = fork();
    if (childPID >= 0){ //fork success
        if (childPID == 0){ //child process
            char *args[] = {"./app", NULL}; //create the argument string
            execvp(args[0], args); //first argument is app name 
        }
        else{ //parent process
            waitpid(childPID,NULL,0);
        }
    }
    else{ //fork failed
        printf("\n Fork failed, quitting!\n");
        return 1;
    }
    return 0;
}
