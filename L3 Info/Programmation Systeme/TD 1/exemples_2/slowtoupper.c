#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#include "error.h"

char *FILENAME = "file.txt";

int main (int argc, char *argv[])
{
  if (argc > 1)
    FILENAME = argv[1];

  int fd = open (FILENAME, O_RDWR);
  check (fd, "Cannot open %s file", FILENAME);

  // Get file size
  off_t len = lseek (fd, 0, SEEK_END);
    
  char *region = mmap (NULL, len, PROT_READ | PROT_WRITE,
                MAP_SHARED, fd, 0);
  printf ("File \"%s\" mapped at address %p\n", FILENAME, region);

  for (int i = 0; i < len; i++) {
    usleep (100000);
    region[i] = toupper (region[i]);
  }

  munmap (region, len);
  
  close (fd);

  return 0;
}
