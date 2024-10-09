#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "error.h"

char *filename = "file.txt";

void lire (int fd)
{
  // TODO: read (and display) bytes in reverse order
  off_t taille;

  taille = lseek (fd, 0, SEEK_END);

  for (off_t pos = taille - 1; pos >= 0; pos--) {
    off_t p = lseek (fd, pos, SEEK_SET);
    check_syscall (p, "lseek cannot reach position %lld", pos);

    char c;
    int n;
    n = read (fd, &c, 1);
    check_syscall (n, "Cannot read from file %s", filename);

    write (STDOUT_FILENO, &c, 1);
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
