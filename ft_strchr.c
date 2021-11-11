#include "minishell.h"

int	ft_strchr(char *s, int c)
{
	int		i;
	int		nb_chr;

	i = 0;
    nb_chr = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			nb_chr++;
		i++;
	}
	return (nb_chr);
}