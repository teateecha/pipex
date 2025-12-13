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
	char	**paths;
	char	*path_env;
	char	*candidate;
	int		i;

	i = 0;
	while (environ[i] && ft_memcmp(environ[i], "PATH=", 5) != 0)
		i++;
	if (!environ[i])
		return (NULL);
	path_env = environ[i] + ft_strlen("PATH=");
	paths = ft_split(path_env, ':');
	if (NULL == paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		candidate = ft_strjoinjoin(paths[i], "/", cmd);
		if (NULL == candidate)
		{
			ft_free_arr(paths);
			return (NULL);
		}
		if (access(candidate, X_OK) == 0)
		{
			ft_free_arr(paths);
			return (candidate);
		}
		free(candidate);
		candidate = NULL;
		i++;
	}
	ft_free_arr(paths);
	return (NULL);
}

static int	do_child1(int fd[2], char **argv)
{
	char	**argu;
	char	*cmd_path;

	argu = find_arg(argv[2], argv[1]);
	if (NULL == argu)
		return (EXIT_FAILURE);
	if (0 > dup2(fd[1], STDOUT_FILENO))
		return (EXIT_FAILURE);
	close(fd[0]);
	close(fd[1]);
	cmd_path = find_path(argu[0]);
	if (NULL == cmd_path)
	{
		perror("find_path");
		return (EXIT_FAILURE);
	}
	execve(cmd_path, argu, environ);
	perror("execve");
	free(cmd_path);
	return (EXIT_FAILURE);/*todo exit*/
}

static int	do_child2(int fd[2], char **argv)
{
	int		fd_file;
	char	**argu;
	char	*cmd_path;

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
	cmd_path = find_path(argu[0]);
	if (NULL == cmd_path)
	{
		perror("find_path");
		return (EXIT_FAILURE);
	}
	execve(cmd_path, argu, environ);
	perror("execve");
	free(cmd_path);
	return (EXIT_FAILURE);/*todo exit*/
}

int	main(int argc, char **argv)
{
	int	pid1;
	int	pid2;
	int	fd[2];
	int	*wait_child1;
	int	*wait_child2;

	if (argc != 5)
	{
		perror("Usage: ./pipex file1 cmd1 cmd2 file2");
		return (EXIT_FAILURE);
	}
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
	waitpid(pid1, wait_child1, 0);
	waitpid(pid2, wait_child2, 0);
	if (WIFEXITED(wait_child1) || WIFEXITED(wait_child2))
		status_Code = WEXITSTATUS(wait_child1) + WEXITSTATUS(wait_child2);
	return (wait_child1 | wait_chid2);
}
