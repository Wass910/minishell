#include "../inc/minishell.h"

void	free_list(t_list **a_list)
{
	t_list	*temp;

	while ((*a_list)->next)
	{
		temp = (*a_list);
		(*a_list) = (*a_list)->next;
		free(temp);
	}
	free(*a_list);
}