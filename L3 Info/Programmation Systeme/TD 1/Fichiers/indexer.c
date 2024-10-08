#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "error.h"

#define SUFFIXE ".idx"
#define BUF_SIZE 2048

int main(int argc, char *argv[])
{
  assert(argc == 2);

  // construire le chemin au fichier index
  int l = strlen(argv[1]);
  char idx_filename[l + strlen(SUFFIXE) + 1];
  strncpy(idx_filename, argv[1], l);
  strcpy(idx_filename + l, SUFFIXE);

  char c;
  int r, w;
  int in = open(argv[1], O_RDONLY);
  check_syscall(in, "%s", argv[1]);
  int out = open(idx_filename, O_CREAT | O_WRONLY | O_TRUNC, 0640);
  check_syscall(out, "%s", idx_filename);

  while ((r = read(in, &c, 1)) != 0) {
    check_syscall(r, "read");
    if (c == '\n') {
      off_t position = lseek(in,0, SEEK_CUR);
      w = write(out, &position, sizeof(position));
      check_syscall(w, "write");
    }
  }

  return EXIT_SUCCESS;
}
