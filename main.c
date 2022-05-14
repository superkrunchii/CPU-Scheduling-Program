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

void sortByBurstTime(struct Process process[] , int settings[])
{
    int i, j , min, temp;

    for(i = 0; i < settings[1] - 1; i++) {
        min = i;

        for(j = i + 1; j < settings[1]; j++) {
            if(process[j].burstTime < process[min].burstTime) 
                min = j;
        }

        temp = process[min].arrivalTime;
        process[min].arrivalTime = process[i].arrivalTime;
        process[i].arrivalTime = temp;

        temp = process[min].pNo;
        process[min].pNo = process[i].pNo;
        process[i].pNo = temp;

        temp = process[min].burstTime;
        process[min].burstTime = process[i].burstTime;
        process[i].burstTime = temp;

        temp = process[min].timeLength;
        process[min].timeLength = process[i].timeLength;
        process[i].timeLength = temp;

        temp = process[min].waitingTime;
        process[min].waitingTime = process[i].waitingTime;
        process[i].waitingTime = temp;

        for(int l = 0; l < settings[1]; l++) {
            temp = process[min].endTime[l];
            process[min].endTime[l] = process[i].endTime[l];
            process[i].endTime[l] = temp;
        }

        for(int l = 0; l < settings[1]; l++) {
            temp = process[min].startTime[l];
            process[min].startTime[l] = process[i].startTime[l];
            process[i].startTime[l] = temp;
        }
        
    }

}

void sortByArrivalTime(struct Process process[], int settings[])
{

    int i, j, min, temp;

    for (i = 0; i < settings[1] - 1; i++)
    {
        min = i;

        for (j = i + 1; j < settings[1]; j++)
        {
            if (process[j].arrivalTime < process[min].arrivalTime)
                min = j;
        }

        temp = process[min].arrivalTime;
        process[min].arrivalTime = process[i].arrivalTime;
        process[i].arrivalTime = temp;

        temp = process[min].pNo;
        process[min].pNo = process[i].pNo;
        process[i].pNo = temp;

        temp = process[min].burstTime;
        process[min].burstTime = process[i].burstTime;
        process[i].burstTime = temp;

        temp = process[min].timeLength;
        process[min].timeLength = process[i].timeLength;
        process[i].timeLength = temp;

        temp = process[min].waitingTime;
        process[min].waitingTime = process[i].waitingTime;
        process[i].waitingTime = temp;

        for(int l = 0; l < settings[1]; l++) {
            temp = process[min].endTime[l];
            process[min].endTime[l] = process[i].endTime[l];
            process[i].endTime[l] = temp;
        }

        for(int l = 0; l < settings[1]; l++) {
            temp = process[min].startTime[l];
            process[min].startTime[l] = process[i].startTime[l];
            process[i].startTime[l] = temp;
        }
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
    sortByArrivalTime(process, settings);

    
    //Check if Sorted Properly
    for(int i = 0; i < settings[1]; i++) {
        printf("%d %d %d\n" , process[i].pNo, process[i].arrivalTime, process[i].burstTime); 
    }
    
   
   while(workingProcess != 0) {
       
       for(i = 0; i < settings[1]; i++) {

           if(processProgress[i] == 0) {
               process[i].startTime[j] = currentTime;
               process[i].waitingTime += currentTime - process[i].arrivalTime;
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

    int workingProcess = settings[1];
    int processProgress[workingProcess];
    int i, k;
    int currentTime = 0;

    for (k = 0; k < workingProcess; k++)
    {
        processProgress[k] = 0;
    }

    for (k = 0; k < settings[1]; k++)
    {
        process[k].timeLength = 0;
        process[k].waitingTime = 0;
    }

    sortByArrivalTime(process, settings);
    sortByBurstTime(process, settings);
    
    // Check if sorted properly
    for(i = 0; i < settings[1]; i++) {
        printf("%d %d %d\n" , process[i].pNo, process[i].arrivalTime, process[i].burstTime); 
    }

    int firstArrIndex = 0;
    int firstArr = process[0].arrivalTime;

    // Do preemptive stuff
    for (i = 0; i < settings[1]; i++)
    {
        if(process[i].arrivalTime < firstArr) {
            firstArrIndex = i;
            firstArr = process[i].arrivalTime;
        }
    }

    process[firstArrIndex].burstTime -= process[0].arrivalTime;
    process[firstArrIndex].startTime[0] = process[firstArrIndex].arrivalTime;
    currentTime += process[0].arrivalTime;
    process[firstArrIndex].endTime[0] = currentTime;
    process[firstArrIndex].timeLength += 1;
    process[firstArrIndex].waitingTime += process[firstArrIndex].arrivalTime;

    sortByArrivalTime(process, settings);
    sortByBurstTime(process, settings);
    printf("\n");

    // Check if sorted properly
    for (i = 0; i < settings[1]; i++)
    {   
        printf("%d %d %d\n", process[i].pNo, process[i].arrivalTime, process[i].burstTime);
    }

    firstArr = process[0].arrivalTime;

    for (i = 0; i < settings[1]; i++)
    {
        if (process[i].arrivalTime < firstArr)
        {
            firstArrIndex = i;
            firstArr = process[i].arrivalTime;
        }
    }
    
    while(workingProcess != 0) {

        for(i = 0; i < settings[1]; i++) {

            if(i == firstArrIndex) {
                process[i].startTime[1] = currentTime;
                process[i].waitingTime += currentTime;
                currentTime += process[i].burstTime;
                process[i].endTime[1] = currentTime;
                workingProcess -= 1;
                process[i].timeLength += 1;
            } else {
                process[i].startTime[0] = currentTime;
                process[i].waitingTime += currentTime - process[i].arrivalTime;
                currentTime += process[i].burstTime;
                process[i].endTime[0] = currentTime;
                workingProcess -= 1;
                process[i].timeLength += 1;
            }

        }

    }

    int totalWTime = 0;
    for (k = 0; k < settings[1]; k++)
    {

        for (int p = 0; p < process[k].timeLength; p++)
        {

            if (p == 0)
            {
                printf("P[%d] Start Time: %d End time: %d |", process[k].pNo, process[k].startTime[p], process[k].endTime[p]);
            }
            else
            {
                printf(" Start Time: %d End time: %d |", process[k].startTime[p], process[k].endTime[p]);
                process[k].waitingTime = process[k].startTime[0];
                for (int m = 0; m < process[k].timeLength - 1; m++)
                {
                    process[k].waitingTime += process[k].startTime[m + 1] - process[k].endTime[m];
                }
            }

            if (p == process[k].timeLength - 1)
            {
                printf(" Waiting time: %d\n", process[k].waitingTime);
                totalWTime += process[k].waitingTime;
            }
        }

        if (k == settings[1] - 1)
        {
            float ave = (float)totalWTime / settings[1];

            printf("Average waiting time: %.1f", ave);
        }
    }
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