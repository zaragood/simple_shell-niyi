#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

char *lineptr = NULL;

/**
 * sigintHandler - Handles the SIGINT signal (Ctrl+C)
 * @sig: The signal number (not used in the function)
 *
 * Frees the dynamically allocated memory for 'lineptr' and
 * terminates the program.
 */
void sigintHandler(int sig)
{
	(void) sig;
	free(lineptr);
	printf("\n");
	exit(0);
}

/**
 * mygetline - Reads a line of input from stdin
 *
 * Reads a line of input from stdin and stores it in the 'lineptr' variable
 * Dynamically allocates memory for 'lineptr' to accommodate the input line
 *
 * Return: the pointer to the input line (or NULL if no input is available).
 */
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

/**
 * myfork - Creates a child process and executes a command
 */
void myfork(void)
{
	pid_t child_pid;
	char **argv = malloc(2 * sizeof(char *));
	int status;

	argv[0] = lineptr;
	argv[1] = NULL;

	child_pid = fork();
	if (child_pid == -1)
		exit(0);
	else if (child_pid == 0)
	{
		if (execve(argv[0], argv, NULL) == -1)
			exit(0);
	}
	else
		wait(&status);

	free(argv);
}

/**
 * main - Entry point of the program
 *
 * Return: 0 on successful completion
 */
int main(void)
{
	/* The SIGINT signal handler to handle Ctrl+C interrupts */
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
