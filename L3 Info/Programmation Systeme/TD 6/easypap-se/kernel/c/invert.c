
#include "easypap.h"

#include <omp.h>

#define INV_MASK (ezv_rgb_mask ())

static inline unsigned compute_color (int i, int j)
{
  return INV_MASK ^ cur_img (i, j);
}

int invert_do_tile_default (int x, int y, int width, int height)
{
  for (int i = y; i < y + height; i++)
    for (int j = x; j < x + width; j++)
      cur_img (i, j) = compute_color (i, j);

  return 0;
}

///////////////////////////// Simple sequential version (seq)
// Suggested cmdline(s):
// ./run -l data/img/shibuya.png -k invert -v seq -i 100 -n
//
unsigned invert_compute_seq (unsigned nb_iter)
{
  for (unsigned it = 1; it <= nb_iter; it++) {

    for (int i = 0; i < DIM; i++)
      for (int j = 0; j < DIM; j++)
        cur_img (i, j) = compute_color (i, j);
  }

  return 0;
}


///////////////////////////// Tiled sequential version (tiled)
// Suggested cmdline(s):
// ./run -l data/img/shibuya.png -k invert -v tiled -ts 32 -i 100 -n
//
unsigned invert_compute_tiled (unsigned nb_iter)
{
  for (unsigned it = 1; it <= nb_iter; it++) {

    for (int y = 0; y < DIM; y += TILE_H)
      for (int x = 0; x < DIM; x += TILE_W)
        do_tile (x, y, TILE_W, TILE_H);

  }

  return 0;
}

void *thread_fun(void *id)
{
    int i = id;
    
    return NULL;
}

unsigned invert_compute_thread(unsigned nb_iter)
{
    unsigned nb_thread = easypap_requested_number_of_threads();
    pthread_t pids[nb_thread];
    printf("DIM = %d\n", DIM);

    for (int i = 0; i < nb_thread; i++) {
        pthread_create(&pids[i], NULL, thread_fun, i);
    }


    for (int i = 0; i < nb_thread; i++) {
        pthread_join(pids[i], NULL);
    }

    return 0;
}
