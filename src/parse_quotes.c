#include "../inc/minishell.h"

char	*delete_pair(char *s, t_list **a_list)
{
	t_del	*del;

	del = setup_del();
	while (s[del->i])
	{
		del->k = 0;
		if (s[del->i] == 34 || s[del->i] == 39)
			del_if1(del, s);
		else
			del->temp[0] = '\0';
		while (del->temp && del->temp[del->k])
		{
			if (del->temp[del->k] == '$' && del->temp[del->k + 1]
				&& char_alphanum(del->temp[del->k + 1]) && del->type == 34)
				del_if2(del, s, a_list);
			else if (del->temp[del->k])
				del_else(del);
		}
		del->temp[0] = '\0';
		if (s[del->i] && s[del->i] != 34 && s[del->i] != 39)
			del_if3(del, s, a_list);
	}
	del_free(del, s);
	del->str[del->j] = '\0';
	return (del->str);
}

char	*ft_split_command_quote(char **str)
{
	char	*cmd;
	int		i;
	int		j;

	j = 0;
	i = 0;
	i = 2;
	if (str[0] && str[1])
		cmd = ft_strcat_redf(str[0], str[1]);
	if (str[0] && !str[1])
		return (str[0]);
	while (str[i])
	{
		cmd = ft_strcat_redf(cmd, str[i]);
		i++;
	}
	return (cmd);
}

void	quote_if(int i, char **s, t_list **a_list)
{
	if (check_doll(s[i]))
		s[i] = fill_doll(s[i], a_list);
	if (s[i][0] == '\0')
		s[i] = NULL;
}

char	*parse_quotes(char **s, t_list **a_list)
{
	int		i;
	int		j;
	char	*cmd;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (no_quotes(s[i]))
			quote_if(i, s, a_list);
		else
		{
			if (unclosed_quotes(s[i]))
			{
				printf("Unclosed quotes, check your inport before retrying\n");
				return (NULL);
			}
			s[i] = delete_pair(s[i], a_list);
		}
		i++;
	}
	cmd = ft_split_command_quote(s);
	return (cmd);
}
