#include <main.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    dprintf(2, "Usage: cp file_from file_to\n");
    exit(97);
  }

  char *file_from = argv[1];
  char *file_to = argv[2];

  int fd_from = open(file_from, O_RDONLY);
  if (fd_from < 0) {
    dprintf(2, "Error: Can't read from file %s\n", file_from);
    exit(98);
  }

  int fd_to = open(file_to, O_WRONLY | O_CREAT | O_TRUNC, 0664);
  if (fd_to < 0) {
    dprintf(2, "Error: Can't write to file %s\n", file_to);
    exit(99);
  }

  char buffer[1024];
  int bytes_read;
  while ((bytes_read = read(fd_from, buffer, sizeof(buffer))) > 0) {
    write(fd_to, buffer, bytes_read);
  }

  if (bytes_read < 0) {
    dprintf(2, "Error: Can't read from file %s\n", file_from);
    exit(98);
  }

  close(fd_from);
  close(fd_to);

  return 0;
}
