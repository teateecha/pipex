#include <unistd.h>/*for fork*/
#include <time.h>

int	main(int argc, char **argv)
{
	int	n;
	int	id;
	int	i;

	id = fork();
	if (0 == id)
		n = 1;
	else
		n = 6;
	if (id != 0)
		wait();

	for (i = n; i < n + 5; i++)
	{
		printf("%d, ", n);
		fflush(stdout);
	}
	if (id != 0)
		printf(\n);
	return (0);
}
