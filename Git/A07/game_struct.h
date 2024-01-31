#ifndef _game_struct_h
#endif
#define _game_struct_
#include "game.h"
#include "game_ext.h"
#include "queue.h"

struct game_s {
    uint length;
    uint width;
    bool wrapping;
    neighbourhood neighborhood;
    constraint* constraints;
    color* colors;
    queue* undo_stack;
    queue* redo_stack;
};

// We added a struct move_s, which we will use for undo and redo stacks (move_previous for the undo and move_color for
// the redo)
struct move_s {
    uint x;
    uint y;
    color move_color;
    color move_previous;
};

typedef struct move_s* move;
