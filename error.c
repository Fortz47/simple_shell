#include "shell.h"

/**
 */
void puts_int(unsigned int n)
{
	char digit;

	if (n == 0)
	{
		write(STDERR_FILENO, "0", 1);
		return;
	}

	if (n / 10 != 0)
	{
		puts_int(n / 10);
	}

	digit = (n % 10) + '0';
	write(STDERR_FILENO, &digit, 1);
}


/**
 */
void error_notFound(char *cmd, unsigned int *n)
{
	char *msg = ": not found\n";

	write(STDERR_FILENO, shell, _strlen(shell));
	write(STDERR_FILENO, ": ", 2);
	puts_int(*n);
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, cmd, _strlen(cmd));
	write(STDERR_FILENO, msg, _strlen(msg));
}

/**
 */
int error_exit(int status, unsigned int *n)
{
	char *msg = ": Illegal number: -";
	if (status < 0)
	{
		write(STDERR_FILENO, shell, _strlen(shell));
		write(STDERR_FILENO, ": ", 2);
		puts_int(*n);
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, "exit", 4);
		write(STDERR_FILENO, msg, _strlen(msg));
		puts_int(status * -1);
		write(STDERR_FILENO, "\n", 1);
		return (TRUE);
	}
	return (FALSE);
}

/**
 */
void exit_(char *buffer, char **env_cpy, unsigned int *n, ssize_t *read)
{
	char *token;
	char buf[BUFFER_SIZE];
	int status;

	_strcpy(buf, buffer);
	token = strtok(buf, " ");
	if (_strcmp(token, "exit"))
	{
		token = strtok(NULL, " ");
		if (token)
		{
			status = _atoi(token);
			if (error_exit(status, n))
			{
				free(buffer);
				*read = 0;
				return;
			}
			free_arr_str_all(env_cpy, 0, 0);
			free(buffer);
			exit(status);
		}
		free_arr_str_all(env_cpy, 0, 0);
		free(buffer);
		exit(EXIT_SUCCESS);
	}
}
