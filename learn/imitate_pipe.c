#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>/*for WIFEXITED*/
#include <fcntl.h>/*open*/

int	main(int argc, char **argv, char **envp)
{
	int fd[2];
	int	pid1;
	int	pid2;

	if(-1 == pipe(fd))
		return (1);
	pid1 = fork();
	if (0 > pid1)
		return (2);
	if (0 == pid1)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("ping", "ping", "-c", "5", "google.com", NULL);
	}
	pid2 = fork();
	if (0 > pid2)
		return (2);
	if (0 == pid2)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("grep", "grep", "rtt", NULL);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	
	return (0);
}
