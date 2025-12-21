#ifndef LIBPIPEX_H
# define LIBPIPEX_H

# include <stdlib.h>
# include <unistd.h>/*for close, access, open ,fork, execve, pipe, dup2*/
# include <sys/types.h> /* for pid_t */
# include "libft/libft.h"

/* data container used across the program */
typedef struct s_data
{
	char	**arr;
	char	*path;
	char	**paths;
	int		fdpipe[2];
	int		infile_fd;
	int		outfile_fd;
}			t_data;


/* process tracking */
typedef struct s_pids
{
	pid_t	p[2];
	int		status[2];
}			t_pids;

void	do_child1(t_data *data, char **argv, char **env);
void	do_child2(t_data *data, char **argv, char **env);
void	cleanup_and_exit(int exit_code, const char *msg, t_data *res);
int		cleanup_and_return(int exit_code, const char *msg, t_data *res);
char	*ft_strjoinjoin(char const *s1, char const *s2, char const *s3);
void	get_path(t_data *data, char **env);
#endif
