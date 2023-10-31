#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/mman.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>


#define PASSWORD_SIZE 14

int main(){
    FILE *pid_file = fopen("/tmp/ex1.pid", "w");
    if(pid_file == NULL){
        printf("Error while opening the file");
        return 1;
    }
    fprintf(pid_file, "%d", getpid());
    fclose(pid_file);

    FILE *random = fopen("/dev/random" , "r");
    if(random == NULL){
        printf("Error while opening the file");
    }
    char password[14];
    password[0] = 'p';
    password[1] = 'a';
    password[2] = 's';
    password[3] = 's';
    password[4] = ':';

    int writtenCharacters = 0;

    while(writtenCharacters < 8){
        char tmp;
        fscanf(random, "%c", &tmp);
        if(isprint(tmp)){
            password[writtenCharacters + 5] = tmp;
            writtenCharacters++;
        }
    }
    fclose(random);

    char *mapped_data = mmap(NULL, PASSWORD_SIZE*sizeof(char), PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    printf("%s\n", password);
    strcpy(mapped_data, password);
    munmap(mapped_data, PASSWORD_SIZE * sizeof(char));
    while(1){

    }
    return 0;
}