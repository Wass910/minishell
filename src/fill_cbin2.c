/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cbin2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:05:47 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/02 14:05:48 by glaverdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	fill_else4(t_comm comm, t_fill *fill)
{
	comm.cmd[fill->arg] = malloc(sizeof(char) * 2);
	comm.cmd[fill->arg][fill->argindex] = '\0';
	fill->arg++;
	fill->i++;
}

t_comm	setup_cmd(t_comm comm, int i, int arg, int red)
{
	if (i == 1)
	{
		comm.cmd = malloc(sizeof(char *) * 50);
		comm.redir = malloc(sizeof(char *) * 50);
	}
	else
	{
		comm.cmd[arg] = NULL;
		comm.redir[red] = NULL;
	}
	return (comm);
}

t_comm	setup_cmd2(t_comm comm, int i, int arg, int red)
{
	if (i == 1)
	{
		comm.cmd = malloc(sizeof(char *) * 50);
		comm.redir = malloc(sizeof(char *) * 50);
	}
	else
	{
		comm.cmd[arg] = NULL;
		comm.redir[red] = NULL;
	}
	return (comm);
}
