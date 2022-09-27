/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 11:35:57 by idhiba            #+#    #+#             */
/*   Updated: 2021/12/10 10:30:32 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_lred	*dred_setup(t_lred *dred, int i)
{
	if (i == 1)
	{	
		dred->i = 0;
		dred->count = 0;
		dred->count_temp = 2;
		dred->temp_index = 0;
	}
	else
	{	
		dred->count++;
		dred->count_temp = 2 ;
		dred->temp_index = 0;
	}
	return (dred);
}

t_comm	comm_setup(t_comm comm)
{
	comm.redir_double_input = 0;
	comm.redir_temp = malloc(sizeof(char *) * 50);
	return (comm);
}

char	*fill_s(char *s, int j, t_list *temp)
{
	if (j == 1)
		s = &temp->content[11];
	else
		s = temp->content;
	return (s);
}

int	uniqq_setup(t_uniqq **uniqq, t_comm comm, t_list **a_list, t_list **b_list)
{
	(*uniqq) = malloc(sizeof(t_uniqq) * 1);
	if (!(*uniqq))
		exit(EXIT_FAILURE);
	(*uniqq)->i = 0;
	(*uniqq)->k = 0;
	(*uniqq)->j = 0;
	(*uniqq)->ret = 0;
	if (!comm.redir[0] && comm.cmd[0] && if_builtin(comm.cmd) == 0)
	{
		free(*uniqq);
		g_line.retval = builtin(comm.cmd, a_list, b_list);
		return (1);
	}
	(*uniqq)->path = ft_split(getenv2("PATH", a_list), ':');
	return (0);
}

t_comm	setup_comm(t_comm comm)
{
	comm = replace_space(comm);
	comm.read_file = -3;
	comm.write_file = -3;
	comm = ft_double_left_red(comm);
	return (comm);
}
