#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_SIZE 1024
int main(int argc, char *args[]){
	int subscriber_id = atoi(args[1]);

	char pipe_path[20];
	sprintf(pipe_path, "./tmp/ex1/pipe%d", subscriber_id);

	int pipe_fd = open(pipe_path, O_RDONLY);
	
	char* message = malloc(sizeof(char) * (MAX_SIZE + 1));

	while(1){
		read(pipe_fd, message, MAX_SIZE);
		printf("%s\n", message);
	}

	close(pipe_fd);
	return 0;
}
