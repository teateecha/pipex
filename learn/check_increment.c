#include <stdio.h>

int	main(void)
{
	int	i;

	i = 0;
	printf("i++ extra\n");
	while (i < 3)
	{
		printf("%d\t", i);
		i++;
	}
	i = 0;
	printf("\n\ni++\n");
	while (i++ < 3)
		printf("%d\t", i);
	printf("\n\n++1\n");
	i = 0;
	while (++i < 3)
		printf("%d\t", i);
	return (0);
}
