#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/mman.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/resource.h>
#include <signal.h>
#include <stdbool.h>

int flag = 0;

struct PTE{
    // The page is in the physical memory (RAM)
    bool valid;
    // The frame number of the page in the RAM
    int frame;
    // The page should be written to disk
    bool dirty;
    // The page is referenced/requested
    int referenced;
};

void signalHandler(int signal){
    if(signal == SIGCONT){
        flag = 1;
    }
}

void printPageTable(struct PTE* pageTable, int P){
    printf("Page Table\n-------------------------------------\n");
    for(int i=0; i<P; i++){
        printf("Page %d ---> valid=%d, frame=%d, dirty=%d, referenced=%d\n", i, pageTable[i].valid, pageTable[i].frame, pageTable[i].dirty, pageTable[i].referenced);
    }
}

int main(int argc, char *argv[]){
    signal(SIGCONT, signalHandler);
    int P = atoi(argv[0]);
    char *accesses = argv[1];
    pid_t pager_pid = atoi(argv[2]);
    pid_t mmu_pid = getpid();
    
    char *access = strtok(accesses, "");

    int fd = open("/tmp/ex2/pagetable", O_RDWR);
    struct PTE* pageTable = mmap(NULL, sizeof(struct PTE) * P, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(pageTable == MAP_FAILED){
        printf("Error while mapping the file");
        exit(1);
    }

    while(access != NULL){
        int pageIndex = atoi(access);
        char *accessType = access+1;
        access = strtok(NULL, " ");
        if(pageTable[pageIndex].valid == 0){
            pageTable[pageIndex].referenced = mmu_pid;
            close(fd);
            munmap(pageTable, sizeof(struct PTE) * P);
            if(kill(pager_pid, SIGUSR1) == -1){
                printf("Error sending signal");
                return 1;
            }
            while(1){
                if(flag){
                    flag = 0;
                    fd = open("/tmp/ex2/pagetanle", O_RDWR);
                    pageTable = mmap(NULL, sizeof(struct PTE) * P, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
                    pageTable[pageIndex].valid = true;
                    break;
                }
            }
        }else{
            if(*accessType == 'W'){
                pageTable[pageIndex].dirty = true;
            }
        }
        printPageTable(pageTable, P);
    }

    if(kill(pager_pid, SIGUSR1) == -1){
        printf("Error sending signal");
    }

    return 0;
}