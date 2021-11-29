#include "../inc/minishell.h"

int	open_file(char *filename)
{
	char *str;
	int i;
	filename++;
	i = open(filename, O_RDONLY);
	if (i == -1)
	{
		str = strerror(errno);
		printf("%s: %s\n", filename, str);
		return (-1);
	}
	return (i);
}