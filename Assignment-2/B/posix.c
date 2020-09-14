#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int global_var = 0;

void *threadFun(void *vargp) 
{ 
	int local_var = 0;

    global_var++;
    local_var++;

    printf("glob = %i ", global_var);
    printf("loc = %i ", local_var);

    printf("\n");
    return NULL; 
}

int main(int argc, char const *argv[])
{
	pthread_t thread_id1, thread_id2; 
    printf("Before Thread\n"); 

    pthread_create(&thread_id1, NULL, threadFun, NULL); 
    pthread_create(&thread_id2, NULL, threadFun, NULL);

    pthread_join(thread_id1, NULL);  
    pthread_join(thread_id2, NULL);
    
    printf("After Thread\n"); 
    exit(0); 
}