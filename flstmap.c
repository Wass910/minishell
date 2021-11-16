#include "minishell.h"

t_list	*flstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*newstart;
	t_list	*newnext;

	if (!f || !lst)
		return (NULL);
	new = flstnew(f(lst->content));
	if (!new)
		return (NULL);
	lst = lst->next;
	newstart = new;
	while (lst)
	{
		newnext = flstnew(f(lst->content));
		if (!newnext)
		{
			flstclear(&newstart, del);
			return (0);
		}
		new->next = newnext;
		new = newnext;
		lst = lst->next;
	}
	return (newstart);
}
