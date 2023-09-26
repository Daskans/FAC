// foobar.c

#include <stdio.h>
#include "foo.h"
#include "bar.h"
#include "foo.h"

int main(void)
{
    int x = foo(4);
    double y = bar(x);
    int z = VALUE;
    printf("foo=%d, bar=%g, val=%d\n", x, y, z);
    return 0;
}
