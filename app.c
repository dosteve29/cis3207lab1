#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/time.h>
#include <string.h>

int main(int argc, char *argv[]){
    struct timeval time2;
    gettimeofday(&time2, NULL);
    int time_jawn2 = (int) time2.tv_sec;
    
    FILE * timeptr = fopen("time1.txt", "a+");
    fprintf(timeptr, "%d", time_jawn2);
    fclose(timeptr);  

    //get random time seed before iteration
    srand(time(NULL)); 
    int i;
    //begin iteration
    for (i = 0; i < 1; i++){
        //create file
        char filename[20];
        sprintf(filename, "%d.txt", getpid()); //formatted string to get unique filename
        FILE * fp = fopen(filename, "a+"); //create the file

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
        srand(time(NULL)); //refresh seed again
        int random_record = rand() % 10; //from record 0 to record 9 (total 10 records)
        fseek(fp, 120 * random_record, SEEK_SET);
        char buffer[120];
        fread(buffer, sizeof(char), 120, fp);
        int retval = strcmp(buffer, records[random_record]);
        if (retval == 0)
            printf("They're the same!\n");
        else
            printf("They're not the same!\n");

        printf("%s\n", buffer);
        printf("%s\n", records[random_record]);

        //always close file pointer
        fclose(fp);
    }
    return 0;
}
