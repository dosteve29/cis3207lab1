/* 
 * Timer1 program only requires one fork().
 * There is no statements between gettimeofday and execlp.
 * The parent process waits while the child process executes.
 * timedata1 array is important to be declared before gettimeofday
 * in order not to disrupt the startup time.
 *
 * */
#include <stdio.h> //library for basic operation
#include <unistd.h> //library for pid
#include <sys/wait.h>
#include <sys/time.h>
#include <stdlib.h> //exit()

//function prototype
char * time_start(char buff[], int time);

int main(void){
    pid_t childPID; 
    char timedata1[7];
    //getting time
    struct timeval time1;
    gettimeofday(&time1, NULL);

    //CREATE NEW PROCESS
    childPID = fork();
    if (childPID >= 0){ //fork success
        if (childPID == 0){ //child process
            execlp("./app", time_start(timedata1, (int) time1.tv_usec), NULL);
        }
        else{ //parent process
            waitpid(childPID,NULL,0);
        }
    }
    else{ //fork failed
        printf("\n Fork failed, quitting!\n");
        exit(1);
    }
    return 0;
}

/*
 * Purpose: a helper function to return a pointer to a string with the start up time
 * Input: pointer to the empty buffer in the main function, time of the start up time
 * Output: pointer to buffer with time printed now
 */
char * time_start(char * buff, int time){
    sprintf(buff, "%d", time);
    return buff;
}
