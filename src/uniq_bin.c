/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uniq_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:07:04 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/10 16:06:41 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*is_loop(char *cmd)
{
	int	i;

	i = 0;
	if (strchr(cmd, '/'))
	{
		while (cmd[i])
			i++;
		i--;
		while (cmd[i] != '/')
			i--;
		i++;
	}
	while (i > 0)
	{
		cmd++;
		i--;
	}
	return (cmd);
}

void	uniqq_exec(t_uniqq *uniqq, t_comm comm)
{
	char	*l;

	free_str(uniqq->path);
	l = is_loop(comm.cmd[0]);
	uniqq->k = fork();
	if (uniqq->k == 0)
	{
		exec_cmd(uniqq->str, comm);
		signal(SIGINT, SIG_IGN);
		exit(0);
	}
	else
	{
		waitpid(uniqq->k, &uniqq->status, 0);
		uniqq->k = WEXITSTATUS(uniqq->status);
	}
}

int	fill_ret(t_uniqq *uniqq, t_comm comm, t_list **a_list, t_list **b_list)
{
	int	j;

	uniqq->k = red_uniq_comm(comm, uniqq->str, a_list, b_list);
	free_str(uniqq->path);
	j = uniqq->k;
	free(uniqq->str);
	free(uniqq);
	return (j);
}

void	fill_while(t_uniqq *uniqq, t_comm comm)
{
	while (uniqq->path[uniqq->k])
	{
		uniqq->str = ft_strcat_cmd(uniqq->path[uniqq->k], comm.cmd[0]);
		if (access(uniqq->str, F_OK) == 0)
			uniqq->k = 0;
		if (access(uniqq->str, F_OK) == 0)
			break ;
		free(uniqq->str);
		uniqq->k++;
	}
}

int	fill_if(t_uniqq *uniqq, t_comm comm)
{
	while (comm.redir[uniqq->j])
	{
		if (ft_strchr(comm.redir[uniqq->j], '>') > 0)
			open_file2(comm.redir[uniqq->j]);
		if (ft_strchr(comm.redir[uniqq->j], '<') > 0)
		{
			if (open_file(comm.redir[uniqq->j]) == -1)
			{
				g_line.retval = 1;
				free_str(uniqq->path);
				free(uniqq);
				return (-1);
			}
		}
		uniqq->j++;
	}
	if (comm.cmd[0])
		printf("%s: command not found\n", comm.cmd[0]);
	g_line.retval = 127;
	free_str(uniqq->path);
	free(uniqq);
	return (127);
}
