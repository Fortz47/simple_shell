#include "shell.h"

/**
 * _getline - reads an entire line from stream, storing the address
 * of the buffer containing the text into *lineptr
 * @lineptr: array of strings
 * @n: byte in size
 * @stream: file stream
 *
 * Return: number of characters read or -1 if failed
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	size_t read;

	read = getline(lineptr, n, stream);
	return (read);
}
