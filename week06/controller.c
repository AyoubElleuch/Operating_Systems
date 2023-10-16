#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>

pid_t pid;

void signalHandler(int signal){
	if(signal == SIGINT){
		kill(pid, SIGTERM);
		exit(0);
	}
}


int main(){

	const char* pidFilePath = "var/run/agent.pid";
	FILE* pidFile = fopen(pidFilePath, "r");
	if(pidFile == NULL){
		printf("File not found.\n");
		exit(1);
	}

	char buffer[20];

	if(fgets(buffer, 20, pidFile) == NULL){
		printf("Error: No agent found!.\n");
		exit(1);
	}

	pid = atoi(buffer);

	if(pid){
		printf("Agent found.\n");
	}

	signal(SIGINT, signalHandler);

	printf("Choose a command {\"read\", \"exit\", \"stop\", \"continue\"} to send to agent.\n");
	while(fgets(buffer, sizeof(buffer), stdin)){
		if(strcmp(buffer, "read\n") == 0){
			kill(pid, SIGUSR1);
		}else if(strcmp(buffer, "exit\n") == 0){
			kill(pid, SIGUSR2);
			exit(0);
		}else if(strcmp(buffer, "stop\n") == 0){
			kill(pid, SIGSTOP);
		}else if(strcmp(buffer, "continue\n") == 0){
			kill(pid, SIGCONT);
		}
		printf("Choose a command {\"read\", \"exit\", \"stop\", \"continue\"} to send to agent.\n");
	}

	return 0;
}