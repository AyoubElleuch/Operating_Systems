#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdbool.h>


// Primality test
bool is_prime(int n){
    if(n <= 1) return false;
    for(int i=2; i*i <= n; i++){
        if(n % i == 0){
            return false;
        }
    }
    return true;
}

// Primes counter in [a, b)
int primes_count(int a, int b){
    int ret = 0;
    for(int i = a; i < b; i++){
        if(is_prime(i) != 0){
            ret++;
        }
    }
    return ret;
}

typedef struct prime_request{
    int a, b;
}prime_request;


void *prime_counter(void *arg){
    // get the request from arg
    prime_request req = *(prime_request*)arg;

    // perform the request
    int *count = malloc(sizeof(int));
    *count = primes_count(req.a, req.b);
    
    return count;
}

int min(int a, int b){
    return (a>b ? b : a);
}

int main(int argc, char* args[]){
    int n = atoi(args[1]);
    int m = atoi(args[2]);

    int segment = n / m;
    prime_request *requests = malloc(m*sizeof(prime_request));
    pthread_t *threads = malloc(m * sizeof(pthread_t));
    void **partialResults = malloc(m * sizeof(void *));
    for(int i=0; i<m; i++){
        requests[i].a = segment*i;
        requests[i].b = min(requests[i].a+segment, n);
        pthread_create(&threads[i], NULL, prime_counter, requests+i);
    }
    for(int i=0; i<m; i++){
        pthread_join(threads[i], partialResults+i);
    }
    int ans = 0;
    for(int i=0; i<m; i++){
        ans+=*(int *)partialResults[i];
    }
    printf("%d\n", ans);
    free(threads);
    free(partialResults);
    free(requests);

    return 0;
}