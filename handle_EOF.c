#include "shell.h"
/**
 * handle_EOF - checks for EOF(ctrl + D) and/or "exit"
 * @read: number of characters read(from stdin)
 * @buffer: pointer to read input(from stdin)
 * @env_cpy: environment
 */
void handle_EOF(ssize_t *read, char *buffer, char **env_cpy)
{
	char *token, buf[BUFFER_SIZE];
	int status;

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
		(*read)--;
		if (*read == 0)
		{
		free(buffer);
			return;
		}
	}
	_strcpy(buf, buffer);
	token = strtok(buf, " ");
	if (_strcmp(token, "exit"))
	{
		free_arr_str_all(env_cpy, 0, 0);
		free(buffer);
		token = strtok(NULL, " ");
		if (token)
		{
			status = _atoi(token);
			exit(status);
		}
		exit(EXIT_SUCCESS);
	}
}
