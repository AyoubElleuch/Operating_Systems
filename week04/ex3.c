#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]){
	int n = atoi(argv[1]);
	
	for(int i=0; i<n; i++){
		pid_t pid = fork();
		if(pid < 0){
			printf("Failed fork\n");
			return 1;
		}
		sleep(5);
	}

	exit(0);
	return 0;
}
