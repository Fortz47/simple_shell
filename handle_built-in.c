#include "shell.h"

/**
 * handle_built_in - checks for built-in cmd
 * @cmd: command
 * n: number of times enter/return key has been pressed
 * Return: function to handle
 */
void (*handle_built_in(char *cmd))(parse *, char ***, unsigned int *)
{
	int i;

	built_in f[] = {
			{"setenv", _setenv},
			{"unsetenv", _unsetenv},
			{"cd", cd},
			{NULL, NULL}
	};

	for (i = 0; f[i].cmd; i++)
	{
		if (_strcmp(f[i].cmd, cmd))
			return (f[i].func);
	}
	return (NULL);
}
