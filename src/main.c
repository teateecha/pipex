#include <stdio.h> /*for perror*/
#include <fcntl.h>/*for open flags*/
#include <time.h>
#include <sys/wait.h>/*for WIFEXITED*/
#include "../libpipex.h"
#include <errno.h>

static void	init_data(t_data *data, char **env)
{
	if (!data)
		return ;
	data->arr = NULL;
	data->path = NULL;
	data->paths = NULL;
	data->fdpipe[0] = -1;
	data->fdpipe[1] = -1;
	data->infile_fd = -1;
	data->outfile_fd = -1;
}

static int	waitforchildren(t_pids pid)
{
	int		status_code;

	status_code = 0;
	waitpid(pid.p[1], &pid.status[1], 0);
	if (WIFEXITED(pid.status[1]))
		status_code = WEXITSTATUS(pid.status[1]);
	waitpid(pid.p[0], &pid.status[0], 0);
	if (WIFEXITED(pid.status[0]))
		status_code = WEXITSTATUS(pid.status[0]);
	return (status_code);
}

static void	parent(t_data *data, t_pids *pid, char **argv, char **env)
{
	if (0 > pipe(data->fdpipe))
		cleanup_and_exit(EXIT_FAILURE, "pipe failed", data);
	pid->p[1] = fork();
	if (0 > pid->p[1])
		cleanup_and_exit(EXIT_FAILURE, "fork of child 1 failed", data);
	if (0 == pid->p[1])
		do_child1(data, argv, env);
	pid->p[0] = fork();
	if (0 > pid->p[0])
		cleanup_and_exit(EXIT_FAILURE, "fork of child 2 failed", data);
	if (0 == pid->p[0])
		do_child2(data, argv, env);
	close(data->fdpipe[0]);
	close(data->fdpipe[1]);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_pids	pid;
	int		status_code;

	if (argc != 5)
		cleanup_and_exit(EXIT_FAILURE, "wrong usage", NULL);
	init_data(&data, envp);
	parent(&data, &pid, argv, envp);
	status_code = waitforchildren(pid);
	return (cleanup_and_return(status_code, NULL, &data));
}
