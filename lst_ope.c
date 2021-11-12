#include "minishell.h"

t_comm	fill_comm(t_comm comm ,char *cmd)
{
	//printf("c = %s\n", cmd);
  	comm.nb_pipe = ft_strchr(cmd, '|');
  	comm.redir_input = ft_strchr(cmd, '<');
  	comm.redir_output = ft_strchr(cmd, '>');
	comm.single_quote = ft_strchr(cmd, 39);
  	comm.double_quote = ft_strchr(cmd, '"');
	return (comm);
}