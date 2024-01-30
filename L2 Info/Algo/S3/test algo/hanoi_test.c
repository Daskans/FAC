#include <stdlib.h>
#include <stdio.h>
#include "hanoi.h"

int main() {
    hanoi_t* hanoi_new(size_t plate_nh);
    void hanoi_delete(hanoi_t* h);
    size_t hanoi_display(hanoi_t* h, FILE* Fd);
    int hanoi_move(hanoi_t* h, size_t tower_src, size_t tower_dst);
    return EXIT_SUCCESS;
}