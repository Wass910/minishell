/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:06:49 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/07 14:27:50 by idhiba           ###   ########.fr       */
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
			|| !temp->path))
	{
		temp = temp->next;
	}	
	if (!temp)
		pipex_last(temp, 0);
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

void	exec_pipe(t_pipe *comm_pip, t_list **a_list, t_list **b_list)
{
	int		last_cmd;
	int		error;
	t_pipe	*temp;

	temp = comm_pip;
	last_cmd = 1;
	error = 0;
	while (temp)
	{
		if (temp->error_syn_red == 1 || !temp->path)
		{
			error = 1;
			temp = exec_pipe_norm_err(temp);
		}
		if (temp)
		{
			if (!temp->next)
				last_cmd = 0;
			if (temp->write_file >= 0 && temp->read_file == -1)
				pipex_write(temp, last_cmd, a_list, b_list);
			else if (temp->write_file == -1 && temp->read_file == -1)
				exec_pipe_norm(temp, error, a_list, b_list);
			else if (temp->write_file == -1 && temp->read_file >= 0)
				exec_pipe_norm2(temp, last_cmd, a_list, b_list);
			else
				exec_pipe_norm3(temp, last_cmd, a_list, b_list);
			temp = temp->next;
		}
		error = 0;
	}
}

int	pipe_glitch(char *line, t_list **a_list, t_list **b_list)
{
	char	**cmd;
	char	**red_double;
	int		j;
	int		i;
	t_pipe	*comm_pip;
	int		nb_cmds;
	int		last_cmd;

	j = 0;
	last_cmd = 1;
	i = 0;
	cmd = ft_split_no_free(line, '|');
	i = 0;
	while (cmd[i])
	{
		while (cmd[i][j])
		{
			if (cmd[i][j] == 23)
				cmd[i][j] = '|';
			j++;
		}
		i++;
		j = 0;
	}
	i = 0;
	j = 0;
	red_double = double_in(line, a_list);
	while (red_double && red_double[j])
		j++;
	if (red_double && red_double[0])
		ft_redir_temp(red_double, j);
	if (red_double)
		free_str(red_double);
	while (cmd[i])
		i++;
	nb_cmds = i;
	i--;
	comm_pip = parcing_comm_pip(cmd[i], a_list);
	while (i-- > 0)
		comm_pip = new_parcing_comm_pip(cmd[i], comm_pip, a_list);
	all_good_red(comm_pip);
	if (error_synthax_red(comm_pip) == 0)
	{
		not_valid_comm(comm_pip);
		exec_pipe(comm_pip, a_list, b_list);
	}
	free_pipe(comm_pip);
	free_str(cmd);
	return (0);
}

