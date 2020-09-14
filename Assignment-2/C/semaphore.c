#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

sem_t sem;

void *thread(void *arg) {
    sem_wait(&sem);

    int num = (int *)arg;

    printf("\nEntering thread number %i\n", num);

    sleep(2);

    printf("\nExiting thread number %i\n", num);
    sem_post(&sem);

    return 0;
}

int main(int argc, char const *argv[])
{
    sem_init(&sem, 0, 3);
    pthread_t threads [5];

    for (int i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, thread, i);
    }

    for(int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
        usleep(100000);
    }


    sem_destroy(&sem);
    return 0;
}
