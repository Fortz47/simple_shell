#include "shell.h"
/**
 * then - continuation of handle_path function
 * @fp: filepath
 * @t: token
 * @p: pointer to struct parse
 * @av: pointer to struct parse
 * @F: flag
 * @s: status
 * @e: environment
 */
void then(char *fp, char *t, parse *p, parse *av, int *F, int *s, char **e)
{
	int index;

	while (t != NULL)
	{
		_strcpy(fp, t);
		_strcat(fp, "/");
		_strcat(fp, p->cmd);
		av->cmd = _strdup(fp);
		av->args[0] = _strdup(fp);
		if (check_valid(fp))
		{
			*F = TRUE;
			for (index = 1; index < p->argc; index++)
				av->args[index] = _strdup(p->args[index]);
			av->args[index] = NULL;
			*s = exec_cmd(av, e);
			if (*s != 0)
			{
				free_arr_str(av->args, index, 0);
				_then_free(2, av, fp, av->cmd, av->args);
				return;
			}
			break;
		}
		_then_free(3, NULL, fp, av->cmd, av->args[0], NULL);
		t = strtok(NULL, ":");
		if (t != NULL)
			fp = malloc(sizeof(char) * (_strlen(t) + _strlen(p->cmd) + 2));
	}
	if (*F && *s == 0)
	{
		_then_free(2, NULL, fp, av->cmd, NULL);
		free_arr_str(av->args, index, 0);
	}
	_then_free(0, av, av->args);
}
