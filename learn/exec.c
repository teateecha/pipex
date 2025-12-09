#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int	main(int argc, char **argv, char **envp)
{
	int pid = fork();

	if(-1 == pid)
		return (-1);
	if (0 == pid)
		execlp("ping", "ping", "-c", "3", "google.com", NULL);
	else
	{
		wait(NULL);
		printf("Success!\n");
	}
	printf("post parent or child \n");
	return (0);
}
