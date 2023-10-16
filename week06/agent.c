#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>

void printFile(const char* filePath){
	FILE *file = fopen(filePath, "r");
	if(file == NULL) return;
	char buffer[100];
	
	while(fgets(buffer, sizeof(buffer), file) != NULL){
		printf("%s", buffer);
	}
	printf("\n");	
}

void signalHandler(int signal){
	if(signal == SIGUSR1){
		const char* textFilePath = "text.txt";
		printFile(textFilePath);
	}else if(signal == SIGUSR2){
		printf("Process terminating...");
		exit(0);
	}
}


int main(){
	pid_t pid = getpid();

	const char *pidFilePath = "var/run/agent.pid";
	FILE *pidFile = fopen(pidFilePath, "w");
	fprintf(pidFile, "%d", pid);
	fclose(pidFile);

	const char *textFilePath = "text.txt";
	printFile(textFilePath);

	signal(SIGUSR1, signalHandler);
	signal(SIGUSR2, signalHandler);
	while(1){
		sleep(1);
	}

	return 0;
}
