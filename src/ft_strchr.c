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

int	is_quott(char c)
{
	if (c == 34 || c == 39)
		return (1);
	return (0);
}

int	is_red(char c)
{
	if (c == 60 || c == 62)
		return (1);
	return (0);
}

int	is_echo(char *s)
{
	if (!s[0] || !s[1] || !s[2] || !s[3])
		return (0);
	if (s[0] == 'e' && s[1] == 'c' && s[2] == 'h'
		&& s[3] == 'o' && (s[4] == ' ' || s[4] == '\0'))
		return (1);
	else
		return (0);
}
