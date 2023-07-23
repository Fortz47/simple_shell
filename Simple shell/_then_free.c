#include "shell.h"

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
