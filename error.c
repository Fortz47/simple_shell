#include "shell.h"

/**
 * puts_int - puts an integer
 * @n: integer
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
 * error_notFound - handles not found error
 * @cmd: command
 * @n: number of times enter/return key has been pressed
 * @p: parse struct pointer
 * @buf: buffer of input from stdin
 * @env: environment
 */
void error_notFound(char *cmd, unsigned int *n, parse *p,
		char *buf, char ***env)
{
	char *msg = ": not found\n";

	write(STDERR_FILENO, shell, _strlen(shell));
	write(STDERR_FILENO, ": ", 2);
	puts_int(*n);
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, cmd, _strlen(cmd));
	write(STDERR_FILENO, msg, _strlen(msg));

	if (!isatty(STDIN_FILENO))
	{
		free_arr_str_all(p->args, 0, 0);
		free_arr_str_all((*env), 0, 0);
		then_free(2, NULL, p, buf, p->cmd, NULL);
		exit(127);
	}
}

/**
 * error_exit - handle exit error
 * @status: exit status
 * @n: number of times enter/return key has been pressed
 * @buf: buffer of input from stdin
 * @env: environment
 *
 * Return: TREUE or FALSE
 */
int error_exit(int status, unsigned int *n, char *buf, char ***env, char *tok)
{
	char *msg = ": Illegal number: -";
	char *msg2 = ": Illegal number: ";

	if (status < 0)
	{
		write(STDERR_FILENO, shell, _strlen(shell));
		write(STDERR_FILENO, ": ", 2);
		puts_int(*n);
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, "exit", 4);
		if (tok)
		{
			write(STDERR_FILENO, msg2, _strlen(msg2));
			write(STDERR_FILENO, tok, _strlen(tok));
		}
		else
		{
			write(STDERR_FILENO, msg, _strlen(msg));
			puts_int(status * -1);
		}
		write(STDERR_FILENO, "\n", 1);

		if (!isatty(STDIN_FILENO))
		{
			free_arr_str_all((*env), 0, 0);
			then_free(1, NULL, NULL, buf, NULL);
			exit(2);
		}
		return (TRUE);
	}
	return (FALSE);
}

/**
 * exit_ - handles exiting the shell
 * @buffer: input from stdin
 * @env_cpy: environment
 * @n: number of times enter/return key has been pressed
 * @read: number of characters read from stdin
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
			if (!(status == -1100110011))
				token = NULL;
			if (error_exit(status, n, buffer, &env_cpy, token))
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
