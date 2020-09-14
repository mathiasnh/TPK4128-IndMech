#include <stdio.h>
#include <stdlib.h>

void allocate(int value) { 
    int *ptr = NULL;
    ptr = malloc(10000000000 * sizeof(int));

    /*
    if(ptr == NULL){
    	perror("malloc");
    	exit(0);
    }
    */

    *ptr = value;
    printf("test of allocated memory: %i\n", *ptr);
}