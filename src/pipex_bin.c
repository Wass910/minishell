/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:06:56 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/09 11:30:14 by glaverdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	dup_write(t_pipe *comm_pip, t_list **a_list,
	t_list **b_list, int *pipefd)
{
	close(pipefd[0]);
	dup2(comm_pip->write_file, 1);
	if (verif_the_builtin(comm_pip->cmd) == 0)
	{
		if (find_builtin(comm_pip->cmd) != UNSET_TYPE)
			builtin(comm_pip->cmd, a_list, b_list);
	}
	else
		execve(comm_pip->path, comm_pip->cmd, NULL);
	exit (0);
}

void	dup_read_norme(int i, int *pipefd)
{
	close(pipefd[0]);
	if (i == 1)
		dup2(pipefd[1], 1);
}

void	dup_read(t_pipe *comm_pip, t_list **a_list,
	t_list **b_list)
{
	if (verif_the_builtin(comm_pip->cmd) == 0)
	{
		if (find_builtin(comm_pip->cmd) != UNSET_TYPE)
			builtin(comm_pip->cmd, a_list, b_list);
	}
	else
		execve(comm_pip->path, comm_pip->cmd, NULL);
	exit (0);
}

t_comm	replace_space2(t_comm comm)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (comm.cmd[j])
	{
		while (comm.cmd[j][k])
		{
			if (comm.cmd[j][k] == 25)
				comm.cmd[j][k] = 32;
			k++;
		}
		k = 0;
		j++;
	}
	return (comm);
}

t_comm	replace_space(t_comm comm)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	comm = replace_space2(comm);
	while (comm.redir[j])
	{
		while (comm.redir[j][k])
		{
			if (comm.redir[j][k] == 25)
				comm.redir[j][k] = 32;
			k++;
		}
		k = 0;
		j++;
	}
	return (comm);
}
