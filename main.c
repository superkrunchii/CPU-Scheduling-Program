#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Process {
    int pNo;
    int startTime[99];
    int endTime[99];
    int arrivalTime;
    int burstTime;
    int waitingTime;
};


void sortByArrivalTime(int settings[] , int tasks[][2]) {
    
    
    


} 


void RoundRobin(int settings[], struct Process process[]) {

    int timeSlice = settings[2];
    

}

void SRTF(int settings[], struct Process process[]){

    
}

int main() {

    char filename[50];
    char test[2];
    int settings[2];
    int i;

    printf("Enter filename: ");

    scanf("%s" , filename);
    FILE *f = fopen(strcat(filename , ".txt") , "r");

    if(f == NULL) {
        perror("File does not exist");

    } else {

        fgets(test, 2, f); // X (Algorithm)
        settings[0] = atoi(test);

        fgets(test, 3, f); // Y (Number of Process)
        settings[1] = atoi(test);

        fgets(test, 3, f); // Z (Time Slice) Set to 1 If not RR
        settings[2] = atoi(test);

        printf("%d %d %d\n", settings[0], settings[1], settings[2]);

        struct Process process[settings[1]];

        fgets(test, 3, f); // Remove Extra Spaces

        for(i = 0; i < settings[1]; i++) {

            fgets(test, 2, f);

            process[i].pNo = atoi(test);

            fgets(test, 3, f);

            process[i].arrivalTime = atoi(test);

            fgets(test, 3, f);

            process[i].burstTime = atoi(test);

            fgets(test, 3, f); // Remove Extra Spaces

            printf("%d %d %d\n", process[i].pNo, process[i].arrivalTime, process[i].burstTime);
        }

        if(settings[0] == 1) {
            
        } else if(settings[0] == 2) {

        } else if(settings[0] == 3) {
            SRTF(settings, process);
        } else if(settings[0] == 4) {
            RoundRobin(settings, process);
        }



        

    }
    
    fclose(f);
    

    return 0;
}