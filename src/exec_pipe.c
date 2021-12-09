/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:47:24 by idhiba            #+#    #+#             */
/*   Updated: 2021/12/09 10:30:21 by glaverdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_exec	exec_setup(t_exec exec, t_pipe *comm_pip)
{
	exec.temp = comm_pip;
	exec.last_cmd = 1;
	exec.error = 0;
	return (exec);
}

void	exec_pipe(t_pipe *comm_pip, t_list **a_list, t_list **b_list)
{
	t_exec	exec;
	int i = 0;

	exec = exec_setup(exec, comm_pip);
	while (exec.temp)
	{
		while (exec.temp->cmd[i])
		{
			printf("cmd = |%s|\n", exec.temp->cmd[i]);
			i++;
		}
		printf("  ---------------------- \n");
		i = 0;
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
