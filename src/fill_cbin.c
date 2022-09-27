/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cbin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:05:45 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/03 15:46:12 by glaverdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_fill	*fill_setup(void)
{
	t_fill	*fill;

	fill = malloc(sizeof(t_fill) * 1);
	if (!fill)
		exit(EXIT_FAILURE);
	fill->argindex = 0;
	fill->arg = 0;
	fill->redindex = 0;
	fill->red = 0;
	fill->i = 0;
	return (fill);
}

void	fill_if1(t_comm comm, t_fill *fill, char *cmd)
{
	comm.cmd[fill->arg] = malloc(sizeof(char) * 400);
	fill->i++;
	while (cmd[fill->i] && cmd[fill->i] != 32)
	{
		comm.cmd[fill->arg][fill->argindex] = cmd[fill->i];
		fill->i++;
		fill->argindex++;
	}
	comm.cmd[fill->arg][fill->argindex] = '\0';
	fill->arg++;
	fill->argindex = 0;
}

void	fill_else1(t_comm comm, t_fill *fill, char *cmd)
{
	comm.redir[fill->red] = malloc(sizeof(char) * 400);
	while (cmd[fill->i] && cmd[fill->i] != 32)
	{
		comm.redir[fill->red][fill->redindex] = cmd[fill->i];
		fill->i++;
		fill->redindex++;
	}
	comm.redir[fill->red][fill->redindex] = '\0';
	fill->red++;
	fill->redindex = 0;
}

void	fill_else2(t_comm comm, t_fill *fill)
{
	comm.cmd[fill->arg] = malloc(sizeof(char) * 5);
	comm.cmd[fill->arg][fill->argindex] = '\0';
	fill->argindex = 0;
	fill->arg++;
	fill->i += 2;
}

void	fill_else3(t_comm comm, t_fill *fill, char *cmd)
{
	comm.cmd[fill->arg] = malloc(sizeof(char) * 400);
	if (cmd[fill->i] != 32)
	{
		while (cmd[fill->i] && cmd[fill->i] != 32)
		{
			comm.cmd[fill->arg][fill->argindex] = cmd[fill->i];
			fill->i++;
			fill->argindex++;
		}
	}
	else
		fill->i++;
	comm.cmd[fill->arg][fill->argindex] = '\0';
	fill->argindex = 0;
	fill->arg++;
}
