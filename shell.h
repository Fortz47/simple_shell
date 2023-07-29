#ifndef SHELL_H
#define SHELL_H

#define TRUE 1
#define FALSE 0
#define BUFFER_SIZE 1024

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>

extern char *shell;

/**
 * struct parse - a struct parse
 * @argc: number of argument parsed
 * @cmd: command
 * @args: array of parsed arguments
 */
typedef struct parse
{
	int argc;
	char *cmd;
	char **args;
} parse;
/**
 * struct built_in - handle builtin cmd
 * @cmd: command
 * @func: function to handle command
 */
typedef struct built_in
{
	char *cmd;
	void (*func)(parse *, char ***, unsigned int *);
} built_in;

int _strcmp(const char *s1, const char *s2);
char *_strdup(char *str);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
int _strlen(char *s);
parse *parse_line(char *line);
void handle_EOF(ssize_t *read, char *buffer, char **env_cpy, unsigned int *n);
int handle_path(parse *parsed, char **env_cpy);
void free_arr_str(char **arr, int i, int j);
int exec_cmd(parse *parsed, char **);
int check_valid(char *filepath);
int return_num_of_arg(char *buffer, const char *delim);
parse *then_free(int count, parse *_return, parse *ptr, ...);
void _then_free(int count, parse *ptr, ...);
int _atoi(char *str);
void then(char *fp, char *t, parse *p, parse *av, int *flag, int *s, char **);
char *getenv_value(const char *var, char **env_cpy);
void (*handle_built_in(char *cmd))(parse *ptr, char ***env_cpy,
		unsigned int *n);
parse *create_struct_parse(int cmd_count, int args_count);
char **copy_env(char **env, int Add_byte);
void _setenv(parse *ptr, char ***env_cpy, unsigned int *n);
void free_arr_str_all(char **arr, int i, int j);
void _unsetenv(parse *ptr, char ***env_cpy, unsigned int *n);
void execute_all(char *buffer, char ***envp, unsigned int *n);
void cd(parse *ptr, char ***env, unsigned int *);

#endif
