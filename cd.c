#include "shell.h"

void puts_int(unsigned int n);
int find_var(const char *var, char *env_var);
char *getenv_value(const char *var, char **env_cpy);

/**
 * _getenv - gets an environment variable
 * @var: environment variable
 * @env_cpy: environment
 *
 * Return: environment variable or NULL if doesn't exist
 */
char *_getenv(const char *var, char **env_cpy)
{
	int i = 0;
	char **env = env_cpy;

	while (env[i] != NULL)
	{
		if (find_var(var, env[i]))
			return (env[i]);
		i++;
	}
	return (NULL);
}

/**
 * reset_env - sets an environment variable if it exists
 * @old_var: old environment variable
 * @new_var: new environment variable
 * @env_cpy: environment
 *
 * Return: environment variable or NULL if doesn't exist
 */
int reset_env(const char *old_var, char *new_var, char ***env_cpy)
{
	int i = 0;

	while ((*env_cpy)[i] != NULL)
	{
		if (find_var(old_var, (*env_cpy)[i]))
		{
			free((*env_cpy)[i]);
			(*env_cpy)[i] = new_var;
			if ((*env_cpy)[i] == NULL)
				return (FALSE);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

/**
 */
void error_cd(parse *ptr, unsigned int *n)
{
	char *msg = ": can't cd to ";

	write(STDERR_FILENO, shell, _strlen(shell));
	write(STDERR_FILENO, ": ", 2);
	puts_int(*n);
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, ptr->cmd, _strlen(ptr->cmd));
	write(STDERR_FILENO, msg, _strlen(msg));
	write(STDERR_FILENO, ptr->args[1], _strlen(ptr->args[1]));
	write(STDERR_FILENO, "\n", 1);
}

/**
 */
void cd(parse *p, char ***env_cpy, unsigned int *n)
{
	int flag = 1, FLAG = 1;
	char *PWD, *OLDPWD, BUF[BUFFER_SIZE], *dir;
	char *ptr = _getenv("PWD", (*env_cpy));

	if (p->argc == 1)
	{
		dir = getenv_value("HOME", (*env_cpy));
		flag = chdir((const char *)dir);
	}
	else if (_strcmp(p->args[1], "-"))
	{
		dir = getenv_value("OLDPWD", (*env_cpy));
		flag = chdir((const char *)dir);
	}
	else
		FLAG = chdir((const char *)p->args[1]);

	if (flag == -1 || FLAG == -1)
		error_cd(p, n);
	else if (flag == 0 || FLAG == 0)
	{
		if (getcwd(BUF, sizeof(BUF)) == NULL)
		{
			perror("cd");
			free(dir);
			return;
		}
		PWD = malloc(sizeof(char) * (_strlen(BUF) + 5));
		if (!PWD)
		{
			perror("cd");
			free(dir);
			return;
		}
		OLDPWD = malloc(sizeof(char) * (_strlen(ptr) + 4));
		if (!OLDPWD)
		{
			perror("cd");
			free(PWD);
			free(dir);
			return;
		}
		_strcpy(PWD, "PWD=");
		_strcat(PWD, BUF);
		_strcpy(OLDPWD, "OLD");
		_strcat(OLDPWD, ptr);
		if (reset_env("PWD", PWD, env_cpy))
		{
			if (!(reset_env("OLDPWD", OLDPWD, env_cpy)))
			{
				perror("cd");
				then_free(2, NULL, NULL, PWD, OLDPWD, NULL);
			}
		}
		else
		{
			perror("cd");
			then_free(2, NULL, NULL, PWD, OLDPWD, NULL);
		}
	}
	if (flag != 1 && FLAG == 1)
		free(dir);
}
