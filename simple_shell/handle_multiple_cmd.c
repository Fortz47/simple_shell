#include "shell.h"

/**
 * split_string - splits a string
 * @str: string
 * @delim: split delimiter
 *
 * Return: 2d array ot the strings or Null if failed
 */
char **split_string(char *str, const char *delim)
{
	int i = 0;
	char *token;
	int count = return_num_of_arg(str, delim);
	char **arr = malloc(sizeof(char *) * (count + 1));

	if (!arr)
		return (NULL);
	token = strtok(str, delim);
	while (token && count)
	{
		arr[i] = _strdup(token);
		if (!arr[i])
		{
			free_arr_str_all(arr, i, 0);
			perror(shell);
			return (NULL);
		}
		token = strtok(NULL, delim);
		count--;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
/**
 * execute - executes a shell command
 * @buffer: buffer containing command
 * @env_cpy: environment
 */
void execute(char *buffer, char ***env_cpy)
{
	parse *ptr;
	void (*f)(parse *, char ***);

	ptr = parse_line(buffer);
	if (ptr)
	{
		f = handle_built_in(ptr->cmd);
		if (f != NULL)
			f(ptr, env_cpy);
		else if (handle_path(ptr, *env_cpy) != 0)
		{
			if (exec_cmd(ptr, *env_cpy) != 0)
				perror(shell);
		}
		free_arr_str_all(ptr->args, 0, 0);
		then_free(1, NULL, ptr, ptr->cmd, NULL);
	}
}

/**
 * execute_all - executes command input
 * @buffer: buffer containing command input
 * @env_cpy: environment
 */
void execute_all(char *buffer, char ***env_cpy)
{
	char **arr;
	int count, i = 0, j = 0, num = 0;

	while (buffer[i])
	{
		if (buffer[i] == ';')
			num++;
		i++;
	}
	count = return_num_of_arg(buffer, ";");
	if (num == 0 || count == 1)
	{
		execute(buffer, env_cpy);
		free(buffer);
		return;
	}
	else if (count > 1)
	{
		arr = split_string(buffer, ";");
		if (!arr)
		{
			perror(shell);
			return;
		}
		while (arr[j])
		{
			execute(arr[j], env_cpy);
			free(arr[j]);
			j++;
		}
		free(arr);
		free(buffer);
	}
}
