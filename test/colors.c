#include <stdio.h>
#include <stdlib.h>

/* Colors*/
#define BOLDGREEN "\033[1m\033[32m" 
#define BOLDRED   "\033[1m\033[31m" 
#define BOLDBLUE  "\033[1m\033[34m"
#define BOLDLIGHTBLUE "\033[1m\033[94m"
#define BOLDPINK "\033[1m\033[95m"
#define BOLDORANGE "\033[1m\033[38;5;208m"
#define BOLDDARKGREEN "\033[1m\033[38;5;22m"
#define RESET     "\033[0m"         /* Reset color */

void main(void) {
    int a = 3;
    printf("%s%d%s\n", BOLDLIGHTBLUE, a, RESET );
    printf("%s %s\n", BOLDLIGHTBLUE "hello", BOLDGREEN "there");
    printf("%s %s\n", BOLDORANGE "General", BOLDRED "Kenobi");
}