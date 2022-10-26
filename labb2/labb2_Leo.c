#include <pthread.h> // Compile: gcc -o labb2 labb2.c -pthread
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 3

int buffer = 0;
pthread_mutex_t lock;

void *increment() {
    int counter = 0;
    while(1) {
        pthread_mutex_lock(&lock);
        if (buffer >= 15) {
            pthread_mutex_unlock(&lock);
            break;
        }
        printf("TID: %lu, PID: %d, Buffer: %d\n", pthread_self(), getpid(), buffer);
        buffer++;
        counter++;
        pthread_mutex_unlock(&lock);
    }
    printf("TID %lu worked on the buffer %d times\n", pthread_self(), counter);
    int *res = malloc(sizeof(int));
    *res = counter;
    return (void*) res;
}

int main() {
    pthread_t threads[NUM_THREADS];
    for(int i = 0; i < NUM_THREADS; i++) {
        if(pthread_create(&threads[i], NULL, increment, NULL) != 0) {
            fprintf(stderr, "Creating thread failed");
            return 1;
        }        
    }

    int* res[NUM_THREADS];
    for(int i = 0; i < NUM_THREADS; i++) {
        if(pthread_join(threads[i], (void**) &res[i]) != 0) {
            fprintf(stderr, "Joining thread failed");
            return 1;
        }
    }
    printf("Total buffer accesses: %d\n", (*res[0]) + (*res[1]) + (*res[2]));

    free(res[0]);
    free(res[1]);
    free(res[2]);
    return 0;
}