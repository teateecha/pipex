#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>/*for WIFEXITED*/
#include <fcntl.h>/*open*/

int	main(int argc, char **argv, char **envp)
{
	int	pid = fork();
	int	err;
	int	wstatus;
	int	statusCode;

	if(-1 == pid)
		return (1);
	if (0 == pid)
	{
		int file = open("pingResult.txt", O_WRONLY | O_CREAT, 0777);/*bitwise or for the flags, 0777 the 0 tells it is an octal value everybody can read or write from it*/
		if (-1 == file)
			return (2);
		dup2(file, STDOUT_FILENO);
		close(file);
		err = execlp("ping", "ping", "-c", "3", "google.com", NULL);
		printf("error is: %d\n", err);
		return (2);
	}
	else
	{
		wait(&wstatus);
		if(WIFEXITED(wstatus))
		{
			statusCode = WEXITSTATUS(wstatus);
			if(0 == statusCode)
				printf("Success!\n");
			else
				printf("Failure with status code %d\n", statusCode);
		}
	}
	return (0);
}
