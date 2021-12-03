/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_uniq.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:06:55 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/03 16:58:50 by glaverdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	verif_pipe(char *str)
{
	int	i;
	int	pipe;

	pipe = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '|')
		{
			pipe = i + 1;
			if (str[i + 1] == '|')
				return (1);
			while (str[pipe] == 32)
				pipe++;
			if (str[pipe] == '|' || !str[pipe])
				return (1);
		}
		i++;
	}
	return (0);
}

t_comm	setup_comm(t_comm comm)
{
	comm = replace_space(comm);
	comm.read_file = -3;
	comm.write_file = -3;
	comm = ft_double_left_red(comm);
	return (comm);
}

int    only_in_quotes(char *s)
{
    int i;
    int type;
    
    i = 0;
    while (s[i])
    {
        if (s[i] == 34 || s[i] == 39)
        {
            type = s[i];
            i++;
            while (s[i] != type && s[i])
            {
                if (s[i] == 124)
                    s[i] = 23;
                i++;
            }
        }
        i++;
    }
    return (0);
}

int    go_pipe(char *all_cmd, t_list **a_list, t_list **b_list)
{
    if (only_in_quotes(all_cmd))
        return (0);
    if (ft_strchr(all_cmd, '|') > 0)
    {
        if (verif_pipe(all_cmd) == 0)
            pipe_glitch(all_cmd, a_list, b_list);
        else
            printf("Minishell: syntax error near unexpected token `|'.\n");
        g_retval = 1;
        return (1);
    }
    return (0);
}

char	*cmd_parse(char *all_cmd, t_list **a_list)
{
	char	**str;
	char	*cmd_new;

	cmd_new = malloc(sizeof(char) * 100);
	if (!cmd_new)
		exit(EXIT_FAILURE);
	cmd_new = split_glitch(all_cmd);
	str = ft_split(cmd_new, ' ');
	cmd_new = parse_quotes(str, a_list);
	return (cmd_new);
}

char    *being_back(char *all_cmd)
{
    int i;

    i = 0;
    while (all_cmd[i])
    {
        if (all_cmd[i] == 23)
            all_cmd[i] = 124;
        i++;
    }
    return (all_cmd);
}

int	parcing(char *all_cmd, t_list **a_list, t_list **b_list)
{
	char	*cmd_new;
	t_comm	comm;

	comm.env = NULL;
	if (go_pipe(all_cmd, a_list, b_list) == 1)
		return (1);
	all_cmd = being_back(all_cmd);
	cmd_new = cmd_parse(all_cmd, a_list);
	if (!cmd_new)
		return (1);
	comm = fill_comm(cmd_new);
	if (ft_error_parse_red(comm.redir) == 0)
	{
		printf("Minishell: syntax error near unexpected token\n");
		g_retval = -1;
		return (-1);
	}
	comm = setup_comm(comm);
	if (comm.redir_temp[0])
		ft_redir_temp(comm.redir_temp, comm.redir_double_input);
	uniq_cmd(comm, a_list, b_list);
	return (1);
}
