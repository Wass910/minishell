/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:06:54 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/10 18:01:02 by glaverdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*delete_pair(char *s, t_list **a_list)
{
	char	*final;
	t_del	*del;

	del = NULL;
	del = delete_pair_setup_del(del);
	while (s[del->i])
	{
		del->k = 0;
		delete_pair_norm(s, del);
		while (del->temp && del->temp[del->k])
			delete_pair_norm_while(s, del, a_list);
		del->temp[0] = '\0';
		if (s[del->i] && s[del->i] != 34 && s[del->i] != 39)
			delete_pair_norm4(s, del, a_list);
	}
	del->str[del->j] = '\0';
	final = ft_strdup(del->str);
	free(del->str);
	free(del->temp);
	free(del->temp2);
	free(del);
	free(s);
	return (final);
}

char	*ft_split_command_quote(char **str)
{
	char	*cmd;
	int		i;
	int		j;
	char	*temp;

	j = 0;
	i = 0;
	i = 2;
	if (str[0] && !str[1])
		return (ft_strdup(str[0]));
	if (str[0] && str[1])
		cmd = ft_strcat_redf(str[0], str[1]);
	while (str[i])
	{
		temp = ft_strcat_redf(cmd, str[i]);
		free(cmd);
		cmd = temp;
		i++;
	}
	return (cmd);
}

int	parse_quote_norm(char **s, int i)
{
	if (unclosed_quotes(s[i]))
	{
		printf("Unclosed quotes, check your inport before retrying\n");
		return (1);
	}
	return (0);
}

char	*parse_quote_norm2(char **s, int i, t_list **a_list)
{
	if (check_doll(s[i]))
		s[i] = fill_doll(s[i], a_list);
	return (s[i]);
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
			s[i] = ft_strdup_free(parse_quote_norm2(s, i, a_list));
		else
		{
			if (parse_quote_norm(s, i) == 1)
				return (NULL);
			s[i] = ft_strdup_free(delete_pair(s[i], a_list));
		}
		i++;
	}
	cmd = ft_strdup_free(ft_split_command_quote(s));
	free_str(s);
	return (cmd);
}
