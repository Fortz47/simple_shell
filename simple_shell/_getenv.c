#include "shell.h"

/**
 * find_var - finds an environment variable
 * @var: variable
 * @env_var: string to search
 *
 * Return: True (1), or False (0)
 */
int find_var(const char *var, char *env_var)
{
	int i = 0, j = 0;
	char *token;

	if (!env_var || !var)
		return (FALSE);
	while (env_var[i] != '=')
		i++;
	token = malloc(sizeof(char) * (i + 1));
	if (!token)
		return (FALSE);
	while (i)
	{
		token[j] = env_var[j];
		i--;
		j++;
	}
	token[j] = '\0';
	if (_strcmp(token, var))
	{
		free(token);
		return (TRUE);
	}
	free(token);
	return (FALSE);
}

/**
 * copy_env - copies the env array and allocate memory
 * @env: environment
 * @Add_byte: byte to add to env in memory
 *
 * Return: pointer to array copy or Null if failed
 */
char **copy_env(char **env, int Add_byte)
{
	char **envCopy;
	int i = 0, j;

	while (env[i] != NULL)
		i++;
	envCopy = malloc(sizeof(char *) * (i + 1 + Add_byte));
	if (!envCopy)
		return (NULL);
	for (j = 0; j < i; j++)
	{
		envCopy[j] = _strdup(env[j]);
		if (!envCopy[j])
		{
			free_arr_str(envCopy, j, 0);
			free(envCopy);
			return (NULL);
		}
	}
	envCopy[j] = NULL;
	return (envCopy);
}

/**
 * _getenv - gets an environment variable
 * @var: environment variable
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
 * _setenv - sets an environmental variable
 * @ptr: pointer to struct parse
 * @env_cpy: environment
 *
 * Return: void pointer
 */
void *_setenv(parse *ptr, char **env_cpy)
{
	int i = 0, len;
	char *var;
	char **New_env;

	if (ptr->argc != 3)
	{
		write(STDERR_FILENO, "Usage: setenv VARIABLE VALUE\n", 29);
		return (NULL);
	}
	len = _strlen(ptr->args[1]) + _strlen(ptr->args[2]) + 2;
	var = malloc(sizeof(char) * len);
	if (!var)
	{
		perror("malloc");
		return (NULL);
	}
	_strcpy(var, ptr->args[1]);
	_strcat(var, "=");
	_strcat(var, ptr->args[2]);
	while (env_cpy[i] != NULL)
	{
		if (find_var(ptr->args[1], env_cpy[i]))
		{
			free(env_cpy[i]);
			env_cpy[i] = var;
			return (NULL);
		}
		i++;
	}

	New_env = copy_env(env_cpy, 1);
	if (!New_env)
	{
		free(var);
		perror("malloc");
	        return (NULL);
	}
	New_env[i] = var;
	New_env[i + 1] = NULL;
	free_arr_str_all(env_cpy, 0, 0);
	env_cpy = New_env;
	return (env_cpy);
}

/**
 */
void *_unsetenv(parse *ptr, char **env_cpy)
{
	int i = 0, len;
	char *var;
	char **New_env;

	if (ptr->argc != 2)
	{
		write(STDERR_FILENO, "Usage: unsetenv VARIABLE\n", 25);
		return (NULL);
	}
}
