/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:47:24 by idhiba            #+#    #+#             */
/*   Updated: 2021/12/10 15:21:58 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_exec	exec_setup(t_exec exec, t_pipe *comm_pip)
{
	exec.temp = comm_pip;
	exec.last_cmd = 1;
	return (exec);
}

void	exec_pipe(t_pipe *comm_pip, t_list **a_list, t_list **b_list)
{
	t_exec	exec;

	exec.error = 0;
	exec = exec_setup(exec, comm_pip);
	while (exec.temp)
	{
		if (exec.temp->error_syn_red == 1 || (!exec.temp->path
				&& (find_builtin(exec.temp->cmd) != EXPORT_TYPE)))
		{
			exec.error = 1;
			exec.temp = exec_pipe_norm_err(exec.temp);
		}
		if (exec.temp)
		{
			if (!exec.temp->next)
				exec.last_cmd = 0;
			exec_pipe_norm4(exec, a_list, b_list);
			exec.temp = exec.temp->next;
		}
		exec.error = 0;
	}
}
