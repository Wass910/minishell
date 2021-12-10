/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_norm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:18:52 by idhiba            #+#    #+#             */
/*   Updated: 2021/12/10 16:07:40 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exec_pipe_norm(t_pipe *temp, int error, t_list **a_list,
	t_list **b_list)
{
	int		last_cmd;
	char	**cmd;
	char	*str;

	str = ft_strdup("ls ef");
	cmd = ft_split_no_free(str, ' ');
	last_cmd = 1;
	if (!temp->next)
		last_cmd = 0;
	if (error != 0)
		pipex_for_one(NULL, cmd);
	pipex(temp, last_cmd, a_list, b_list);
	free_str(cmd);
	free(str);
}

t_pipe	*exec_pipe_norm_err(t_pipe *temp)
{
	while (temp && (temp->error_syn_red == 1
			|| (!temp->path && (verif_the_builtin(temp->cmd) == 1))))
	{
		if (temp->next)
			temp = temp->next;
		else
		{	
			temp = temp->next;
			break ;
		}
	}	
	if (!temp || (!temp->next && (verif_the_builtin(temp->cmd) == 0)))
	{	
		pipex_last(0);
		return (temp);
	}
	return (temp);
}

void	exec_pipe_norm2(t_pipe *temp, int last_cmd,
	t_list **a_list, t_list **b_list)
{
	dup2(temp->read_file, 0);
	pipex_read(temp, last_cmd, a_list, b_list);
}

void	exec_pipe_norm3(t_pipe *temp, int last_cmd,
	t_list **a_list, t_list **b_list)
{
	dup2(temp->read_file, 0);
	pipex_write_read(temp, last_cmd, a_list, b_list);
}

void	exec_pipe_norm4(t_exec exec, t_list **a_list,
	t_list **b_list)
{
	if (exec.temp->write_file >= 0 && exec.temp->read_file == -1)
		pipex_write(exec.temp, exec.last_cmd, a_list, b_list);
	else if (exec.temp->write_file == -1 && exec.temp->read_file == -1)
		exec_pipe_norm(exec.temp, exec.error, a_list, b_list);
	else if (exec.temp->write_file == -1 && exec.temp->read_file >= 0)
		exec_pipe_norm2(exec.temp, exec.last_cmd, a_list, b_list);
	else
		exec_pipe_norm3(exec.temp, exec.last_cmd, a_list, b_list);
}
