#include "minishell.h"

void	flstadd_back(t_list **alst, t_list *new)
{
	t_list	*begin;

	if (!(*alst))
	{
		(*alst) = new;
		return ;
	}
	begin = (*alst);
	while (begin->next)
		begin = begin->next;
	begin->next = new;
}
