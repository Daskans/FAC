#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "error.h"

char *filename = "file.txt";

void lire (int fd)
{
  // TODO: read (and display) bytes in reverse order

  off_t pos;

  pos = lseek (fd, -1, SEEK_END);

  while (pos != -1) {
    char c;
    int n;
    n = read (fd, &c, 1);
    check_syscall (n, "read");

    write (STDOUT_FILENO, &c, 1);

    pos = lseek (fd, -2, SEEK_CUR);
    // TODO
  }
}

int main (int argc, char *argv[])
{
  if (argc > 1)
    filename = argv[1];

  int fd = open (filename, O_RDONLY);
  check_syscall (fd, "Cannot open %s file", filename);

  lire (fd);

  close (fd);

  return 0;
}
