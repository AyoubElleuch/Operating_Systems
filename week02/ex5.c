#include<stdio.h>

int trib(int n){
	if(n < 0) return 0;
	if(n == 0 || n == 1) return n;
	if(n == 2) return 1;
	int a = 0;
	int b = 1;
	int c = 1;
	int result;
	for(int i=3; i<=n; i++){
		result = a + b + c;
		a = b;
		b = c;
		c = result;
	}
	return result;
}


int main(){
	int n;
	scanf("%d", &n);

	printf("%d", trib(n));

	return 0;
}

