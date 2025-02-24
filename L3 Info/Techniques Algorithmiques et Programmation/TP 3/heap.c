#include "heap.h"
#include "tools.h"
#include <stdlib.h>

heap heap_create(int k, int (*f)(const void *, const void *)) {
  heap h = malloc(sizeof(*h));
  h->array = malloc(k * sizeof(const void *));
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
  if (h->n++ < h->nmax) {
    h->array[h->n] = object;
    for (int i = h->n;i > 1 && h->f(h->array[i/2], h->array[i]) > 0; i/=2) {
        void* tmp;
        SWAP(h->array[i],h->array[i/2],tmp);
    }
    return false;
  }
  return true;
}

void *heap_top(heap h) {
  if (heap_empty(h)) {
    return NULL;
  }
  return h->array[1];
}

void *heap_pop(heap h) {
  if (heap_empty(h)) {
    return NULL;
  }
  void *head = h->array[1];
  h->array[1] = h->array[h->n];
  h->n--;
  for (int i = 1;;) {
    void* tmp;
    if (2*i > h->n) {
      break;
    }
    if (h->f(h->array[2*i], h->array[2*i+1]) <= 0) {
      SWAP(h->array[2*i], h->array[i], tmp);
      i *= 2;
    } else if (2*i+1 <= h->n) {
      SWAP(h->array[2*i+1], h->array[i], tmp);
      i = 2*i+1;
    }
  }
  return head;
}
