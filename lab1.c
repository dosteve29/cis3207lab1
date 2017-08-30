#include <stdio.h> //library for basic operation
#include <unistd.h> //library for pid
#include <time.h> //library for time

int var_glb = 0;
int main(void){
    pid_t childPID;
    int var_lcl = 0;
    childPID = fork();
    if (childPID >= 0){ //fork success
        if (childPID == 0){ //child process
            var_lcl++;
            var_glb++;
        }
        else{ //parent process
            var_lcl = 10;
            var_glb = 20;
        }
    }
    else{ //fork failed
        printf("\n Fork failed, quitting!\n");
        return 1;
    }
    return 0;
}
