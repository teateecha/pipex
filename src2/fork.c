#include <fcntl.h>/*for open, access*/
#include <unistd.h>/*for FILENO Makros and close()*/
#include <stdlib.h>/*for Exit status*/
#include "../libpipex.h"
#include "../libft/libft.h"/*for ft_split*/

extern char **environ;

static char	*find_path(char *cmd)
{
	char	*path;
	return (path);
}

static void	ft_free(char **nullwords, size_t j)
{
	size_t	i;
		int	j;

	j = 0;
	while (nullwords[j])
		j++;
	i = 0;
	if (!nullwords)
		return ;
	while (i <= j && nullwords[i] != NULL)
	{
		free(nullwords[i]);
		i++;
	}
	free(nullwords);
}

static void	child(int fd[2], char **argv, int cmd, int fdf)
{
	char	**arr;

	close(fdf);
	close(fd[1]);
	close(fd[0]);
	arr = ft_split(argv[cmd]);
	execve(find_path(arr[cmd]), arr, environ);
	ft_free(arr)
}

static int	get_child(void)
{
	int	pid;

	pid = fork();
	if (-1 == pid)
		ft_exit(EXIT_FAILURE);
	return (pid);
}

void	parent(char **argv, int fd[2],)
{
	int	pid1;
	int	pid2;
	int	fdf;

	pid1 = get_child();
	if (0 == pid1)
	{
		fdf = open(argv[1], O_RDONLY);
		if (0 > fdf)
			ft_error();
		dup2(fd[1], STDOUT_FILENO);
		dup2(fdf, STDIN_FILENO);
		child(fd, argv, fdf, 2);
	}
	pid2 = get_child();
	if (0 == pid2)
	{
		fdf = open(argv[4], O_WRONLY | O_CREAT, 0777);
		dup2(fd[0], STDIN_FILENO);
		child(fd, argv, fdf, 3);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

