#include "main.h"


/**
 * read_textfile- Read text file print to STDOUT.
 * @filename: text file being read
 * @letters: number of letters to be read
 *
 * Return: w- actual number of bytes read and printed
 */
ssize_t read_textfile(const char *filename, size_t letters)
{
    int fd;
    char *buffer;
    ssize_t n;

    if (filename == NULL)
        return 0;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return 0;

    buffer = malloc(letters + 1);
    if (buffer == NULL)
    {
        close(fd);
        return 0;
    }

    n = read(fd, buffer, letters);
    if (n == -1)
    {
        free(buffer);
        close(fd);
        return 0;
    }

    buffer[n] = '\0';
    write(STDOUT_FILENO, buffer, n);

    free(buffer);
    close(fd);

    return n;
}
