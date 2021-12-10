/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_uniq.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:06:55 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/10 16:19:48 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	go_pipe(char *all_cmd, t_list **a_list, t_list **b_list)
{
	int	i;

	if (all_cmd[0] == '|' || all_cmd[0] == 32)
	{
		i = 0;
		while (all_cmd[i] == 32)
			i++;
		if (go_pipe_norm(all_cmd, i) == 1)
			return (1);
	}	
	if (only_in_quotes(all_cmd))
		return (0);
	if (ft_strchr(all_cmd, '|') > 0)
	{
		if (verif_pipe(all_cmd) == 0)
			pipe_glitch(all_cmd, a_list, b_list);
		else
			printf("Minishell: syntax error near unexpected token `|'.\n");
		return (1);
	}
	return (0);
}

char	*cmd_parse(char *all_cmd, t_list **a_list)
{
	char	**str;
	char	*cmd_new;

	cmd_new = split_glitch(all_cmd);
	str = ft_split(cmd_new, ' ');
	cmd_new = parse_quotes(str, a_list);
	return (cmd_new);
}

char	*being_back(char *all_cmd)
{
	int	i;

	i = 0;
	while (all_cmd[i])
	{
		if (all_cmd[i] == 23)
			all_cmd[i] = 124;
		i++;
	}
	return (all_cmd);
}

int	parcing(char *all_cmd, t_list **a_list, t_list **b_list)
{
	char	*cmd_new;
	t_comm	comm;

	comm.env = NULL;
	if (go_pipe(all_cmd, a_list, b_list) == 1)
		return (1);
	all_cmd = being_back(all_cmd);
	cmd_new = cmd_parse(all_cmd, a_list);
	if (!cmd_new)
	{
		free(cmd_new);
		return (1);
	}
	comm = fill_comm(cmd_new);
	free(cmd_new);
	if (norme_parcing(comm) == 1)
		return (-1);
	comm = setup_comm(comm);
	norm_for_double_input(comm);
	norme_parcing2(comm, a_list, b_list);
	free_str(comm.cmd);
	free_str(comm.redir);
	return (1);
}
