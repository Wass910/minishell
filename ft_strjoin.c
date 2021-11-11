#include "minishell.h"

static int		ft_count(char const *s1, char const *s2)
{
	int i;
	int e;

	i = 0;
	e = 0;
	while (s1[i] != '\0')
		i++;
	while (s2[e] != '\0')
	{
		e++;
		i++;
	}
	i = i + 2;
	return (i);
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	int		e;
	int		i;
	char	*str;

	e = 0;
	i = ft_count(s1, s2);
	if (!(str = malloc(sizeof(*str) * i)))
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
    str[i] = 'a';
    i++;
	while (s2[e] != '\0')
	{
		str[i] = s2[e];
		i++;
		e++;
	}
	str[i] = '\0';
	return (str);
}