/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:06:49 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/09 17:08:42 by glaverdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**cmd_pipe_glitch(int i, int j, char *line)
{
	char	**cmd;

	cmd = ft_split_no_free(line, '|');
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
	return (cmd);
}

void	pipe_glitch_norme(t_pipe *comm_pip, t_list **a_list, t_list **b_list)
{
	if (error_synthax_red(comm_pip) == 0)
	{
		not_valid_comm(comm_pip);
		exec_pipe(comm_pip, a_list, b_list);
	}
}

t_pipe	*comm_pipe_setup(char **cmd, int i, t_list **a_list, t_pipe *comm_pip)
{
	comm_pip = parcing_comm_pip(cmd[i], a_list);
	while (i-- > 0)
		comm_pip = new_parcing_comm_pip(cmd[i], comm_pip, a_list);
	return (comm_pip);
}

t_norm	norm_setup(t_norm norm, char *line, t_list **a_list)
{
	norm.last_cmd = 1;
	norm.cmd = cmd_pipe_glitch(0, 0, line);
	norm.j = 0;
	norm.red_double = double_in(line, a_list);
	return (norm);
}

int	pipe_glitch(char *line, t_list **a_list, t_list **b_list)
{
	t_pipe	*comm_pip;
	t_norm	norm;

	norm.i = 0;
	norm = norm_setup(norm, line, a_list);
	while (norm.red_double && norm.red_double[norm.j])
		norm.j++;
	if (norm.red_double && norm.red_double[0])
		ft_redir_temp(norm.red_double, norm.j);
	if (norm.red_double)
		free_str(norm.red_double);
	while (norm.cmd[norm.i])
		norm.i++;
	norm.nb_cmds = norm.i;
	norm.i--;
	comm_pip = NULL;
	comm_pip = comm_pipe_setup(norm.cmd, norm.i, a_list, comm_pip);
	all_good_red(comm_pip);
	pipe_glitch_norme(comm_pip, a_list, b_list);
	free_pipe(comm_pip);
	free_str(norm.cmd);
	return (0);
}
