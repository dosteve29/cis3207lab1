#include <stdio.h> //library for basic operation
#include <unistd.h> //library for pid
#include <sys/types.h> 
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h> //library for time
#include <stdlib.h> //exit()

int main(void){
    pid_t childPID; 

    printf("Running Timer1! PID: %d\n", getpid());
    printf("Start Timer!\n");
    //getting time
    struct timeval time1;
    gettimeofday(&time1, NULL);
    long time_record = (long) time1.tv_usec;

    char time_filename[20];
    sprintf(time_filename, "%dtime2.txt", getpid());

    //writing time to file
    FILE * time; //file pointer to time1.txt
    if ((time = fopen(time_filename, "a+")) == NULL){ //if file pointer fails to open
        puts("Failed creating/opening the file");
        exit(1);
    }
    fprintf(time, "%d", time_record); //print the time_record before fork() to time.txt
    fclose(time); //ALWAYS CLOSE FILE POINTER

    //CREATE NEW PROCESS
    childPID = fork();
    if (childPID >= 0){ //fork success
        if (childPID == 0){ //child process
            printf("Fork Complete!\n");
            char *args[] = {"./app", time_filename, NULL}; //create the argument string
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
    printf("Terminating Timer1!\n");
    return 0;
}
