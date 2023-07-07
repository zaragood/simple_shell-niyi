#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
	int i;
	pid_t child_pid;
	char *const argv[] = {"./myppid", NULL};
	int status;

	for (i = 0; i < 5; i++)
	{
		child_pid = fork();
		if (child_pid == -1)
    		{
        		return (1);
    		}
		else if (child_pid == 0)
                {
			if (execve(argv[0], argv, NULL) == -1)
			{
				return (1);
			}
                }
		else 
		{
			wait(&status);
		}
	}
	return (0);
}
