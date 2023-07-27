#include "shell.h"

char *shell;

/**
 * main - entry point
 * @ac: argument count
 * @av: array of argument
 * @env: environment
 *
 * Return: 0, success
 */
int main(int ac, char **av, char **env)
{
	char *buffer;
	ssize_t read;
	size_t len;
	char **env_cpy;

	shell = av[0];
	if (ac >= 1)
		env_cpy = copy_env(env, 0);
	while (TRUE)
	{
		buffer = NULL;
		len = 0;
		write(STDOUT_FILENO, "$ ", 2);
		read = getline(&buffer, &len, stdin);
		handle_EOF(&read, buffer, env_cpy);
		if (!read)
			continue;
		execute_all(buffer, &env_cpy);
	}
	return (0);
}
