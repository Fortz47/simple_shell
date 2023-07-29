#include "shell.h"

char **rm_env(char **env, int index);

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
	int i = 0, j, k = 0;

	while (env[i] != NULL)
		i++;
	envCopy = malloc(sizeof(char *) * (i + 1 + Add_byte));
	if (!envCopy)
		return (NULL);
	for (j = 0; k < i; j++)
	{
		while (!env[j])
			k++;
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
 * getenv_value - gets the value of an environment variable
 * @var: environment variable
 * @env_cpy: environment
 *
 * Return: environment variable or NULL if doesn't exist
 */
char *getenv_value(const char *var, char **env_cpy)
{
	int i = 0, j = 0, k, x;
	char *token;

	while (env_cpy[i] != NULL)
	{
		if (find_var(var, env_cpy[i]))
		{
			while (env_cpy[i][j] != '=')
				j++;
			for (k = j + 1; env_cpy[i][k] != '\0'; k++)
				{ ; }
			k -= j + 1;
			token = malloc(sizeof(char) * (k + 1));
			if (!token)
				return (NULL);
			x = 0;
			j++;
			while (k)
			{
				token[x] = env_cpy[i][j];
				x++;
				j++;
				k--;
			}
			token[x] = '\0';
			return (token);
		}
		i++;
	}
	return (NULL);
}

/**
 * _setenv - sets an environmental variable
 * @ptr: pointer to struct parse
 * @env_cpy: environment
 * @n: number of times enter/return key has been pressed
 */
void _setenv(parse *ptr, char ***env_cpy,
		unsigned int *n __attribute__((unused)))
{
	int i = 0, len = _strlen(ptr->args[1]) + _strlen(ptr->args[2]) + 2;
	char *var;
	char **New_env;

	if (ptr->argc != 3)
	{
		write(STDERR_FILENO, "Usage: setenv VARIABLE VALUE\n", 29);
		return;
	}
	var = malloc(sizeof(char) * len);
	if (!var)
	{
		perror(shell);
		return;
	}
	_strcpy(var, ptr->args[1]);
	_strcat(var, "=");
	_strcat(var, ptr->args[2]);
	while ((*env_cpy)[i] != NULL)
	{
		if (find_var(ptr->args[1], (*env_cpy)[i]))
		{
			free((*env_cpy)[i]);
			(*env_cpy)[i] = var;
			return;
		}
		i++;
	}

	New_env = copy_env((*env_cpy), 1);
	if (!New_env)
	{
		free(var);
		perror(shell);
		return;
	}
	New_env[i] = var;
	New_env[i + 1] = NULL;
	free_arr_str_all(*env_cpy, 0, 0);
	(*env_cpy) = New_env;
}

/**
 * _unsetenv - removes an environment variable
 * @ptr: pointer to struct parse
 * @env_cpy: environment
 * @n: number of times enter/return key has been pressed
 */
void _unsetenv(parse *ptr, char ***env_cpy,
		unsigned int *n __attribute__((unused)))
{
	int i = 0;
	char **New_env;

	if (ptr->argc != 2)
	{
		write(STDERR_FILENO, "Usage: unsetenv VARIABLE\n", 25);
		return;
	}
	while ((*env_cpy)[i] != NULL)
	{
		if (find_var(ptr->args[1], (*env_cpy)[i]))
		{
			New_env = rm_env((*env_cpy), i);
			if (!New_env)
			{
				perror(shell);
				return;
			}
			free_arr_str_all((*env_cpy), 0, 0);
			(*env_cpy) = New_env;
			return;
		}
		i++;
	}
}
