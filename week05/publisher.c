#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

#define MAX_SIZE 1024


int main(int argc, char *args[]){
	int n = atoi(args[1]);

	char pipe_path[20];
	for(int i=0; i<n; i++){
		sprintf(pipe_path, "./tmp/ex1/pipe%d", i+1);
		int x = mkfifo(pipe_path, 0777);
	}
	
	char message[MAX_SIZE];
	while(1){
		fgets(message, MAX_SIZE, stdin);
		pid_t pid;
		for(int i=0; i<n; i++){
			pid = fork();
			if(pid==0){
				int pipe_fd;
				sprintf(pipe_path,  "./tmp/ex1/pipe%d", i+1);
				pipe_fd = open(pipe_path, O_WRONLY);
				if(pipe_fd == -1){
					exit(1);
				}
				write(pipe_fd, message, strlen(message)+1);
				close(pipe_fd);				
				exit(0);
			}
		}
	}

	return 0;
}
