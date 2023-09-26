#include <stdio.h>

int const_tri(int* p, int n){
	if(n==0) return 0;
	if(n==1 || n==2) return 1;
	if(n==2) return 2;
	n-=2;
	while(n--){
		int temp = *p + *(p+1) + *(p+2);
		*p = *(p+1);
		*(p+1) = *(p+2);
		*(p+2) = temp;
	}
	return *(p+2);
}

int main(){
	const int x = 1;
	const int *q = &x;

	int cells[3];
	int *p = cells;

	*p = *q;
	*(p + 1) = *q;
	*(p + 2) = 2*(*q);

	printf("Memory addresses\n");
	printf("Cell 1: %p\n", (void *)&cells[0]);
	printf("Cell 2: %p\n", (void *)&cells[1]);
	printf("Cell 3: %p\n", (void *)&cells[2]);

	if(&cells[0] + 1 == &cells[1] && &cells[1] + 1 == &cells[2]){
		printf("The addresses are contigous\n");
	}else{
		printf("The addresses are not contigous\n");
	}

	int n;
	scanf("%d", &n);
	int result = const_tri(p, n);
	printf("The %dth tribonacci number is %d\n", n, result);

	return 0;
}
