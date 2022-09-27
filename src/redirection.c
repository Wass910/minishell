/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:06:59 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/09 14:24:21 by glaverdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	rw_redirection(t_comm comm, t_list **a_list, t_list **b_list, char *str)
{
	int	k;
	int	status;

	k = fork();
	if (k == 0)
	{
		dup2(comm.write_file, STDOUT);
		dup2(comm.read_file, STDIN);
		if (verif_the_builtin(comm.cmd))
			exec_cmd(str, comm);
		else
			builtin(comm.cmd, a_list, b_list);
		exit(0);
	}
	else
	{
		waitpid(k, &status, 0);
		k = WEXITSTATUS(status);
		g_line.retval = k;
	}
	return (k);
}

int	r_redirection(t_comm comm, t_list **a_list, t_list **b_list, char *str)
{
	int	k;
	int	status;

	k = fork();
	if (k == 0)
	{
		if (verif_the_builtin(comm.cmd))
		{
			dup2(comm.read_file, STDIN);
			exec_cmd(str, comm);
		}
		else
		{
			dup2(comm.read_file, STDIN);
			builtin(comm.cmd, a_list, b_list);
		}
		exit(0);
	}
	else
	{
		waitpid(k, &status, 0);
		k = WEXITSTATUS(status);
		g_line.retval = k;
	}
	return (k);
}

int	w_redirection(t_comm comm, t_list **a_list, t_list **b_list, char *str)
{
	int	k;
	int	status;

	k = fork();
	if (k == 0)
	{
		if (verif_the_builtin(comm.cmd))
		{
			dup2(comm.write_file, STDOUT);
			exec_cmd(str, comm);
		}
		else
		{
			dup2(comm.write_file, STDOUT);
			builtin(comm.cmd, a_list, b_list);
		}
		exit(0);
	}
	else
	{
		waitpid(k, &status, 0);
		k = WEXITSTATUS(status);
		g_line.retval = k;
	}
	return (k);
}
