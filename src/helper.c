#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>/*for access*/
#include <fcntl.h>/*for open*/
#include <time.h>
#include <sys/wait.h>/*for WIFEXITED*/
#include "../libft/libft.h"


char	**find_arg(char *cmd, char *append)
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

char	*prefix_str(char *word, char prefix)
{
	int	len;
	char	*str;

	str = word;
	len = ft_strlen(str);
	ft_memmove(&str[1], &str[0], len * sizeof(char));
	str[0] = prefix;
	return (str);
}