#include "../inc/minishell.h"

void	flstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (!(*lst))
		return ;
	if (del)
	{
		while (*lst)
		{
			del((*lst)->content);
			tmp = (*lst);
			*lst = (*lst)->next;
			free(tmp);
		}
	}
	*lst = NULL;
}
