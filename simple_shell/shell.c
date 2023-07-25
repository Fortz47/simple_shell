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
	parse *p;
	char *buffer;
	ssize_t read;
	size_t len;
	void (*f)(parse *, char ***);
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
		p = parse_line(buffer);
		if (p)
		{
			f = handle_built_in(p->cmd);
			if (f != NULL)
				f(p, &env_cpy);
			else if (handle_path(p, env_cpy) != 0)
			{
				if (exec_cmd(p, env_cpy) != 0)
					perror(av[0]);
			}
			free_arr_str_all(p->args, 0, 0);
			then_free(2, NULL, p, buffer, p->cmd, NULL);
		}
	}
	return (0);
}
