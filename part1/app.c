#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/time.h>
#include <string.h>

int main(int argc, char *argv[]){
    printf("Running Application! PID: %d\n", getpid());
    //get time
    struct timeval time2;
    gettimeofday(&time2, NULL);
    long time_record2 = (long) time2.tv_usec;

    //same time_filename from timer1.c
    char time_filename[20];
    sprintf(time_filename, "%dtime.txt", getppid()); //uses parent pid to use same filename

    //write time
    FILE * timeptr;
    if ((timeptr = fopen(time_filename, "a+")) == NULL){ //open in append not to overwrite
        puts("Failed creating/opening the file.");
        exit(1);
    }
    fprintf(timeptr, "%d", time_record2); //record time of executing the application
    fclose(timeptr);  

    printf("End Timer!\n");

    //data filename creation
    char filename[20];
    sprintf(filename, "%d.txt", getpid());

    //get random time seed before iteration
    srand(time(NULL)); 
    int i;
    //begin iteration
    for (i = 0; i < 1000000; i++){ 
        //create file
        FILE * fp;
        if ((fp = fopen(filename, "w+")) == NULL){ //empty file each pass
            puts("Failed creating/opening the file.");
            exit(1);
        }

        /* printf("%s\n", filename); */

        //write content to memory
        char records[10][121]; //10 records of 120 random alphanumeric char + null terminator
        int j, k;
        for (j = 0; j < 10; j++){ //number of records
            for (k = 0; k < 120; k++){
                int random_char = (rand() % 75) + 48; //ASCII range from 0 to z
                while (!isalnum(random_char)){ //filter non-alphanumeric char
                    random_char = (rand() % 75) + 48; //loop until alphanumeric
                }
                records[j][k] = (char) random_char; //fill the record table
            }
            records[j][120] = '\0'; //end string with null terminating char
        } //finished building records to memory

        //write records to file
        for (j = 0; j < 10; j++){
            fwrite(records[j], sizeof(char), 120, fp); //writes the current record, specify size of char, 120 char, FILE pointer
        } //this does not write the line terminator in the .txt file

        //select a random record
        int random_record = rand() % 10; //from record 0 to record 9 (total 10 records)
        fseek(fp, 120 * random_record, SEEK_SET); 
        char buffer[120]; //create buffer to read from file
        fread(buffer, sizeof(char), 120, fp); //read from file to buffer
        int retval = strcmp(buffer, records[random_record]); //compare buffer and record
        /* if (retval == 0) */
        /*     printf("They're the same!\n"); */
        /* else */
        /*     printf("They're not the same!\n"); */

        /* printf("%d\n", random_record); */
        /* printf("%s\n", buffer); */
        /* printf("%s\n", records[random_record]); */

        //reset to the beginning of the file
        fseek(fp, 0, SEEK_SET);

        //always close file pointer
        fclose(fp);
    } //end iteration

    //delete the data file
    int ret = remove(filename);
    /* if (ret == 0) */
    /*     printf("removed data file successfully.\n"); */
    /* else */
    /*     printf("Error in deleting the data file.\n"); */
    printf("Terminating Application!\n");
    return 0;
}
