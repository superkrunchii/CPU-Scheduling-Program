#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void RoundRobin() {

}

void SRTF() {

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

        int tasks[settings[1]][2];

        fgets(test, 3, f); // Remove Extra Spaces

        for(i = 0; i < settings[1]; i++) {

            fgets(test, 2, f);

            tasks[i][0] = atoi(test);

            fgets(test, 3, f);

            tasks[i][1] = atoi(test);

            fgets(test, 3, f);

            tasks[i][2] = atoi(test);

            fgets(test, 3, f); // Remove Extra Spaces

            printf("%d %d %d\n" , tasks[i][0] , tasks[i][1] , tasks[i][2]);

        }

        
        

    }
    
    fclose(f);
    

    return 0;
}