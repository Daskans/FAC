#ifndef HANOI_H
#define HANOI_H

typedef struct _hanoi_t hanoi_t;

hanoi_t * hanoi_new(size_t plate_nh);
void hanoi_delete(hanoi_t* h);
size_t hanoi_display(hanoi_t* h, FILE* Fd);
int hanoi_move(hanoi_t* h, size_t tower_src, size_t tower_dst);

#endif /*HANOI_H*/