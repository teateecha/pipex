#include "../libft/libft.h"
#include <stdio.h>

static char	**find_arg(char *cmd, char *append)
{
	char	**arguments;
	int		i;

	arguments = ft_split(cmd, ' ');
	if (NULL == arguments)
		return (NULL);
	if (append)
	{
		i = 0;
		while (arguments[i])
			i++;
		arguments[i] = append;
		arguments[i + 1] = NULL;
	}
	return (arguments);
}

int	main(void)
{
	char	*cmd;
	char	*append;
	int		i;
	char	**arr;

	cmd = "first second third";
	append = "last";
	arr = find_arg(cmd, append);
	i = 0;
	while (arr[i])
	{
		printf("%d: %s\n", i, arr[i]);
		i++;
	}
	return (0);
}