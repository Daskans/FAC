#include <stdio.h>

typedef struct myStruct{
    int foo;
    int bar;
}MyStruct;

int main()
{
    MyStruct* pS = NULL;
    
    pS->foo = 10;
    pS->bar = 5;
    
    return 0;
}