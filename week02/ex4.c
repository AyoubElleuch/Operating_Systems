#include <stdio.h>
#include <ctype.h>

#define MAX_LENGTH 256

int count(char s[MAX_LENGTH], char c){
	int occurrence = 0;
	for(int i=0; i<MAX_LENGTH; i++){
		if(s[i]!='\0'){
			if(tolower(s[i])==tolower(c)){
				occurrence++;
			}
		}else{
			break;
		}
	}
	return occurrence;
}

void countAll(char s[MAX_LENGTH]){
	for(int i=0; i<MAX_LENGTH; i++){
		if(s[i]!='\0'){
			printf("%c:%d, ", tolower(s[i]), count(s, s[i]));
		}else{
			break;
		}
	}
	printf("\n");
}


int main(){
	char input[MAX_LENGTH];
	scanf("%s", input);

	countAll(input);

	return 0;
}
