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

int main(int argc, char *argv[])
{
  assert(argc == 3);

  // construire le chemin au fichier index
  int l = strlen(argv[1]);
  char idx_filename[l + strlen(SUFFIXE) + 1];

  strncpy(idx_filename, argv[1], l);
  strcpy(idx_filename + l, SUFFIXE);

  int r;
  int ligne = atoi(argv[2]);

  int in_idx = open(idx_filename, O_RDONLY);
  check_syscall(in_idx, "%s", idx_filename);

  int in = open(argv[1], O_RDONLY);
  check_syscall(in, "%s", argv[1]);

  char c;
  off_t position;
  position = lseek(in, 0, SEEK_SET);

  if (ligne > 0) {
    position = lseek(in_idx, (ligne-1) * sizeof(off_t), SEEK_SET);
    read(in_idx, &position, sizeof(position));
    position = lseek(in, (position)* sizeof(char), SEEK_SET);
  }
   

  while((r = read(in, &c, 1)) != 0 && c != '\n') {
    printf("%c",c);
  }
  printf("\n");

  return EXIT_SUCCESS;
}
