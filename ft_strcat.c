
#include "minishell.h"

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

char	*ft_strcat_cmd(char *dest, char *src)
{
	unsigned int	i;
	unsigned int	j;
	char			*tmp;

	tmp = malloc(sizeof(char) * (ft_count_str(dest, src) + 2));
	if (!tmp)
		return (0);
	i = 0;
	while (dest[i] != '\0')
	{
		tmp[i] = dest[i];
		i++;
	}
	j = 0;
	tmp[i] = '/';
	i++;
	while (src[j] != '\0')
	{
		tmp[i] = src[j];
		i++;
		++j;
	}
	tmp[i++] = '\0';
	return (tmp);
}

char	*ft_strcat_cote(char *dest, char *src)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;
	char			*tmp;

	tmp = malloc(sizeof(char) * (ft_count_str(dest, src) + 3));
	if (!tmp)
		return (0);
	i = 0;
	k = 0;
	while (dest && dest[k] != '\0')
	{
		if (k >= 1 && dest[k - 1] == '=')
		{
			tmp[i] = '"';
			i++;
		}
		tmp[i] = dest[k];
		i++;
		k++;
	}
	tmp[i] = '"';
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