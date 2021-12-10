/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_uniq_norm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:43:49 by idhiba            #+#    #+#             */
/*   Updated: 2021/12/10 15:54:10 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	go_pipe_norm(char *all_cmd, int i)
{
	if (all_cmd[i] == '|')
	{
		printf("Minishell: syntax error near unexpected token `|'.\n");
		g_line.retval = 1;
		return (1);
	}
	return (0);
}

int	norme_parcing(t_comm comm)
{
	if (ft_error_parse_red(comm.redir) == 0)
	{
		printf("Minishell: syntax error near unexpected token\n");
		free_str(comm.redir);
		free_str(comm.cmd);
		g_line.retval = 1;
		return (1);
	}
	return (0);
}

void	open_with_no_comm(t_comm comm)
{
	int	i;

	i = 0;
	while (comm.redir[i])
	{
		if (comm.redir[i][0] == '>' && comm.redir[i][1] != '<')
			open_file2(comm.redir[i]);
		if (comm.redir[i][0] == '<' && (comm.redir[i][1] != '<'
			&& comm.redir[i][1] != '>'))
			open_file(comm.redir[i]);
		i++;
	}
}

void	norme_parcing2(t_comm comm, t_list **a_list, t_list **b_list)
{
	if (comm.cmd[0] != NULL)
		uniq_cmd(comm, a_list, b_list);
	else if (comm.redir)
		open_with_no_comm(comm);
}
