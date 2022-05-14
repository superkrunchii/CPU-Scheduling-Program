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
    int timeLength;
};

// Warning: Does not work properly when there is two the same arrival time, should try to fix this first
void sortByArrivalTime(struct Process process[], int first, int last)
{

    int i, j, pivot, temp;

    if(first < last) {
        pivot = first;
        i = first;
        j = last; 
        
        while(i < j) {
            while (process[i].arrivalTime <= process[pivot].arrivalTime && i < last)
                i++;
            while (process[j].arrivalTime > process[pivot].arrivalTime) 
                j--;

            if(i < j) {
                temp = process[i].arrivalTime;
                process[i].arrivalTime = process[j].arrivalTime;
                process[j].arrivalTime = temp;

                temp = process[i].pNo;
                process[i].pNo = process[j].pNo;
                process[j].pNo = temp;

                temp = process[i].burstTime;
                process[i].burstTime = process[j].burstTime;
                process[j].burstTime = temp;
            } 
        }

        temp = process[pivot].arrivalTime;
        process[pivot].arrivalTime = process[j].arrivalTime;
        process[j].arrivalTime = temp;

        temp = process[pivot].pNo;
        process[pivot].pNo = process[j].pNo;
        process[j].pNo = temp;

        temp = process[pivot].burstTime;
        process[pivot].burstTime = process[j].burstTime;
        process[j].burstTime = temp;

        sortByArrivalTime(process, first, j - 1);

        sortByArrivalTime(process, j + 1, last);
    }
}

void RoundRobin(int settings[], struct Process process[]) {

    int timeSlice = settings[2];
    int workingProcess = settings[1];
    int processProgress[workingProcess];
    int k , p;

    for(k = 0; k < workingProcess; k++) {
        processProgress[k] = 0;
    }

    for(k = 0; k < settings[1]; k++) {
        process[k].timeLength = 0;
        process[k].waitingTime = 0;
    }

    int i = 0;
    int j = 0;
    int currentTime = 0;
    sortByArrivalTime(process, 0 , settings[1] - 1);

    
    //Check if Sorted Properly
    for(int i = 0; i < settings[1]; i++) {
        printf("%d %d %d\n" , process[i].pNo, process[i].arrivalTime, process[i].burstTime); 
    }
    
   
   while(workingProcess != 0) {
       
       for(i = 0; i < settings[1]; i++) {

           if(processProgress[i] == 0) {
               process[i].startTime[j] = currentTime;
               process[i].waitingTime += currentTime;
               if (timeSlice < process[i].burstTime){
                   currentTime += timeSlice;
                   process[i].burstTime -= timeSlice;
                   process[i].endTime[j] = currentTime;
                   process[i].timeLength += 1;
               } else {
                   currentTime += process[i].burstTime;
                   process[i].endTime[j] = currentTime;
                   process[i].burstTime = 0;
                   processProgress[i] = 1;
                   workingProcess -= 1;
                   process[i].timeLength += 1;
               }
           }

       }

        j++;

   }
   int totalWTime = 0;
   for(k = 0; k < settings[1]; k++) {

       for(int p = 0; p < process[k].timeLength; p++) {

           if(p == 0) {
               printf("P[%d] Start Time: %d End time: %d |", process[k].pNo, process[k].startTime[p], process[k].endTime[p]);
           } else {
               printf(" Start Time: %d End time: %d |", process[k].startTime[p], process[k].endTime[p]);
               process[k].waitingTime = process[k].startTime[0];
               for(int m = 0; m < process[k].timeLength - 1; m++) {
                   process[k].waitingTime += process[k].startTime[m + 1] - process[k].endTime[m];
               }
           }

           if(p == process[k].timeLength - 1) {
               printf(" Waiting time: %d\n" , process[k].waitingTime);
               totalWTime += process[k].waitingTime;
           }
       }

       if(k == settings[1] - 1) {
           float ave = (float) totalWTime / settings[1];

           printf("Average waiting time: %.1f", ave);
       }
   }






 }

void SRTF(int settings[], struct Process process[]){


}

int main() {

    char filename[50];
    char test[4];
    char temp[4];
    int settings[3];
    int i;

    printf("Enter filename: ");

    scanf("%s" , filename);
    FILE *f = fopen(strcat(filename , ".txt") , "r");

    if(f == NULL) {
        perror("File does not exist");

    } else {

        fscanf(f, "%d %d %d", &settings[0], &settings[1], &settings[2]);

        printf("%d %d %d\n", settings[0], settings[1], settings[2]);

        struct Process process[settings[1]];

        for(i = 0; i < settings[1]; i++) {

            fscanf(f, "%d %d %d", &process[i].pNo, &process[i].arrivalTime, &process[i].burstTime);

            //printf("%d %d %d\n", process[i].pNo, process[i].arrivalTime, process[i].burstTime);
        }

        if(settings[0] == 0) {
            
        } else if(settings[0] == 1) {

        } else if(settings[0] == 2) {
            SRTF(settings, process);
        } else if(settings[0] == 3) {
            RoundRobin(settings, process);
        }



        

    }
    
    fclose(f);
    

    return 0;
}