#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/mman.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>

#define FILE_SIZE 500 * 1024 * 1024
#define LINE_LENGTH 1024

int main(){
    FILE* textFile = fopen("text.txt", "w");
    FILE* random = fopen("/dev/random", "r");

    size_t writtenBytes = 0;
    while(writtenBytes < FILE_SIZE){
        char c;
        int read_bytes = fscanf(random, "%c", &c);
        if(isprint(c)){
            fprintf(textFile, "%c", c);
            writtenBytes++;
            if(writtenBytes % LINE_LENGTH == 0){
                fprintf(textFile, "\n");
                writtenBytes++;
            }
        }
    }

    fclose(random);
    fclose(textFile);

    int fd = open("text.txt", O_RDWR);
    void *mapped_data = mmap(NULL, FILE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    unsigned long int count = 0;
    for(ssize_t i = 0; i<FILE_SIZE; i++){
        char letter = ((char *)mapped_data)[i];
        if(isupper(letter)){
            ((char *)mapped_data)[i] = tolower(letter);
            count++;
        }
    }
    printf("The number of capital letters in the file is: %lu\n", count);

    munmap(mapped_data, FILE_SIZE);
    close(fd);

    return 0;
}