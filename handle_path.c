#include "shell.h"

/**
 * handle_path - appends command input to PATH
 * @parsed: pointer to struct parse
 * @env_cpy: environment
 * @flag: check if cmd is on path
 *
 * Return: 0 if command exist on PATH or 1 if not
 */
int handle_path(parse *parsed, char **env_cpy, int *flag)
{
	char *filepath, *token, *path;
	int status;
	parse *argv;

	status = 1;
	path = getenv_value("PATH", env_cpy);
	if (!path)
		return (status);
	argv = malloc(sizeof(parse));
	if (!argv)
	{
		free(path);
		return (status);
	}
	argv->args = malloc(sizeof(char *) * (parsed->argc + 1));
	if (!argv->args)
	{
		free(path);
		free(argv);
		return (status);
	}
	token = strtok(path, ":");
	filepath = malloc(sizeof(char) * (_strlen(token) + _strlen(parsed->cmd) + 2));
	if (!filepath)
	{
		free(path);
		free(argv->args);
		free(argv);
		return (status);
	}
	then(filepath, token, parsed, argv, flag, &status, env_cpy);
	free(path);
	if (status != 0 && *flag)
		return (status);
	return (status);
}
