#include<stdio.h>
#include<string.h>

#define MAX_LENGTH 256

int main(){
	char input[MAX_LENGTH];
	char character;
	int index = 0;

	printf("Please enter a sentence: ");

	while((character = getchar()) != '.' && character != '\n' && index < MAX_LENGTH - 1){
		input[index] = character;
		index++;
	}

	input[index] = '\0';

	for(int i = index-1; i>=0; i--){
		printf("%c", input[i]);
	}
	printf("\n");

	return 0;
}
