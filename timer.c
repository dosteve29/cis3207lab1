#include <stdio.h> //library for basic operation
#include <unistd.h> //library for pid
#include <sys/types.h> 
#include <sys/wait.h>
#include <time.h> //library for time

void application(int n);

int main(void){
    pid_t childPID;
    clock_t cstart = clock();
    clock_t cend = 0;
    childPID = fork();
    if (childPID >= 0){ //fork success
        if (childPID == 0){ //child process
            char *args[] = {"./app", "Hello", NULL};
            execvp(args[0], args);
        }
        else{ //parent process
            waitpid(childPID,0,0);
        }
    }
    else{ //fork failed
        printf("\n Fork failed, quitting!\n");
        return 1;
    }
    return 0;
}

//The first program to be made.
//n is the number of iterations
void application(int n){
    
}
