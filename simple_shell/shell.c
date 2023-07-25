#include "shell.h"

/**
 * main - entry point
 * @ac: argument count
 * @av: array of argument
 * @env: environment
 *
 * Return: 0, success
 */
int main(int ac __attribute__((unused)), char **av, char **env)
{
	parse *parsed;
	char *buffer;
	int i;
	ssize_t read;
	size_t len;
	void *(*f)(parse *, char **);
	char **env_cpy = copy_env(env, 0);

	while (TRUE)
	{
		buffer = NULL;
		len = 0;
		write(STDOUT_FILENO, "($) ", 4);
		read = getline(&buffer, &len, stdin);
		handle_EOF(&read, buffer, env_cpy);
		if (!read)
			continue;
		parsed = parse_line(buffer);
		if (parsed)
		{
			f = handle_built_in(parsed->cmd);
			if (f != NULL)
				env_cpy = (char **)f(parsed, env_cpy);
			else if (handle_path(parsed, env_cpy) != 0)
			{
				if (exec_cmd(parsed, env_cpy) != 0)
					perror(av[0]);
			}
			free(buffer);
			free(parsed->cmd);
			for (i = 0; parsed->args[i] != NULL; i++)
				free(parsed->args[i]);
			free(parsed->args);
			free(parsed);
		}
	}
	return (0);
}
