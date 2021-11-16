#include "minishell.h"

void	flstadd_front(t_list **alst, t_list *new)
{
	new->next = (*alst);
	*alst = new;
}
