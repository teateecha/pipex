#ifndef LIBPIPEX_H
# define LIBPIPEX_H

/* data container used across the program */
typedef struct s_data
{
	char	**arr;/* argv/command split (owned) */
	char	*path;/* constructed exec path (owned) */
	int		infile_fd;/* input fd (-1 if unused) */
	int		outfile_fd;/* output fd (-1 if unused) */
	char	**envp;		/* environment pointer (NOT owned) */
}	t_data;

/*
**	pid_t	*pids;
**	size_t	n_children;
*/

char	**find_arg(char *cmd, char *append);
char	*prefix_str(char *word, char prefix);
char	*ft_strjoinjoin(char const *s1, char const *s2, char const *s3);
int		cleanup_and_return(int exit_code, const char *msg, t_data *res);
void	cleanup_and_exit(int exit_code, const char *msg, t_data *res);
#endif