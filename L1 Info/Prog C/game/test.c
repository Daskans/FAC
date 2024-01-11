#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include "folt.h"

typedef unsigned int uint;

uint get_random_integer(uint start, uint stop){
    uint r = start+rand()%(stop-start);
    return r;
}

int main(void){
    return EXIT_SUCCESS;
}
