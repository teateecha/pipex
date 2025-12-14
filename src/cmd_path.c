#include "../libpipex.h"
#include <stdio.h> /*for perror*/

static char	**extract_paths_from_env(char **env, t_data *data)
{
	int		i;

	i = 0;
	while (env[i] && ft_memcmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
		cleanup_and_exit(127, "no PATH in environment", data);
	return (ft_split(env[i] + 5, ':'));
}

void	get_path(t_data *data, char **env)
{
	int	i;

	i = 0;
	data->paths = extract_paths_from_env(env, data);
	if (NULL == data->paths)
		cleanup_and_exit(127, "split failed", data);
	while (data->paths[i])
	{
		data->path = ft_strjoinjoin(data->paths[i], "/", data->arr[0]);
		if (NULL == data->path)
			cleanup_and_exit(EXIT_FAILURE, "strjoinjoin failed", data);
		if (access(data->path, X_OK) == 0)
			return ;
		free(data->path);
		data->path = NULL;
		i++;
	}
	if (data->arr && data->arr[0])
		cleanup_and_exit(127, data->arr[0], data);
	cleanup_and_exit(127, "command not found", data);
}
