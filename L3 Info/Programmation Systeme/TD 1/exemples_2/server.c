#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <string.h>

#include "error.h"

char *FILENAME = "dump.bin";
#define FILESIZE 4096

#define NB_MSG 3

char *tab[NB_MSG] = { "Bonjour", "Ola", "Hey" };

void display (char **ptr)
{
  int i = 0;
  while (ptr[i] != NULL) {
    printf ("msg %d: %s\n", i, ptr[i]);
    i++;
  }
}

int main (int argc, char *argv[])
{
  if (argc > 1)
    FILENAME = argv[1];

  int fd = open (FILENAME, O_RDWR | O_CREAT | O_TRUNC, 0666);
  check (fd, "Cannot open %s file", FILENAME);

  // set file length to FILESIZE
  ftruncate (fd, FILESIZE);
   
  char *region = mmap (NULL, FILESIZE, PROT_READ | PROT_WRITE,
                MAP_SHARED, fd, 0);
  printf ("File \"%s\" mapped at address %p\n", FILENAME, region);

  char **ptr = (char **)region;
  char *dst = region + (NB_MSG + 1) * sizeof (char *);

  for (int i = 0; i < NB_MSG; i++) {
    ptr[i] = dst;
    dst = stpcpy (dst, tab[i]) + 1;
  }
  ptr[NB_MSG] = NULL;

  display (ptr);

  munmap (region, FILESIZE);
  
  return 0;
}
