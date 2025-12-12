#include "libft.h"
#include <stdlib.h>


static char	**ft_fill(size_t w, char const *s, char c, char **words)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	while (s[i])
	{
		len = 0;
		while (s[i] != c && s[i] != '\0')
		{
			len++;
			i++;
		}
		if (len && j < w)
		{
			words[j] = ft_substr(s, (i - len), len);
			if (words[j] == NULL)
				return (ft_free_arr(words), NULL);
			j++;
		}
		i++;
	}
	return (words);
}

static size_t	ft_wordcount(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (s[0] != c && s[0] != '\0')
	{
		i = 1;
		count = 1;
	}
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			count++;
		i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	size_t	w;

	if (!s)
		return (NULL);
	w = ft_wordcount(s, c);
	words = malloc((w + 1) * sizeof(char *));
	if (!words)
		return (NULL);
	else
		words[w] = NULL;
	words = ft_fill(w, s, c, words);
	return (words);
}

#include "libft.h"
#include <stdlib.h>

void	ft_free_arr(char **nullwords)
{
	size_t	i;

	i = 0;
	if (!nullwords)
		return ;
	while (nullwords[i] != NULL)
	{
		free(nullwords[i]);
		nullwords[i] = NULL;
		i++;
	}
	free(nullwords);
	nullwords = NULL;
}

/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	char	*ex[5]= {"lolo",
				"and",
				"this",
				"should",
				"appear???"};
	char	**real;
	int		i;
	int		err;

	printf("\n••••• START\tsplit\t\tTEST •••••\n");
	i = 0;
	err = 0;
	real = ft_split("  lolo and      this should appear???   ",' ');
	if (!real)
		err++;
	else 
		while (i < 4)
		{
			if (memcmp(ex[i],real[i],strlen(ex[i])) != 0)
			{
				printf("ERROR for \t%s>>>\t%s\n", ex[i],real[i]);
				err++;
			}
			else 
				printf("FINE for \t%s\t>>>%s\n", ex[i],real[i]);
			free(real[i]);
			i++;
		}
	free(real);
	printf("ENDED ft_split TEST with \t %d \t ERRORS.\n",err);
	return (0);
}//*/
