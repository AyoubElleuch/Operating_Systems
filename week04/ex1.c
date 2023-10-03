#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <signal.h>

int main(){

	clock_t start, end, start1, end1, start2, end2;
	double childOneExecutionTime, childTwoExecutionTime, parentExecutionTime;
	start = clock();
	
	pid_t pid1 = fork();
	start1 = clock();
	

	if(pid1 == 0){
		printf("This is the child 1 process\n");
		
		end1 = clock();
		childOneExecutionTime = (double)(end1 - start1) / (CLOCKS_PER_SEC / 1000);
		
		printf("Child process 1 is terminating...\n");
		kill(getpid(), SIGTERM);
		
	}else{
		printf("This is the parent process after creating the first child process\n");
		pid_t pid2 = fork();
		start2 = clock();
		if(pid2 == 0){
			printf("This is the child 2 process\n");
			
			end2 = clock();
			childTwoExecutionTime = (double)(end2 - start2) / (CLOCKS_PER_SEC / 1000);
			
			printf("Child process 2 is terminating...\n");
			kill(getpid(), SIGTERM);
			
		}else{
			printf("This is the parent process after the creating the second child process\n");
		}
	}
	end = clock();
	parentExecutionTime = (double)(end - start) / (CLOCKS_PER_SEC / 1000);
	
	printf("The execution time for the parent process is %.2fms\n", parentExecutionTime);
	printf("The execution time for the first child is %.2fms\n", childOneExecutionTime);
	printf("The execution time for the second child is %.2fms\n", childTwoExecutionTime);
	return 0;
}
