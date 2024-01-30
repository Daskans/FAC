#include <stdlib.h>
#include <stdio.h>
#include "hanoi.h"

struct _hanoi_t {
    size_t plate_nb;
    size_t* towers[3];
};

