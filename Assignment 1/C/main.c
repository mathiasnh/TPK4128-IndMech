#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include "sleep.h"

void *threadFun(void *vargp) 
{ 
	printf("Tic \n");
	sleep(5);
    printf("Tok \n"); 
    return NULL; 
}
   
int main() 
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
