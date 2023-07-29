#include "shell.h"

void error_notFound(char *, unsigned int *, parse *, char *, char ***);

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
 * @n: number of times enter/return key has been pressed
 */
void execute(char *buffer, char ***env_cpy, unsigned int *n)
{
	int flag = FALSE, status1, status2;
	parse *ptr;
	void (*f)(parse *, char ***, unsigned int *);

	ptr = parse_line(buffer);
	if (ptr)
	{
		f = handle_built_in(ptr->cmd);
		if (f != NULL)
		{
			if (!isatty(STDIN_FILENO))
				free(buffer);
			f(ptr, env_cpy, n);
		}
		else
		{
			status1 = handle_path(ptr, *env_cpy, &flag);
			if (status1 != 0)
			{
				if (check_valid(ptr->cmd))
					status2 = exec_cmd(ptr, *env_cpy);
				else if (!flag && !check_valid(ptr->cmd))
					error_notFound(ptr->cmd, n, ptr, buffer, env_cpy);
				if ((flag && status1 != 0) || (check_valid(ptr->cmd) && status2 != 0))
				{
					if (!isatty(STDIN_FILENO))
					{
						free_arr_str_all(ptr->args, 0, 0);
						free_arr_str_all((*env_cpy), 0, 0);
						then_free(2, NULL, ptr, buffer, ptr->cmd, NULL);
						exit(2);
					}
				}
			}
		}
		free_arr_str_all(ptr->args, 0, 0);
		then_free(1, NULL, ptr, ptr->cmd, NULL);
	}
}

/**
 * execute_all - executes command input
 * @buffer: buffer containing command input
 * @env_cpy: environment
 * @n: number of times enter/return key has been pressed
 */
void execute_all(char *buffer, char ***env_cpy, unsigned int *n)
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
	if (num == 0)
	{
		execute(buffer, env_cpy, n);
		free(buffer);
		return;
	}
	else if (count && num > 0)
	{
		arr = split_string(buffer, ";");
		if (!arr)
		{
			perror(shell);
			return;
		}
		while (arr[j])
		{
			execute(arr[j], env_cpy, n);
			free(arr[j]);
			j++;
		}
		free(arr);
		free(buffer);
	}
}
