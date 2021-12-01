#include "../inc/minishell.h"

int	ft_count_str(char *s1, char *s2)
{
	int	i;
	int	e;

	i = 0;
	e = 0;
	while (s1 != NULL && s1[i] != '\0')
		i++;
	while (s2 && s2[e] != '\0')
	{
		e++;
		i++;
	}
	i = i + 2;
	return (i);
}

char	*ft_strcat(char *dest, char *src)
{
	unsigned int	i;
	unsigned int	j;
	char			*tmp;

	tmp = malloc(sizeof(char) * (ft_count_str(dest, src) + 2));
	if (!tmp)
		return (0);
	i = 0;
	while (dest && dest[i] != '\0')
	{
		tmp[i] = dest[i];
		i++;
	}
	tmp[i] = ' ';
	i++;
	j = 0;
	while (src && src[j] != '\0')
	{
		tmp[i] = src[j];
		i++;
		j++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*ft_strcat_ns(char *dest, char *src)
{
	unsigned int	i;
	unsigned int	j;
	char			*tmp;

	tmp = malloc(sizeof(char) * (ft_count_str(dest, src) + 1));
	if (!tmp)
		return (0);
	i = 0;
	while (dest && dest[i] != '\0')
	{
		tmp[i] = dest[i];
		i++;
	}
	j = 0;
	while (src && src[j] != '\0')
	{
		tmp[i] = src[j];
		i++;
		j++;
	}
	tmp[i] = '\0';
	return (tmp);
}

t_cat	cat_setup(t_cat scat, char *dest, char *src)
{
	scat.i = 0;
	scat.k = 0;
	scat.j = 0;
	scat.tmp = malloc(sizeof(char) * (ft_count_str(dest, src) + 3));
	if (!scat.tmp)
		exit(EXIT_FAILURE);
	return (scat);
}

char	*ft_strcat_cote(char *dest, char *src)
{
	t_cat	scat;

	scat = cat_setup(scat, dest, src);
	while (dest && dest[scat.k] != '\0')
	{
		if (scat.k >= 1 && dest[scat.k - 1] == '=')
		{
			scat.tmp[scat.i] = '"';
			scat.i++;
		}
		scat.tmp[scat.i] = dest[scat.k];
		scat.i++;
		scat.k++;
	}
	scat.tmp[scat.i] = '"';
	scat.i++;
	while (src && src[scat.j] != '\0')
	{
		scat.tmp[scat.i] = src[scat.j];
		scat.i++;
		scat.j++;
	}
	scat.tmp[scat.i] = '\0';
	return (scat.tmp);
}
