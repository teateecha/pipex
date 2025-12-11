#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../libpipex.h"

static int	ft_exit()

static void	*ft_error()

static void	check_input()
{
	// if (fail)
	// 	ft_exit();
}

read_execute_write(int fdin,int fdout,char *cmd,char **arguments)
/*close the other one, read from in, close it, execute it,close the other one  write it to out , close the out... in and out are different for parent and child*/

static void processs()
{
	int		id;
	char	**arr;
	int		fd;

	id = fork();
	if (-1 == id)
		// ft_exit(..., fail);
	if (0 != id)/*wait for child,*/
		wait(NULL);
	arr = ft_split(argv[2], ' ');
	
	ft_free(arr);
	/*parent and child: split the cmds and arguments,*/
	if (0 == id)/*child: execute cmd with the arguments on the file*/
		fd = 1;
	else/*parent: read form stdout, exec on what i read from stdout*/
		fd = 0;
	// read_execute_write(fdin, fdout, cmd, arguments)
	ft_exti();
	return ;
}


/*creates a pipe,*/
int	main(int argc, char **argv, char **envp)
{
	int			fd[2];
	int			file1;


	if (-1 == pipe(fd))
		return(ft_error);
	/*check input*/
	parent(argv, fd, data);
	// processes(argv);/*forking function: fork, read the cmds and infiles*/
	return (0);
}
