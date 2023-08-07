#include "main.h"
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s file_from file_to\n", argv[0]);
        exit(97);
    }

    char *file_from = argv[1];
    char *file_to = argv[2];

    // Check if file_to already exists
    struct stat sb;
    if (stat(file_to, &sb) == 0) {
        // Truncate file_to
        ftruncate(open(file_to, O_RDWR), 0);
    }

    // Open file_from and file_to
    int fd_from = open(file_from, O_RDONLY);
    if (fd_from == -1) {
        fprintf(stderr, "Error: Can't read from file %s\n", file_from);
        exit(98);
    }

    int fd_to = open(file_to, O_WRONLY | O_CREAT | O_TRUNC);
    if (fd_to == -1) {
        fprintf(stderr, "Error: Can't create file %s\n", file_to);
        exit(99);
    }

    // Read and write buffer
    char buffer[BUFFER_SIZE];
    ssize_t read_bytes, write_bytes;

    // Copy contents of file_from to file_to
    while ((read_bytes = read(fd_from, buffer, BUFFER_SIZE)) > 0) {
        write_bytes = write(fd_to, buffer, read_bytes);
        if (write_bytes != read_bytes) {
            fprintf(stderr, "Error: Can't write to file %s\n", file_to);
            exit(99);
        }
    }

    // Close file descriptors
    close(fd_from);
    close(fd_to);

    // Set permissions of file_to to rw-rw-r--
    struct stat sb;
    stat(file_to, &sb);
    sb.st_mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    chmod(file_to, sb.st_mode);

    return 0;
}
