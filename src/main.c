#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>/*for access*/
#include <fcntl.h>/*for open*/
#include <time.h>
#include <sys/wait.h>/*for WIFEXITED*/
#include "../libft/libft.h"
#include "../libpipex.h"

extern char	**environ;

static char	*find_path(char *cmd)
{
	char	**path;
	char	*str;
	int	i;

	i = 0;
	while (ft_memcmp(environ[i], "PATH", 4))
		i++;
	str = ft_memchr(environ[i - 1], '/', ft_strlen(environ[i - 1]));
	path = ft_split(str, ':');
	if (NULL == path)
		return(NULL);
	i = -1;
	while (path[++i])
	{
		str = ft_strjoinjoin(path[i], "/", cmd);
		if (NULL == str)
			return (NULL);
		if (0 == access(cmd, X_OK))
		{
			ft_free_arr(path);
			return (str);
		}
		free(str);
		str = NULL;
	}
	ft_free_arr(path);
	path = NULL;
	return (NULL);
}

static int	do_child1(int fd[2], char **argv)
{
	char	**argu;

	argu = find_arg(argv[2], argv[1]);
	if (NULL == argu)
		return (EXIT_FAILURE);
	if (0 > dup2(fd[1], STDOUT_FILENO))
		return (EXIT_FAILURE);
	close(fd[0]);
	close(fd[1]);
	execve(find_path(argu[0]), argu, environ);
	perror("execve");
	return (EXIT_FAILURE);/*todo exit*/
}

static int	do_child2(int fd[2], char **argv)
{
	int		fd_file;
	char	**argu;

	argu = find_arg(argv[3], NULL);
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
	execve(find_path(argu[0]), argu, environ);
	perror("execve");
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
