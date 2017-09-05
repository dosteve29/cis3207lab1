#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]){
    /* PUT END CLOCK HERE ON THE FIRST LINE OF THE APPLICATION */
    int i;
    for (i = 0; i < 1; i++){
        //create file
        char filename[20];
        sprintf(filename, "%d.txt", getpid()); //formatted string to get unique filename
        FILE * fp = fopen(filename, "a+");

        //write content to memory
        char records[10][121]; //10 records of 120 random alphanumeric char
        int j, k;
        for (j = 0; j < 10; j++){ //number of records
            srand(time(NULL)); //the random seed is refreshed for each record
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
            fwrite(records[j], sizeof(char), 120, fp); //writes the current reocrd, specify size of char, 120 char, FILE pointer
        }

        //always close file pointer
        fclose(fp);
    }
    return 0;
}
