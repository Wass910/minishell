/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_norm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:54:03 by idhiba            #+#    #+#             */
/*   Updated: 2021/12/07 13:57:29 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	error_synthax_red(t_pipe *comm_pip)
{
	while (comm_pip)
	{
		if (ft_error_parse_red(comm_pip->redir) == 0)
		{	
			printf("Minishell: syntax error near unexpected token\n");
			return (1);
		}
		comm_pip = comm_pip->next;
	}
	return (0);
}

void	not_valid_comm(t_pipe *comm_pip)
{
	while (comm_pip)
	{
		if (comm_pip->path == NULL && comm_pip->cmd[0])
		{
			if (verif_the_builtin(comm_pip->cmd) == 1)
			{
				printf("%s: command not found\n", comm_pip->cmd[0]);
			}
		}
		comm_pip = comm_pip->next;
	}
}

int	end_comm(t_pipe *parse_pip)
{
	while (parse_pip->next)
		parse_pip = parse_pip->next;
	if (!parse_pip->path)
		return (1);
	return (0);
}

void	all_good_red(t_pipe *comm_pip)
{
	t_pipe	*temp;
	t_pipe	*temp2;
	int		i;

	i = 0;
	temp2 = comm_pip;
	temp = comm_pip;
	while (temp)
	{
		if (temp->error_syn_red == 1)
			i++;
		temp = temp->next;
	}
	if (i == 0)
	{
		while (temp2)
		{
			temp2 = open_file_redir(temp2);
			temp2 = temp2->next;
		}
	}
}
