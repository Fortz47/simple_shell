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
