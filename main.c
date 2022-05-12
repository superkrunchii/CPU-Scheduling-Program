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
    int x, y, z;
    int c;

    printf("Enter filename: ");

    scanf("%s" , filename);
    FILE *f = fopen(strcat(filename , ".txt") , "r");

    if(f == NULL) {
        perror("File does not exist");

    } else {

        while ((c = fgetc(f)) != EOF){
            fgets(test, 2, f); // X
            x = atoi(test);

            fgets(test, 3, f); // Y
            y = atoi(test);

            fgets(test, 3, f); // Z
            z = atoi(test);

            printf("INPUTS: %d %d %d \n", x, y, z);
        }

    }
    
    fclose(f);
    

    return 0;
}