#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char *lineptr = NULL;

void cleanup(void)
{
	free(lineptr);
}

void sigintHandler(int sig)
{
	printf("\n");
	exit(0);
}

char *mygetline(void)
{
	size_t n = 0;
	int nread;

	nread = getline(&lineptr, &n, stdin);
	if (nread == -1)
		return (NULL);

	lineptr[nread - 1] = '\0';
	return (lineptr);
}

void myfork(void)
{
	pid_t child_pid;
	char *argv[] = {lineptr, NULL};
	int status;

	child_pid = fork();
	if (child_pid == -1)
		exit(0);
	else if (child_pid == 0)
	{
		if (execve(argv[0], argv, NULL) == -1)
		{
			exit(0);
		}
	}
	else
	{
		wait(&status);
	}
}

int main(void)
{
	atexit(cleanup);
	signal(SIGINT, sigintHandler);

	while (1)
	{
		printf("#cisfun:) ");

		lineptr = mygetline();
		if (!lineptr)
			return (1);

		myfork();

		free(lineptr);
		lineptr = NULL;
	}
	return (0);
}
