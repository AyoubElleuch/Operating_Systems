#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>

void* aggregate(void* base, size_t size, int n, void* initialValue, void* (*opr)(const void*, const void*)){
	char* data = (char*)base;
	void* result = initialValue;
	for(int i=0; i<n; i++){
		void* elem = (void*)(data + i*size);
		result = opr(result, elem);
	}
	return result;
}


void* add(const void* a, const void* b){
	int* result = (int*)malloc(sizeof(int));
	*result = *(int*)a + *(int*)b;
	return result;
}

void* multiply(const void* a, const void* b){
	int* result = (int*)malloc(sizeof(int));
	*result = *(int*)a * *(int*)b;
	return result;
}

void* max(const void* a, const void* b){
	int* result = (int*)malloc(sizeof(int));
	*result = (*(int*)a > *(int*)b) ? *(int*)a : *(int*)b;
	return result;
}


void* doubleAdd(const void* a, const void* b){
	double* result = (double*)malloc(sizeof(double));
	*result = *(double*)a + *(double*)b;
	return result;
}

void* doubleMultiply(const void* a, const void* b){
	double* result = (double*)malloc(sizeof(double));
	*result = *(double*)a * *(double*)b;
	return result;
}

void* doubleMax(const void* a, const void* b){
	double* result = (double*)malloc(sizeof(double));
	*result = (*(double*)a > *(double*)b) ? *(double*)a : *(double*)b;
	return result;
}

int main(){
	
	int intArray[5] = {1, 2, 3, 4, 5};
	double doubleArray[5] = {1.2, 2.4, 3.6, 4.8, 6.1};
	
	int initial = 0;
	int initialMultiply = 1;
	int min = INT_MIN;
	
	int* intSum = (int*)aggregate(intArray, sizeof(int), 5, &initial, add);
	int* intProduct = (int*)aggregate(intArray, sizeof(int), 5, &initialMultiply, multiply);
	int* intMax = (int*)aggregate(intArray, sizeof(int), 5, &min, max);
	printf("Sum of the integers: %d\n", *intSum);
	printf("Product of the integers is: %d\n", *intProduct);
	printf("The maximum amongst the integers is: %d\n", *intMax);
	
	
	double dInitial = 0.0;
	double dInitialMulitply = 1.0;
	double dMin = DBL_MIN;
	
	double* doubleSum = (double*)aggregate(doubleArray, sizeof(double), 5, &dInitial, doubleAdd);
	double* doubleProduct = (double*)aggregate(doubleArray, sizeof(double), 5, &dInitialMulitply, doubleMultiply);
	double* dbMax = (double*)aggregate(doubleArray, sizeof(double), 5, &dMin, doubleMax);
	
	printf("Sum of the doubles: %f\n", *doubleSum);
	printf("Product of the doubles is: %f\n", *doubleProduct);
	printf("The maximum amongst the doubles is: %f\n", *dbMax);
	
	return 0;
}
