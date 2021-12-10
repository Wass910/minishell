/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:06:46 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/10 14:55:20 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_pipe	*fill_new_norm(t_pipe *new, char *all_cmd, t_list **a_list)
{
	char	**str;
	char	*cmd_new;

	cmd_new = split_glitch(all_cmd);
	str = ft_split(cmd_new, ' ');
	cmd_new = parse_quotes(str, a_list);
	new->read_file = -1;
	new->write_file = -1;
	new = fill_comm_pip(new, cmd_new);
	return (new);
}

t_pipe	*replace_tab_pipe2(t_pipe *comm)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (comm->cmd[j])
	{
		while (comm->cmd[j][k])
		{
			if (comm->cmd[j][k] == 25)
				comm->cmd[j][k] = 32;
			k++;
		}
		k = 0;
		j++;
	}
	return (comm);
}

t_pipe	*replace_tab_pipe(t_pipe *comm)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	comm = replace_tab_pipe2(comm);
	while (comm->redir[j])
	{
		while (comm->redir[j][k])
		{
			if (comm->redir[j][k] == 25)
				comm->redir[j][k] = 32;
			k++;
		}
		k = 0;
		j++;
	}
	return (comm);
}

t_pipe	*parcing_comm_pip(char *all_cmd, t_list **a_list)
{
	t_pipe	*new;

	new = malloc(sizeof(*new));
	if (new == NULL)
		exit(EXIT_FAILURE);
	new = fill_new_norm(new, all_cmd, a_list);
	if (access(new->cmd[0], F_OK) == 0)
		new->path = ft_strdup(new->cmd[0]);
	else
		new->path = path(new->cmd[0], a_list);
	if (ft_error_parse_red(new->redir) == 0)
		new->error_syn_red = 1;
	else
		new->error_syn_red = 0;
	new = replace_tab_pipe(new);
	new->next = NULL;
	return (new);
}

t_pipe	*new_parcing_comm_pip(char *all_cmd,
	t_pipe *pipe, t_list **a_list)
{
	t_pipe	*new;

	new = malloc(sizeof(*new));
	if (new == NULL)
		exit(EXIT_FAILURE);
	new = fill_new_norm(new, all_cmd, a_list);
	if (access(new->cmd[0], F_OK) == 0)
		new->path = ft_strdup(new->cmd[0]);
	else
		new->path = path(new->cmd[0], a_list);
	if (ft_error_parse_red(new->redir) == 0)
		new->error_syn_red = 1;
	else
		new->error_syn_red = 0;
	new = replace_tab_pipe(new);
	new->next = pipe;
	return (new);
}
