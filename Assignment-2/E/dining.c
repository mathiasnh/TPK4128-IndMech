#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

pthread_mutex_t forks[5];
pthread_mutex_t waiter;

void *thread(void *arg){

    int num = (int *)arg;

    printf("Philosopher %i is thinking...\n", num);
    pthread_mutex_lock(&waiter);
    pthread_mutex_lock(&forks[num]);
    usleep(10000);

    if(num == 4) {
        pthread_mutex_lock(&forks[0]);
    } else {
        pthread_mutex_lock(&forks[num + 1]);
    } 

    printf("Philosopher %i is eating...\n", num);
    sleep(2);

    if(num == 4) {
        pthread_mutex_unlock(&forks[0]);
        pthread_mutex_unlock(&forks[num]);
    } else {
        pthread_mutex_unlock(&forks[num + 1]);
        pthread_mutex_unlock(&forks[num]);
    } 

    pthread_mutex_unlock(&waiter);

    return 0;
}

int main(int argc, char const *argv[]){
    pthread_t threads[5];

    pthread_mutex_init(&waiter, NULL);

    for (int i = 0; i < 5; i++) {
        pthread_mutex_init(&forks[i], NULL);
        pthread_create(&threads[i], NULL, thread, i);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
        //usleep(100000);
    }

    for (int i = 0; i < 5; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    pthread_mutex_destroy(&waiter);

    return 0;
}
