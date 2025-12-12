#include <stdio.h>
#include "../libft/libft.h"

extern char	**environ;

int	main(void)
{
	int i;

	i = 0;
	while (environ[i])
	{
		printf("%d ", i);
		if (0 == ft_memcmp(environ[i], "PATH", 4))
			printf("\n%s\n", environ[i]);
		i++;
	}
	return(0);
}

