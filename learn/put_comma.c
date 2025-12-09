#include "../libft/libft.h"

static int	count_words(char *str)
{
	int	i;
	int	count;
	int	inword;

	count = 0;
	inword = 0;
	i = 0;
	while (str[i++])
	{
		if (inword && (' ' == str[i] || '\0' != str[i + 1]))
			count++;
		if (' ' == str[i])
			inword = 0;
		else
			inword = 1;
	}
	return (count);
}


int	main(void)
{
	printf("%d\n",count_words("hello i need how many commas??"));
	printf("%d\n",count_words(" hello i need how many commas??"));
	printf("%d\n",count_words(" hello i need how many commas?? "));
	return (0);
}