#include "mytail.c"

int tailFile(int inputFD, int outputFD, int numLines);

int main(int argc, char *argv[])
{
    return tailFile(0, 1, 10);  
 }