#include "../libpipex.h"

// static void	copy_arguments(t_data *data, char **argu, char *file)
// {
// 	size_t	i;

// 	i = -1;
// 	while (argu[++i])
// 	{
// 		data->arr[i] = ft_strdup(argu[i]);
// 		if (NULL == data->arr[i])
// 		{
// 			ft_free_arr(data->arr);
// 			ft_free_arr(argu);
// 			cleanup_and_exit(EXIT_FAILURE, "strdup", data);
// 		}
// 	}
// 	data->arr[i++] = ft_strdup(file);
// 	if (NULL == data->arr[i - 1])
// 	{
// 		ft_free_arr(data->arr);
// 		ft_free_arr(argu);
// 		cleanup_and_exit(EXIT_FAILURE, "strdup", data);
// 	}
// 	data->arr[i] = NULL;
// 	ft_free_arr(argu);
// 	argu = NULL;
// }

// /*splits cmd in char ** and appends file to this array*/
// void	get_args(t_data *data, char *cmd, char *file)
// {
// 	char	**argu;
// 	size_t	i;

// 	argu = ft_split(cmd, ' ');
// 	if (NULL == argu)
// 		cleanup_and_exit(EXIT_FAILURE, "ft_split", data);
// 	i = 0;
// 	while (argu[i])
// 		i++;
// 	data->arr = (char **)malloc(sizeof(char *) * (i + 2));
// 	if (NULL == data->arr)
// 	{
// 		ft_free_arr(argu);
// 		cleanup_and_exit(EXIT_FAILURE, "malloc", data);
// 	}
// 	copy_arguments(data, argu, file);
// }

static char	**extract_paths_from_env(char **env, t_data *data)
{
	int		i;

	i = 0;
	while (env[i] && ft_memcmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
		cleanup_and_exit(0, "no PATH variable found", data);
	return (ft_split(env[i] + 5, ':'));
}

void	get_path(t_data *data, char **env)
{
	int		i;

	data->paths = extract_paths_from_env(env, data);
	if (NULL == data->paths)
		cleanup_and_exit(EXIT_FAILURE, "split failed or no PATH var", data);
	i = 0;
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
	cleanup_and_exit(EXIT_FAILURE, "no executable path found", data);
}