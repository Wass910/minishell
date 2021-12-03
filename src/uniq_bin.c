/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uniq_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:07:04 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/03 16:20:35 by glaverdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char    *is_loop(char *cmd)
{
    int i;

    i = 0;
    if (strchr(cmd, '/'))
    {
        while (cmd[i])
            i++;
        i--;
        while(cmd[i] != '/')
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

void    uniqq_exec(t_uniqq *uniqq, t_comm comm)
{
    char *l;
    l = is_loop(comm.cmd[0]);
    if ((!comm.cmd[1] && ((l[0] == 'w' && l[1] == 'c' && !l[2]) || (l[0] == 'c' && l[1] == 'a' && l[2] == 't' && !l[3])))
        || (comm.cmd[1] && l[0] == 'g' && l[1] == 'r' && l[2] == 'e' && l[3] == 'p' && !l[4]))
         g_retval = 200;
    uniqq->k = fork();
    if (uniqq->k == 0)
    {
        exec_cmd(uniqq->str, comm);
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
	uniqq->k = red_uniq_comm(comm, uniqq->str, a_list, b_list);
	free_str(uniqq->path);
	g_retval = uniqq->k;
	return (uniqq->k);
}

int	uniqq_setup(t_uniqq **uniqq, t_comm comm, t_list **a_list, t_list **b_list)
{
	(*uniqq) = malloc(sizeof(t_uniqq) * 1);
	if (!(*uniqq))
		exit(EXIT_FAILURE);
	(*uniqq)->i = 0;
	(*uniqq)->k = 0;
	(*uniqq)->j = 0;
	(*uniqq)->ret = 0;
	if (comm.error_parse_red == 1)
	{
		printf("bash: syntax error near unexpected token\n");
		g_retval = 1;
		return (1);
	}
	(*uniqq)->path = ft_split(getenv2("PATH", a_list), ':');
	if (!comm.redir[0] && comm.cmd[0] && if_builtin(comm.cmd) == 0)
	{
		(*uniqq)->k = builtin(comm.cmd, a_list, b_list);
		g_retval = (*uniqq)->k;
		return (1);
	}
	return (0);
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
				g_retval = 1;
				return (-1);
			}
		}
		uniqq->j++;
	}
	if (comm.cmd[0])
		printf("%s: command not found\n", comm.cmd[0]);
	g_retval = 127;
	return (127);
}
