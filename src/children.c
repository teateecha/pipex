#include "../libpipex.h"
#include <fcntl.h>/*for open*/

void	do_child1(t_data *data, char **argv, char **env)
{
	if (0 != access(argv[1], R_OK))
		cleanup_and_exit(EXIT_FAILURE, "infile not readable", data);
	dup2(data->fdpipe[1], STDOUT_FILENO);
	close(data->fdpipe[0]);
	close(data->fdpipe[1]);
	data->infile_fd = open(argv[1], O_RDONLY);
	if (data->infile_fd < 0)
		cleanup_and_exit(EXIT_FAILURE, "open infile", data);
	dup2(data->infile_fd, STDIN_FILENO);
	close(data->infile_fd);
	data->arr = ft_split(argv[2], ' ');
	if (NULL == data->arr)
		cleanup_and_exit(EXIT_FAILURE, "ft_split failed", data);
	get_path(data, env);
	execve(data->path, data->arr, env);
	cleanup_and_exit(EXIT_FAILURE, "child1 failed", data);
}

void	do_child2(t_data *data, char **argv, char **env)
{
	dup2(data->fdpipe[0], STDIN_FILENO);
	close(data->fdpipe[1]);
	close(data->fdpipe[0]);
	data->outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (0 > data->outfile_fd)
		cleanup_and_exit(EXIT_FAILURE, argv[4], data);
	dup2(data->outfile_fd, STDOUT_FILENO);
	close(data->outfile_fd);
	data->arr = ft_split(argv[3], ' ');
	if (NULL == data->arr)
		cleanup_and_exit(EXIT_FAILURE, "ft_split failed", data);
	get_path(data, env);
	execve(data->path, data->arr, env);
	cleanup_and_exit(EXIT_FAILURE, "child2 failed", data);
}
