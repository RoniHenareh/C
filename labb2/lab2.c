#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>

void *start_thread(void *message) {
    printf("%s\n", (const char *)message);
    return message;
}

// TID, Thread ID
pthread_t pthread_self(void); 

int main(void) { 

    pthread_t thread1, thread2, thread3;
    int pid = fork();

    const char *message1; //= "test1";
    const char *message2; //= "test2";
    const char *message3; //= "test3";

    // creates three threads
    pthread_create(&thread1, NULL, start_thread, (void *)message1);
    pthread_create(&thread2, NULL, start_thread, (void *)message2);
    pthread_create(&thread3, NULL, start_thread, (void *)message3);

    // testa på linux
    for (int buffer = 0; buffer < 15; buffer ++) {

        pthread_t TID1 = pthread_self();
        printf("TID: %p, PID: %d, Buffer: %d\n", TID1, getpid(), buffer);
        //pthread_t TID2 = pthread_self();
        //printf("%p\n", TID2);
        //pthread_t TID3 = pthread_self();
        //printf("%p\n", TID3);

    }
    
    // If many threads, joing them
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    return 0;
}