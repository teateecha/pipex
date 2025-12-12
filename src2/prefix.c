#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>/*for access*/
#include <fcntl.h>/*for open*/
#include <time.h>
#include <sys/wait.h>/*for WIFEXITED*/
#include "../libft/libft.h"

static char	*prefix_str(char *word, char prefix)
{
	int	len;
	char	*str;

	str = word;
	len = ft_strlen(str);
	ft_memmove(&str[1], &str[0], len * sizeof(char));
	str[0] = prefix;
	return (str);
}

int main()
{
	char	word[] = "example";
	char	*prefixed_word;

	prefixed_word = prefix_str(word, 'X');
	printf("Prefixed word: %s\n", prefixed_word);
	return (0);
}