#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(){
	int n;
	int u[120], v[120];
	srand(time(0));
	scanf("%d", &n);
	for(int i=0; i<120; i++){
		u[i] = rand() % 100;
		v[i] = rand() % 100;
	
	}

	FILE* file = fopen("temp.txt", "w+");
	
	pid_t pid;
	int elementPerProcess = 120 / n;
	int start, end;
	for(int i=0; i<n; i++){
		start = i * elementPerProcess;
		end = start + elementPerProcess;
		
		pid = fork();
		if(pid < 0){
			printf("Failed fork");
			return 1;
		}else if(pid == 0){
			int result = 0;
			for(int j = start; j < end; j++){
				result += u[j] * v[j];

			}
			fprintf(file, "%d\n", result);
			fclose(file);
			exit(0);
		}
	}

	for(int i=0; i<n; i++){
		wait(NULL);
	}
	
	rewind(file);
	int result = 0;
	int input;
	while(fscanf(file, "%d", &input) == 1){
		result += input;
	}
	
	fclose(file);
	
	printf("The reuslt: %d\n", result);
	
	return 0;
}
