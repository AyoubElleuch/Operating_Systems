#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#define MAX_SIZE 1024

int main(){
	int fd[2];
	pipe(fd);
	pid_t publisher;
	
	publisher = fork();
	
	if(publisher == 0){
		char message[MAX_SIZE];
		fgets(message, MAX_SIZE, stdin);
		write(fd[1], message, strlen(message) + 1);
	}else{
		char message[MAX_SIZE];
		read(fd[0], message, sizeof(message));
		printf("%s\n", message);
	}
	
	return 0;
}
