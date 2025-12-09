#include <fcntl.h>/*for open*/
#include <unistd.h>/*for FILENO Makros and close()*/
#include <stdlib.h>/*for Exit status*/
#include "../libpipex.h"

static void	child1(t_family data, int fd[2], char **argv)
{
	char	**envp
	int		fdf;

	/*get envp*/
	/*what exactly is the pathname?-isargv[2] enough*/
	fdf = open(argv[1], O_RDONLY);
	dup2(fd[1], STDOUT_FILENO);
	dup2(fdf, STDIN_FILENO);
	close(fdf);
	close(fd[1]);
	close(fd[0]);
	execve(argv[2], argv[1], envp);
	close(1,);
}

static int	get_child(void)
{
	int	pid;

	pid = fork();
	if (-1 == pid)
		ft_exit(EXIT_FAILURE);
	return (pid);
}

void	parent(char **argv, int fd[2], t_family data)
{
	int	pid1;
	int	pid2;

	pid1 = get_child();
	if (0 == pid1)
		child1(data, fd, argv);
	pid2 = get_child();
	if (0 == pid2)
		child2();
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

static void	child2(char **argv, int fd[2])
{
	int		fdf;
	char	**envp;

	fdf = open(argv[4], O_WRONLY | O_CREAT, 0777);
	dup2(fd[0], STDIN_FILENO);
	close(fdf);
	close(fd[1]);
	close(fd[0]);
	execve(argv[2], argv[1], envp);
}
