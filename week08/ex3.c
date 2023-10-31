#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/mman.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/resource.h>


int main(){
    struct rusage usage;
    long int size = 10 * 1024 * 1024;

    for(int i=0; i<10; i++){
        void* memory = malloc(size);
        memset(memory, 0, size);

        getrusage(RUSAGE_SELF, &usage);
        printf("Memory usage: %ldKB\n", usage.ru_maxrss);

        sleep(1);
    }

    return 0;
}