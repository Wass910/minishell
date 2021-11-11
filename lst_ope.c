#include "minishell.h"

t_comm	*fill_comm(t_comm *comm, char *cmd, int nb)
{
	t_comm	*new;

	new = malloc(sizeof(*new));
	if (new == NULL)
		exit(EXIT_FAILURE);
	new->cmd = cmd;
  new->nb_of_cmd = nb;
  new->nb_pipe = ft_strchr(cmd, '|');
  if (ft_strchr(cmd, '<') == 1)
    new->redir_input = 1;
  else 
    new->redir_input = 0;
  if (ft_strchr(cmd, '>') == 1)
    new->redir_output = 1;
  else 
    new->redir_output = 0;
	new->next = comm;
	return (new);
}