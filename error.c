#include "shell.h"

/**
 */
void puts_int(unsigned int n)
{
	char digit;

	if (n == 0)
	{
		write(STDERR_FILENO, "0", 1);
		return;
	}

	if (n / 10 != 0)
	{
		puts_int(n / 10);
	}

	digit = (n % 10) + '0';
	write(STDERR_FILENO, &digit, 1);
}


/**
 */
void error_notFound(char *cmd, unsigned int *n)
{
	char *msg = ": not found\n";

	write(STDERR_FILENO, shell, _strlen(shell));
	write(STDERR_FILENO, ": ", 2);
	puts_int(*n);
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, cmd, _strlen(cmd));
	write(STDERR_FILENO, msg, _strlen(msg));
}
