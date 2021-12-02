#include "../inc/minishell.h"

void	del_else2(t_del *del, char *s)
{
	del->str[del->j] = s[del->i];
	del->j++;
	del->i++;
}

void	del_if4(t_del *del, char *s, t_list **a_list)
{
	if (s[del->i] == '$' && s[del->i + 1] && char_alphanum(s[del->i + 1]))
		del_if3(del, s, a_list);
	else
		del_else2(del, s);
}

void	del_free(t_del *del, char *s)
{
	free(del->temp);
	free(s);
}
