#include <stdio.h>


int	main(void)
{
	int		i;

	i = 0;
	while(i < 5)
	{
		printf("%d\t", i);
		i++;
	}
	printf("\t now: %d\n", i);
	i = 0;
	while(i < 5)
		printf("%d\t", i++);
	printf("\t now: %d\n", i);
	i = 0;
	while(i++ < 5)
		printf("%d\t", i);
	printf("\t now: %d\n", i);
	i = 0;
	while(++i < 5)
		printf("%d\t", i);
	printf("\t now: %d\n", i);
	return (0);
}
