#include "../inc/minishell.h"

t_del	*setup_del(void)
{
	t_del	*del;

	del = malloc(sizeof(t_del) * 1);
	if (!del)
		exit(EXIT_FAILURE);
	del->j = 0;
	del->i = 0;
	del->k = 0;
	del->c = 0;
	del->str = malloc(sizeof(char) * 1000);
	if (!del->str)
		exit(EXIT_FAILURE);
	del->temp = malloc(sizeof(char) * 1000);
	if (!del->temp)
		exit(EXIT_FAILURE);
	return (del);
}

void	del_if1(t_del *del, char *s)
{
	del->type = s[del->i];
	del->i++;
	while (s[del->i] && s[del->i] != del->type)
	{
		del->temp[del->k] = s[del->i];
		del->k++;
		del->i++;
	}
	del->temp[del->k] = '\0';
	del->i++;
	del->k = 0;
}

void	del_if2(t_del *del, char *s, t_list **a_list)
{
	del->k++;
	del->temp2[0] = after_env(&del->temp[del->k]);
	del->temp2[1] = getenv2(del->temp2[0], a_list);
	free(del->temp2[0]);
	if (!del->temp2[1])
	{
		del->str[del->j] = s[del->i];
		del->i++;
		del->j++;
	}
	while (del->temp2[1] && del->temp2[1][del->c])
	{
		del->str[del->j] = del->temp2[1][del->c];
		del->c++;
		del->j++;
	}
	del->c = 0;
	if (del->temp2[1])
	{
		while (del->temp[del->k] && char_alphanum(del->temp[del->k]))
			del->k++;
	}
	free(del->temp2[1]);
}

void	del_if3(t_del *del, char *s, t_list **a_list)
{
	del->temp2[0] = after_env(&s[del->i]);
	del->temp2[1] = getenv2(del->temp2[0], a_list);
	free(del->temp2[0]);
	while (del->temp2[1][del->c])
	{
		del->str[del->j] = del->temp2[1][del->c];
		del->c++;
		del->j++;
	}
	del->c = 0;
	if (del->temp2[1])
	{
		del->i++;
		while (s[del->i] && char_alphanum(s[del->i]))
			del->i++;
	}
	free(del->temp2[1]);
}

void	del_else(t_del *del)
{
	del->str[del->j] = del->temp[del->k];
	del->k++;
	del->j++;
}
