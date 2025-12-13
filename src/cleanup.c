#include <stdio.h>
#include "../libpipex.h"

void	cleanup_and_exit(int exit_code, const char *message, t_data *res)
{
	if(res.arr)
		ft_free_arr(res->arr);
	if (message)
		perror(message);
	if (exit_code)
		exit(exit_code);
	else
		return (0);
}