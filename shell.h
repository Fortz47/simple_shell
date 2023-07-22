#ifndef SHELL_H
#define SHELL_H

#define TRUE 1
#define FALSE 0
#define BUFFER_SIZE 1024

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

/**
 */
typedef struct parse
{
	int argc;
	char *cmd;
	char **args;
} parse;

extern char **environ;

int _strcmp(const char *s1, const char *s2);
char *_strdup(char *str);
char *_strcat(char *dest, char *src);
parse *parse_line(char *line);
void handle_EOF(ssize_t *read, char *buffer);
int handle_path(parse *parsed, char **envp);
void free_arr_str(char **arr, int i, int j);
int exec_cmd(parse *parsed, char **);
int check_valid(char *filepath);
int return_num_of_arg(char *buffer);
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);
char *_strcpy(char *dest, const char *src);
#endif
