#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 1e7

unsigned int *array;

void allocateFirstFit(int adrs, int size){
    for(int i=0; i<SIZE-size; i++){
        if(array[i] == 0){
            int freeBlock = 1;
            for(int j=i+1; j<i+size-1; j++){
                if(array[j] != 0){
                    freeBlock = 0;
                    break;
                }
            }
            if(freeBlock){
                for(int j=i; j<i+size; j++){
                    array[j] = adrs;
                }
                break;
            }
        }
    }
}

void allocateBestFit(int adrs, int size){
    int bestFit = 1e7;
    int index = -1;
    int temp = -1;
    int count = 0;
    for(int i=0; i<SIZE; i++){
        if(array[i] == 0){
            if(count == 0){
                temp = i;
            }
            count++;
        }
        else {
            if(count < bestFit && count >= size){
                bestFit = count;
                index = temp;
            }
            count = 0;
        }
    }
    if((count < bestFit && count >= size) || count == SIZE){
        bestFit = count;
        index = temp;
    }
    if(index == -1) return;
    for(int i = index; i<index+size; i++){
        array[i] = adrs;
    }
}

void allocateWorstFit(int adrs, int size){
    int bestFit = 0;
    int index = -1;
    int temp = -1;
    int count = 0;
    for(int i=0; i<SIZE; i++){
        if(array[i] == 0){
            if(count == 0){
                temp = i;
            }
            count++;
        }
        else {
            if(count > bestFit && count >= size){
                bestFit = count;
                index = temp;
            }
            count = 0;
        }
    }
    if((count > bestFit && count >= size) || count == SIZE){
        bestFit = count;
        index = temp;
    }
    if(index == -1) return;
    for(int i = index; i<index+size; i++){
        array[i] = adrs;
    }
}

void clear(int adrs){
    for(int i=0; i<SIZE; i++){
        if(array[i] == adrs) array[i] = 0;
    }
}

int main(){
    array = (unsigned int*) calloc(SIZE, sizeof(unsigned int));
    FILE* file = fopen("queries.txt", "r");

    if(file == NULL) return 1;

    clock_t start, end;
    double cpu_time_used;
    double totalTime = 0;
    int numberOfQueries = 0;

    char buffer[50];
    int allocate = 0;
    int toClear = 0;
    int adrsToClear = 0;
    int adrs = 0;
    int size = 0;
    while(fscanf(file, "%s", buffer) != EOF){
        if(strcmp(buffer, "end") == 0) break;
        if(strcmp(buffer, "allocate") == 0) {
            allocate = 1;
            continue;
        }
        if(allocate == 1){
            if(adrs != 0){
                size = atoi(buffer);
                start = clock();
                allocateBestFit(adrs, size);
                end = clock();
                cpu_time_used = ((double) (end-start)) * 1000 / CLOCKS_PER_SEC;
                totalTime += cpu_time_used;
                numberOfQueries++;
                allocate = 0;
                adrs = 0;
                size = 0;
            }else{
                adrs = atoi(buffer);
            }
        }
        if(strcmp(buffer, "clear") == 0){
            toClear = 1;
            continue;
        }
        if(toClear == 1){
            adrsToClear = atoi(buffer);
            clear(adrsToClear);
            toClear = 0;
            adrsToClear = 0;
        }
    }
    printf("Throughtput: %f\n", (double)(numberOfQueries / totalTime));
    return 0;
}