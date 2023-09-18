#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(){
	int integer = INT_MAX;
	unsigned short ushort = USHRT_MAX;
	long int longint = LONG_MAX;
	float floating = FLT_MAX;
	double dbl = DBL_MAX;

	printf("Size of integer: %lu bytes\n", sizeof(integer));
	printf("Maximum value of integer: %d\n", integer);

	printf("Size of unsigned short: %lu bytes\n", sizeof(ushort));
	printf("Maximum value of unsigned short: %hu\n", ushort);

	printf("Size of signed long int: %lu bytes\n", sizeof(longint));
	printf("Maximum value of signed long int: %ld\n", longint);

	printf("Size of float: %lu bytes\n", sizeof(floating));
	printf("Maximum value of float: %f\n", floating);

	printf("Size of double: %lu bytes\n", sizeof(dbl));
	printf("Maximum value of double: %lf\n", dbl);

	return 0;

}


