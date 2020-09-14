#include <stdio.h>
#include "allocate.h"

int main(int argc, char const *argv[]) {
    int i = 0;

    while(1) {
        allocate(i);
        i++;
    }
    return 0;
}
