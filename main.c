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

struct tempProcess {
	int pNo;
	int waitTime;
    int startTime[99];
    int endTime[99];
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

void FCFS(int settings[], struct Process process[]) {
    int k;
    int currentTime = 0;
    int totalwaitTime = 0;

    for(k = 0; k < settings[1]; k++) {
        process[k].waitingTime = 0;
    }

    int i;
    for(i = 0; i < settings[1]; i++) {
        process[i].startTime[0] = currentTime;
        process[i].waitingTime += currentTime - process[i].arrivalTime;
        currentTime += process[i].burstTime;
        process[i].endTime[0] = currentTime;
        printf("P[%i] Start Time: %i End time: %i |", process[i].pNo, process[i].startTime[0], process[i].endTime[0]);
        printf(" Waiting time: %i\n" , process[i].waitingTime);
        totalwaitTime += process[i].waitingTime;
    }

    float ave = (float) totalwaitTime / settings[1];
    printf("Average waiting time: %.1f", ave);
}

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void SJF(int settings[], struct Process process[]) {
    int j, k, p;
    int currentTime = 0;
    int totalWTime = 0;
    int x = 1000;

    for (k = 0; k < settings[1]; k++)
    {
        process[k].waitingTime = 0;
    }

    int i = 0;
    sortByArrivalTime(process, settings);

    process[0].endTime[0] = process[0].arrivalTime + process[0].burstTime;
    currentTime += process[0].endTime[0];
    for (i = 1; i < settings[1]; i++)
    {
        for (j = i; j < settings[1]; j++)
        {
            if (process[j].arrivalTime <= process[i - 1].endTime[0])
            {
                if (process[j].burstTime < x)
                {
                    x = process[j].burstTime;
                    p = j;
                }
            }
        }
        swap(&process[i].pNo, &process[p].pNo);
        swap(&process[i].arrivalTime, &process[p].arrivalTime);
        swap(&process[i].burstTime, &process[p].burstTime);
        x = 1000;
        process[i].startTime[0] = currentTime;
        currentTime += process[i].burstTime;
        process[i].waitingTime = currentTime - process[i].arrivalTime - process[i].burstTime;
        process[i].endTime[0] = currentTime;
        totalWTime += process[i].waitingTime;
    }

    for (i = 0; i < settings[1]; i++)
    {
        printf("P[%d] Start Time: %d End time: %d |", process[i].pNo, process[i].startTime[0], process[i].endTime[0]);
        printf(" Waiting time: %d\n", process[i].waitingTime);
    }

    float ave = (float)totalWTime / settings[1];
    printf("Average waiting time: %.1f", ave);
}

void RoundRobin(int settings[], struct Process process[]) {
    int timeSlice = settings[2];
    int workingProcess = settings[1];
    int processProgress[workingProcess];
    int k, p;

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
    sortByBurstTime(process, settings);

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

    int totalwaitTime = 0;
    for(k = 0; k < settings[1]; k++) {

        for(int p = 0; p < process[k].timeLength; p++) {

            if(p == 0) {
                printf("P[%i] Start Time: %i End time: %i |", process[k].pNo, process[k].startTime[p], process[k].endTime[p]);
            } else {
                printf(" Start Time: %i End time: %i |", process[k].startTime[p], process[k].endTime[p]);
                process[k].waitingTime = process[k].startTime[0];
                for(int m = 0; m < process[k].timeLength - 1; m++) {
                    process[k].waitingTime += process[k].startTime[m + 1] - process[k].endTime[m];
                }
            }

            if(p == process[k].timeLength - 1) {
                printf(" Waiting time: %i\n" , process[k].waitingTime);
                totalwaitTime += process[k].waitingTime;
            }
        }

        if(k == settings[1] - 1) {
            float ave = (float) totalwaitTime / settings[1];

            printf("Average waiting time: %.1f", ave);
        }
    }


    }

void SRTF(int settings[], struct Process process[]){
    int processNum = settings[1];
    struct tempProcess temp_process[processNum];

    int i, k;
    for (i = 0; i < settings[1]; i++)
    {
        for (k = 0; k < 50; k++)
        {
            temp_process[i].startTime[k] = 9999;
            temp_process[i].endTime[k] = 9999;
        }
    }

    sortByArrivalTime(process, settings);

    int currentTime = 0, finished = 0;
    int startedProcess[processNum], completedProcess[processNum], tempBurst[settings[1]], remainingBurst[processNum], totalTime[processNum];
    int tempIndex = -1;

    for (i = 0; i < processNum; i++)
    {
        completedProcess[i] = 0;
        startedProcess[i] = 0;

        temp_process[i].pNo = process[i].pNo;
        remainingBurst[i] = process[i].burstTime;
        tempBurst[i] = process[i].burstTime;
    }

    while (finished < processNum)
    {
        int currentIndex = -1;
        int burstTemp = 9999;

        for (i = 0; i < processNum; i++)
        {
            if (process[i].arrivalTime <= currentTime && completedProcess[i] == 0)
            {
                if (remainingBurst[i] == burstTemp)
                {
                    if (process[i].arrivalTime < process[currentIndex].arrivalTime)
                    {
                        burstTemp = remainingBurst[i];
                        currentIndex = i;
                    }
                }

                if (remainingBurst[i] < burstTemp)
                {
                    burstTemp = remainingBurst[i];
                    currentIndex = i;
                }

            }
        }

        if (currentIndex != tempIndex)
        {
            int temp = 0;

            for (i = 0; i < 50 && temp == 0; i++)
            {
                if (temp_process[tempIndex].endTime[i] == 9999)
                {
                    temp_process[tempIndex].endTime[i] = currentTime;
                    temp = 1;
                }
            }
        }

        if (currentIndex != -1)
        {
            if (remainingBurst[currentIndex] == process[currentIndex].burstTime)
            {
                int temp = 0;
                if (tempIndex != currentIndex)
                {
                    for (i = 0; i < 50 && temp == 0; i++)
                    {
                        if (temp_process[currentIndex].startTime[i] == 9999)
                        {
                            temp_process[currentIndex].startTime[i] = currentTime;
                            temp = 1;
                        }
                    }
                    
                    tempIndex = currentIndex;
                }
            }

            remainingBurst[currentIndex]--;
            process[currentIndex].burstTime--;
            currentTime++;

            if (remainingBurst[currentIndex] == 0)
            {
                int temp = 0;
                for (i = 0; i < 50 && temp == 0; i++)
                {
                    if (temp_process[currentIndex].endTime[i] == 9999)
                    {
                        temp_process[currentIndex].endTime[i] = currentTime;
                        totalTime[currentIndex] = temp_process[currentIndex].endTime[i] - process[currentIndex].arrivalTime;
                        temp_process[currentIndex].waitTime = totalTime[currentIndex] - tempBurst[currentIndex];
                    }
                }
                
                completedProcess[currentIndex] = 1;
                finished++;
            }

        } else
            currentTime++;
    }

    int z, temp;
    float avgwaitTime = 0;
    for (i = 0; i < settings[1]; i++)
    {
        temp = 0;
        
        for (z = 0; temp_process[i].startTime[z] != 9999 && temp_process[i].endTime[z] != 9999; z++)
        { 
            if(temp == 0) {
                printf("P[%d] Start Time: %d End time: %d | ", temp_process[i].pNo, temp_process[i].startTime[z], temp_process[i].endTime[z]);
                temp++;
            } else 
                printf("Start Time: %d End time: %d | ", temp_process[i].startTime[z], temp_process[i].endTime[z]);
        }
        
        printf("Waiting Time: %d \n", temp_process[i].waitTime);
        avgwaitTime += temp_process[i].waitTime;
    }

    avgwaitTime /= settings[1];
    printf("Average waiting time: %.1f\n", avgwaitTime);

}

int main()
{

    char filename[50];
    char test[4];
    char temp[4];
    int settings[3];
    int i;

    printf("Enter filename: ");

    scanf("%s", filename);
    FILE *f = fopen(strcat(filename, ".txt"), "r");

    if (f == NULL)
    {
        perror("File does not exist");
    }
    else
    {
        fscanf(f, "%i %i %i", &settings[0], &settings[1], &settings[2]);

        struct Process process[settings[1]];

        for (i = 0; i < settings[1]; i++)
        {

            fscanf(f, "%i %i %i", &process[i].pNo, &process[i].arrivalTime, &process[i].burstTime);
        }

        if (settings[0] == 0)
        {
            FCFS(settings, process);
        }
        else if (settings[0] == 1)
        {
            SJF(settings, process);
        }
        else if (settings[0] == 2)
        {
            SRTF(settings, process);
        }
        else if (settings[0] == 3)
        {
            RoundRobin(settings, process);
        }
    }
    fclose(f);
    return 0;
}