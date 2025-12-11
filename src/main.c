#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>/*for open*/
#include <time.h>
#include <sys/wait.h>/*for WIFEXITED*/
#include "../libft/libft.h"

static char	**find_arg(char *cmd)
{
	char	**arguments;

	arguments = ft_split(cmd, ' ');
	if (NULL == arguments)
		return (NULL);
	return (arguments);
}


static int	do_child1(int fd[2], char **argv)
{
	char	**argu;

	argu = find_arg(argv[2]);
	if (NULL == argu)
		return (EXIT_FAILURE);
	if (0 > dup2(fd[1], STDOUT_FILENO))
		return (EXIT_FAILURE);
	close(fd[0]);
	close(fd[1]);
	execvp(argu[0], argu);
	perror("execvp");
	return (EXIT_FAILURE);/*todo exit*/
}

static int	do_child2(int fd[2], char **argv)
{
	int		fd_file;
	char	**argu;

	argu = find_arg(argv[3]);
	if (0 > dup2(fd[0], STDIN_FILENO))
		return (EXIT_FAILURE);
	fd_file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (0 > fd_file)
		return (EXIT_FAILURE);
	if (0 > dup2(fd_file, STDOUT_FILENO))
		return (EXIT_FAILURE);
	close(fd_file);
	close(fd[0]);
	close(fd[1]);
	execvp(argu[0], argu);
	perror("execvp")
	return (EXIT_FAILURE);/*todo exit*/
}

int	main(int argc, char **argv)
{
	int	pid1;
	int	pid2;
	int	fd[2];

	if (0 < pipe(fd))
		return (EXIT_FAILURE);
	pid1 = fork();
	if (0 > pid1)
		return (EXIT_FAILURE);
	if (0 == pid1)
		return (do_child1(fd, argv));
	pid2 = fork();
	if (0 > pid2)
		return (EXIT_FAILURE);
	if (0 == pid2)
		return (do_child2(fd, argv));
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
