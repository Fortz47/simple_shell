#include "shell.h"

void exit_(char *buffer, char **env_cpy, unsigned int *n, ssize_t *read);

/**
 * handle_EOF - checks for EOF(ctrl + D) and/or "exit"
 * @read: number of characters read(from stdin)
 * @buffer: pointer to read input(from stdin)
 * @env_cpy: environment
 * @n: number of times enter/return key has been pressed
 */
void handle_EOF(ssize_t *read, char *buffer, char **env_cpy, unsigned int *n)
{
	if (*read == -1)
	{
		if (feof(stdin))
		{
			free_arr_str_all(env_cpy, 0, 0);
			free(buffer);
			exit(EXIT_SUCCESS);
		}
	}
	if (buffer[*read - 1] == '\n')
	{
		buffer[*read - 1] = '\0';
		if ((*read)-- == 0)
		{
			free(buffer);
			return;
		}
	}
	exit_(buffer, env_cpy, n, read);
}

