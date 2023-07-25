#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main()
{
	if (execlp("export", "export", "FOOD=BEANS", NULL) == -1)
		perror("error");
	return 0;
}
