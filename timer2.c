#include <stdio.h> //library for basic operation
#include <unistd.h> //library for pid
#include <sys/wait.h>
#include <sys/time.h>
#include <stdlib.h>

//function prototype
char * time_start(char buff[], int time);

int main(void){
    char timedata1[7];
    char timedata2[7];
    //getting time
    struct timeval time1;
    struct timeval time2;
    gettimeofday(&time1, NULL);
    
    //CREATE NEW PROCESS
    pid_t child1 = fork();
    if (child1 >= 0){ //fork success
        if (child1 == 0){ //child1 process
            execlp("./app", time_start(timedata1, (int) time1.tv_usec), NULL); 
        }
        else{ //parent process
            //get the time before fork
            gettimeofday(&time2, NULL);

            pid_t child2 = fork();
            if (child2 == 0){
                execlp("./app", time_start(timedata2, (int) time2.tv_usec), NULL);
            }
            else{ //parent process
                waitpid(child1, NULL, 0);
                waitpid(child2, NULL, 0);
                //remove the time between first fork and first application
                char unnecessarytimedata1name[20];
                sprintf(unnecessarytimedata1name, "%dtime.txt", child1);
                int retval = remove(unnecessarytimedata1name);
            }
        }
    }
    else{ //fork failed
        printf("\n Fork failed, quitting!\n");
        exit(1);
    }

    return 0;
}

char * time_start(char * buff, int time){
    sprintf(buff, "%d", time);
    return buff;
}
