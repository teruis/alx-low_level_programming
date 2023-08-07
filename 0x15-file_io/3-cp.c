#include "main.h"
#include <stdio.h>
#include <stdlib.h>

#define BUFF_SIZE 1024

void close_file(int fd);

/**
 * main - Copies the contents of one file to another file.
 * @argc: The number of arguments given to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: 0 on success, or one of the following exit codes:
 *         97 - wrong number of arguments
 *         98 - source file does not exist or cannot be read
 *         99 - destination file cannot be created or written to
 *         100 - source or destination file cannot be closed
 */
int main(int argc, char *argv[])
{
	int from, to, r, w;
	char buffer[BUFF_SIZE];

	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}

	from = open(argv[1], O_RDONLY);
	if (from == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't read from file %s\n", argv[1]);
		exit(98);
	}

	to = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (to == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't write to %s\n", argv[2]);
		close_file(from);
		exit(99);
	}

	while ((r = read(from, buffer, BUFF_SIZE)) > 0)
	{
		w = write(to, buffer, r);
		if (w != r)
		{
			dprintf(STDERR_FILENO,
				"Error: Can't write to %s\n", argv[2]);
			close_file(from);
			close_file(to);
			exit(99);
		}
	}

	if (r == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't read from file %s\n", argv[1]);
		close_file(from);
		close_file(to);
		exit(98);
	}

	close_file(from);
	close_file(to);

	return (0);
}

/**
 * close_file - Closes a file descriptor and handles errors.
 * @fd: The file descriptor to be closed.
 */
void close_file(int fd)
{
	int c;

	c = close(fd);

	if (c == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		exit(100);
	}
}

