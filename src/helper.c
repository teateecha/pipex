// #include <fcntl.h>/*for open*/
// #include <time.h>
// #include <sys/wait.h>/*for WIFEXITED*/
#include "../libpipex.h"

void	init_data(t_data *data, char **env)
{
	if (!data)
		return;
	data->arr = NULL;
	data->path = NULL;
	data->infile_fd = -1;
	data->outfile_fd = -1;
}

char	**find_arg(char *cmd, char *append)
{
	char	**new_args;
	char	**arguments;
	int		i;

	arguments = ft_split(cmd, ' ');
	if (NULL == arguments)
		return (NULL);
	if (NULL == append)
		return (arguments);
	i = 0;
	while (arguments[i])
		i++;
	new_args = (char **)malloc(sizeof(char *) * (i + 2));
	if (NULL == new_args)
		return(ft_free_arr(arguments), NULL);
	i = -1;
	while(arguments[++i])
		new_args[i] = arguments[i];
	new_args[i++] = append;
	new_args[i] = NULL;
	free(arguments);
	arguments = NULL;
	return (new_args);
}

static void	ft_copy_part(char *dst, char const *src, size_t *index)
{
	size_t	len;

	len = ft_strlen(src);
	ft_memcpy(dst + *index, src, len);
	*index += len;
}

char	*ft_strjoinjoin(char const *s1, char const *s2, char const *s3)
{
	char	*new;
	size_t	len;
	size_t	i;

	if (!s1 || !s2 || !s3)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	new = (char *)malloc((len + 1) * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	ft_copy_part(new, s1, &i);
	ft_copy_part(new, s2, &i);
	ft_copy_part(new, s3, &i);
	new[i] = '\0';
	return (new);
}
