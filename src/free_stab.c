#include "../inc/minishell.h"

void	free_str(char **str)
{
	int	line;

	line = 0;
	while (str[line])
	{
		free(str[line]);
		line++;
	}
	free(str);
}

void	free_comm(t_comm comm)
{
	int	i;

	i = 0;
	if (comm.cmd)
		free_str(comm.cmd);
	if (comm.env)
		free_str(comm.env);
	if (comm.path)
		free(path);
	if (comm.redir)
		free_str(comm.redir);
	if (comm.redir_temp)
		free_str(comm.redir_temp);
}
