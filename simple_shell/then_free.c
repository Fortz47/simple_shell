#include "shell.h"

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
