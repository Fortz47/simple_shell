#include "shell.h"
/**
  *bring_line - Assigns the line var for get_line
  *@lineptr: Double pointer that stores the input string
  *@n: Pointer to the size of lineptr
  *@buffer: Pointer to the buffer containing the input string
  *@j: Size of buffer
  */

void bring_line(char **lineptr, size_t *n, char *buffer, size_t j)
{
	if (*lineptr == NULL)
	{
		if (j > BUFFER_SIZE)
			*n = j;
		else
			*n = BUFFER_SIZE;
		*lineptr = buffer;
	}
	else if (*n < j)
	{
		if (j > BUFFER_SIZE)
			*n = j;
		else
			*n = BUFFER_SIZE;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}
/**
  *get_line - Read inpt from stream
  *@lineptr: buffer that stores the input
  *@n: size of lineptr
  *@stream: stream to read from
  *Return: The number of bytes
  */
ssize_t get_line(char **lineptr, size_t *n, FILE *stream)
{
	int i;
	static ssize_t typed;
	ssize_t retVal;
	char *buffer;
	char t = 'z'; /* initialize to 'z' to make sure the */
	/* while loop is entered at least once  */

	if (typed == 0)
		fflush(stream);
	else
		return (-1);
	typed = 0;

	buffer = malloc(sizeof(char) * BUFFER_SIZE);
	if (buffer == NULL)
		return (-1);
	while (t != '\n')
	{
		i = read(STDIN_FILENO, &t, 1);
		if (i == -1 || (i == 0 && typed == 0))
		{
			free(buffer);
			return (-1);
		}
		if (i == 0 && typed != 0)
		{
			typed++;
			break;
		}
		if (typed >= BUFFER_SIZE)
			buffer = realloc(buffer, typed + 2);
		buffer[typed] = t;
		typed++;
	}
	buffer[typed] = '\0';
	bring_line(lineptr, n, buffer, typed);
	retVal = typed;
	if (i != 0)
		typed = 0;
	return (retVal);
}
