#include "../inc/minishell.h"

int	build_pwd(void)
{
	char	*str;
	char	s[100];

	str = getcwd(s, 100);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	if (str == NULL)
		return (1);
	return (0);
}