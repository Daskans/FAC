#include <ctype.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <time.h>
#include <unistd.h>

#include "error.h"

#define print_time(format, ...)                                                \
  do {                                                                         \
    time_t timer;                                                              \
    char buffer[26];                                                           \
    struct tm *tm_info;                                                        \
    timer   = time (NULL);                                                     \
    tm_info = localtime (&timer);                                              \
    strftime (buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);                       \
    fprintf (stderr, "*** [At %s] " format " ***\n", buffer, ##__VA_ARGS__);   \
  } while (0)

char *FILENAME = "file.txt";

int main (int argc, char *argv[])
{
  if (argc > 1)
    FILENAME = argv[1];

  int fd = open (FILENAME, O_RDONLY);
  check (fd, "Cannot open %s file", FILENAME);

  // Get file size
  off_t len = lseek (fd, 0, SEEK_END);

  char *region = mmap (NULL, len, PROT_READ, MAP_SHARED, fd, 0);
  printf ("File \"%s\" mapped at address %p\n", FILENAME, region);

  while (1) {
    sleep (1);
    print_time ("Content of \"%s\" :", FILENAME);

    write (STDOUT_FILENO, region, len);

    printf ("\n");
  }

  munmap (region, len);

  return 0;
}
