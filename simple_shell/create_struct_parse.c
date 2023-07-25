#include "shell.h"

/**
 * create_struct_parse - create and allocate memory for a struct parse
 * @cmd_count: number of bytes to allocate for parse->cmd
 * @args_count: number of bytes to allocate for parse->args
 *
 * Return: pointer to struct parse or NULL if failed
 */
parse *create_struct_parse(int cmd_count, int args_count)
{
	parse *ptr;

	ptr = malloc(sizeof(parse));
	if (!ptr)
		return (NULL);
	ptr->cmd = malloc(sizeof(char) * cmd_count + 1);
	if (!ptr->cmd)
		return (then_free(0, NULL, ptr, NULL));
	ptr->args = malloc(sizeof(char *) * (args_count + 1));
	if (!ptr->args)
		return(then_free(1, NULL, ptr, ptr->cmd, ptr->args));
	return (ptr);

}
