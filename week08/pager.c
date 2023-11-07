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

int P, F;
char **RAM;
char **disk;

void signalHandler(int signal){
    if(signal == SIGUSR1){
        int fd = open("/tmp/ex2/pagetable", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
        //struct stat file_stat;
        //fstat(fd, &file_stat);
        //off_t file_size = file_stat.st_size;

        struct PTE* pageTable = mmap(NULL, sizeof(struct PTE) * P, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        int randomIndex = rand() % P;
        for(int i=0; i<P; i++){
            if(pageTable[i].referenced != -1){
                for(int j=0; j<F; j++){
                    
                }
            }
        }
    }
}

void initializePageTable(struct PTE* pageTable, int numPages){
    for(int i=0; i<numPages; i++){
        pageTable[i].valid = false;
        pageTable[i].dirty = false;
        pageTable[i].frame = -1;
        pageTable[i].referenced = 0;
    }
}

struct PTE* createMappedFile(int numPages){
    const char* filePath = "tmp/ex2/pagetable";
    int fd = open(filePath, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if(fd == -1){
        printf("Cannot open the file!");
        exit(1);
    }
    if(ftruncate(fd, sizeof(struct PTE) * numPages) == -1){
        printf("Error while truncating the page table");
        exit(0);
    }
    struct PTE* pageTable = mmap(NULL, sizeof(struct PTE) * numPages, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(pageTable == MAP_FAILED){
        printf("Error mapping the file");
        exit(1);
    }

    close(fd);
    munmap(pageTable, sizeof(struct PTE) * numPages);
    return pageTable;    
};

int main(int argc, char *argv[])

    P = atoi(argv[0]);
    F = atoi(argv[1]);
    RAM = (char **)malloc(P * sizeof(char *));
    disk = (char **)malloc(F * sizeof(char *));

    for(int i=0; i<P; i++)
        for(int j=0; j<8; j++){
            RAM[i][j] = '\0';
        }
    

    for(int i=0; i<F; i++){
        for(int j=0; j<8; j++){
            disk[i][j] = 33 + rand() % 94;
        }
    }
    

    for(int i=0; i<P; i++){
        RAM[i] = (char *)malloc(8 * sizeof(char));
    }
    for(int i=0; i<F; i++){
        disk[i] = (char *)malloc(8 * sizeof(char));
    }
    signal(SIGUSR1, signalHandler);

    struct PTE* pageTable = createMappedFile(P);
    initializePageTable(pageTable, P);




    return 0;
