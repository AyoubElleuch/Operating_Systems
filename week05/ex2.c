#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>

#define MAX_SIZE 256

struct Thread{
    pthread_t id;
    int i;
    char message[MAX_SIZE];
};

typedef struct Thread T;


void *threadRoutine(void *tPtr){
    T thread = *(T *)tPtr;
    printf("Thread %d id: %lu\n", thread.i, thread.id);
    printf("%s\n", thread.message);
    printf("Thread %d exits\n", thread.i);
}

int main(){
    int n;
    scanf("%d", &n);
    T threads[n];
    for(int i=0; i<n; i++){
        T thread;
        sprintf(thread.message, "Hello from thread %d", i);
        thread.i = i;
        threads[i] = thread;
        pthread_create(&threads[i].id, NULL, threadRoutine, &threads[i]);
        printf("Thread %d is created\n", i);
        pthread_join(threads[i].id, NULL);
    }

    return 0;
}
