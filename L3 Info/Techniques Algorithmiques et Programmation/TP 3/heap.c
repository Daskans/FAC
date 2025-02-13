#include "heap.h"
#include "tools.h"
#include <stdlib.h>

heap heap_create(int k, int (*f)(const void *, const void *)) {
  heap h = malloc(sizeof(*h));
  h->array = malloc(k * sizeof(void *));
  h->n = 0;
  h->nmax = k;
  h->f = f;
  return h;
}

void heap_destroy(heap h) {
  if (h) {
    if (h->array) {
      free(h->array);
    }
    free(h);
  }
}

bool heap_empty(heap h) {
  return h->n == 0;
}

bool heap_add(heap h, void *object) {
  if (h->n < h->nmax) {
    h->array[h->n++] = object;
    for (int i = h->n; h->f(h->array[i/2], h->array[i]) > 0 && i>1 && i != NULL; i/=2) {
      printf("EHO JE SUIS LA\n");
      int tmp;
      SWAP(h->array[i],h->array[i/2],tmp);
    }
    return false;
  }
  return true;
}

void *heap_top(heap h) {
  return h->array[1];
}

void *heap_pop(heap h) {
  h->array[1] = h->array[h->n];
  h->array[h->n] = NULL;
  h->n--;
  for (int i = 1; h->array[i] > h->array[2*i] || h->array[i] > h->array[2*i+1];) {
    if (h->f(h->array[2*i], h->array[2*i+1]) <= 0) {
      int tmp;
      SWAP(h->array[2*i], h->array[i], tmp);
      i *= 2;
    } else {
      int tmp;
      SWAP(h->array[2*i+1], h->array[i], tmp);
      i = 2*i+1;
    }
  } 
}
