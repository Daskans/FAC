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

  int fd = open (FILENAME, O_RDONLY);
  check (fd, "Cannot open %s file", FILENAME);
   
  char *region = mmap (NULL, FILESIZE, PROT_READ,
                MAP_SHARED, fd, 0);
  printf ("File \"%s\" mapped at address %p\n", FILENAME, region);

  printf ("<cheat on> msg[0] : %s<cheat off>\n", region + 4 * sizeof (char *));

  display ((char **)region);

  munmap (region, FILESIZE);
  
  return 0;
}
