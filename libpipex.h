#ifndef LIBPIPEX_H
# define LIBPIPEX_H

typedef struct s_data
{
	char	**arr;
}			t_data;

char	**find_arg(char *cmd, char *append);
char	*prefix_str(char *word, char prefix);
char	*ft_strjoinjoin(char const *s1, char const *s2, char const *s3);
void	cleanup_and_exit(int exit_code, const char *message, t_data *res);
#endif