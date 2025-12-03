#include <unistd.h>/*for fork*/
#include <string.h>
#include <stdio.h>/*for printf and fflush*/
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <errno.h>

/*fflush forces a immediate printf*/
int	main(int argc, char **argv)
{
	int	arr[] = {1, 2, 3, 4, 1, 2, 1, 1, 1};
	int	fd[2];
	int	id1;
	int	id2;
	int	start;
	int	end;
	int	arrSize;

	if (pipe(fd) == -1)
		return (1);
	id1 = fork();
	if (id1 == -1)
		return (2);
	arrSize = sizeof(arr) / sizeof(int);
	if (id1 == 0)
	{
		start = 0;
		end = arrSize / 3;
	}
	else
	{
		id2 = fork();
		if (-1 == id2)
			return (2);
		if (0 == id2)
		{
			start = arrSize / 3;
			end = 2 * arrSize / 3;
		}
		else
			start = 2 * arrSize / 3;
			end = arrSize;
	}
	int sum  = 0;
	int i;
	i = start - 1;
	while (++i < end)
		sum += arr[i];
	printf("Calculated sum %d\t start: %d, end: %d \n", sum, start, end);
	if (0 == id1 || 0 == id2)
	{
		close(fd[0]);
		if ( -1 == write (fd[1], &sum, sizeof(sum)))
			return (3);
		close(fd[1]);
		printf("sum: %d, id1: %d, id2: %d\n", sum, id1, id2);
	}
	else
	{
		int sumFromChild;
		int sumFromChild2;
		close(fd[1]);
		/*check for errors form read or write*/
		if ( -1 == read(fd[0], &sumFromChild, sizeof(sumFromChild)))
			return (4);
		if (-1 == read(fd[0], &sumFromChild2, sizeof(sumFromChild2)))
			return (4);
		close(fd[0]);
		printf("Total sum is %d\n", sum + sumFromChild + sumFromChild2);
	}
	return (0);
}
