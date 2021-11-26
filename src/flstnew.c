#include "../inc/minishell.h"

t_list *flstnew_comm(t_comm comm)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->pipecomm = comm;
	new->next = NULL;
	return (new);
}

t_list	*flstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
