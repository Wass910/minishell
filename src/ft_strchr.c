#include "../inc/minishell.h"

int	ft_strchr(char *s, int c)
{
	int		i;
	int		nb_chr;

	i = 0;
	nb_chr = 0;
	while (s && s[i] != '\0')
	{
		if (s[i] == c)
			nb_chr++;
		i++;
	}
	return (nb_chr);
}

int	ft_double_strchr(char *s, int c)
{
	int		i;
	int		nb_chr;

	i = 0;
	nb_chr = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] == c && s[i - 1] && s[i - 1] == c)
			return (-1);
		if (s[i] == c && s[i + 1] == c)
			nb_chr++;
		i++;
	}
	return (nb_chr);
}	

int	ft_double_strchr_file(char *s, int c)
{
	int		i;
	int		nb_chr;

	i = 0;
	nb_chr = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] == c)
			nb_chr++;
		i++;
	}
	return (nb_chr);
}

int	ft_redir_strchr(char *s, int c)
{
	int		i;
	int		nb_chr;

	i = 0;
	nb_chr = 0;
	while (s[i] != '\0')
	{
		if ((s[i] == c && s[i + 1] != c)
			|| (s[i] == c && s[i + 1] != c && s[i - 1] && s[i - 1] != c))
			nb_chr++;
		i++;
	}
	return (nb_chr);
}
