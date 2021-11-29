#include "../inc/minishell.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (6);
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	ft_strlen_glitch(char *s)
{
	int	i;
	int temp;
	i = 0;
	temp = 0;
	if (s == NULL)
		return (6);
	while (s[i] != '\0')
	{
		if (s[i] == 24)
			temp++;
		i++;
	}
	return (i - temp);
}