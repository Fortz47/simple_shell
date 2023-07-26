#include "shell.h"

/**
 * handle_built_in - checks for built-in cmd
 * @cmd: command
 *
 * Return: pointer to function
 */
void (*handle_built_in(char *cmd))(parse * ptr, char ***env_cpy)
{
	int i;

	built_in f[] = {
			{"setenv", _setenv},
			{"unsetenv", _unsetenv},
			{NULL, NULL}
	};

	for (i = 0; f[i].cmd; i++)
	{
		if (_strcmp(f[i].cmd, cmd))
			return (f[i].func);
	}
	return (NULL);
}
