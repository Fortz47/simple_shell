#include "shell.h"

/**
 * free_arr_str_all - frees a 2D array
 * @arr: 2d array
 * @i: index stop
 * @j: index start
 */
void free_arr_str_all(char **arr, int i, int j)
{
	int k;

	if (i == 0)
	{
		while (arr[i] != NULL)
			i++;
	}
	for (k = j; k < i; k++)
		free(arr[k]);
	free(arr);
}

/**
 * rm_env - removes a variable from environment
 * @env: environment
 * @index: index of variable to remove
 *
 * Return: pointer to new updated array copy or Null if failed
 */
char **rm_env(char **env, int index)
{
	char **envCopy;
	int i = 0, j, k = 0;

	while (env[i] != NULL)
		i++;
	envCopy = malloc(sizeof(char *) * i);
	if (!envCopy)
		return (NULL);
	for (j = 0; k < i; j++)
	{
		if (j == index)
			k++;
		if (!env[k])
			break;
		envCopy[j] = _strdup(env[k]);
		if (!envCopy[j])
		{
			free_arr_str(envCopy, j, 0);
			free(envCopy);
			return (NULL);
		}
		k++;
	}
	envCopy[j] = NULL;
	return (envCopy);
}

/**
 * then_free - frees memory
 * @count: number of argument to free
 * @_return: return value
 * @ptr: pointer to struct parse
 *
 * Return: return value
 */
parse *then_free(int count, parse *_return, parse *ptr, ...)
{
	char *str;
	char **str_arr;
	va_list list;

	va_start(list, ptr);

	while (count)
	{
		str = va_arg(list, char *);
		free(str);
		count--;
	}
	str_arr = va_arg(list, char **);
	if (str_arr)
		free(str_arr);
	if (ptr)
		free(ptr);
	va_end(list);
	return (_return);
}

/**
 * _then_free - frees memory
 * @count: number of argument to free
 * @ptr: pointer to struct parse
 *
 * Return: return value
 */
void _then_free(int count, parse *ptr, ...)
{
	char *str;
	char **str_arr;
	va_list list;

	va_start(list, ptr);

	while (count)
	{
		str = (va_arg(list, char *));
		free(str);
		count--;
	}
	str_arr = va_arg(list, char **);
	if (str_arr)
		free(str_arr);
	if (ptr)
		free(ptr);
	va_end(list);
}
