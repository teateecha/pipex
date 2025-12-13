#include <stdio.h>
#include "../libpipex.h"

/* free owned resources but do NOT call exit */
static void	cleanup_resources(t_data *res)
{
	if (!res)
		return ;
	if (res->arr)
		ft_free_arr(res->arr);
	if (res->path)
	{
		free(res->path);
		res->path = NULL;
	}
	// if (res->pids)
	// {
	// 	free(res->pids);
	// 	res->pids = NULL;
	// }
	if (res->infile_fd > 2)
	{
		close(res->infile_fd);
		res->infile_fd = -1;
	}
	if (res->outfile_fd > 2)
	{
		close(res->outfile_fd);
		res->outfile_fd = -1;
	}
}

/* cleanup and return an error code to caller (prefer in helpers) */
int	cleanup_and_return(int exit_code, const char *msg, t_data *res)
{
	if (msg)
		perror(msg);
	cleanup_resources(res);
	return (exit_code);
}

/* cleanup and exit the program (call from main only) */
void	cleanup_and_exit(int exit_code, const char *msg, t_data *res)
{
	if (msg)
		perror(msg);
	cleanup_resources(res);
	exit(exit_code);
}
