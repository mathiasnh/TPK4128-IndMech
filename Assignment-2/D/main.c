#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

int running = 1;
int var1 = 0;
int var2 = 0;

pthread_mutex_t mutex;

void *thread1(void *arg){
    while(running){
        pthread_mutex_lock(&mutex);
        var1++;
        var2 = var1;
        pthread_mutex_unlock(&mutex);
    }
    return 0;
}

void *thread2(void *arg){
    for(int i = 0; i <= 20; i++){
        printf("Number 1 is %i, number 2 is %i\n", var1, var2);
        usleep(100000);
    }
    running = 0;
    return 0;
}

int main(int argc, char const *argv[])
{
    pthread_mutex_init(&mutex, NULL);
    pthread_t t1, t2;

    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t1, NULL);

    pthread_mutex_destroy(&mutex);
    return 0;
}
