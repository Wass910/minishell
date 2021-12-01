#include "../inc/minishell.h"

int	wejdene(t_comm comm, t_uniq *uniq)
{
	while (comm.redir[uniq->i])
	{
		if ((comm.redir[uniq->i] && (ft_strchr(comm.redir[uniq->i], '>') == 1
					|| ft_strchr(comm.redir[uniq->i], '>') == 2)))
		{
			uniq->retnd = open_file2(comm.redir[uniq->i]);
			close(uniq->retnd);
			if (uniq->retnd == -1)
				return (uniq->retnd);
			uniq->to_write = uniq->i;
		}
		if (comm.redir[uniq->i] && ft_strchr(comm.redir[uniq->i], '<') == 1)
		{
			uniq->retnd = open_file(comm.redir[uniq->i]);
			if (uniq->retnd == -1)
				return (uniq->retnd);
			uniq->to_read = uniq->i;
		}
		uniq->i++;
	}
	return (1);
}

void	reflechir(t_uniq *uniq, char *str, t_comm comm)
{
	if (access(str, F_OK) != 0)
	{
		printf("%s: command not found\n", comm.cmd[0]);
		g_retval = 1;
		return ;
	}
	else
	{
		uniq->k = fork();
		if (uniq->k == 0)
		{
			exec_cmd(str, comm);
			exit(0);
		}
		else
		{
			waitpid(uniq->k, &uniq->status, 0);
			uniq->k = WEXITSTATUS(uniq->status);
			g_retval = uniq->k;
		}
	}
}

int	red_uniq_comm(t_comm comm, char *str, t_list **a_list, t_list **b_list)
{
	t_uniq	*uniq;

	uniq = malloc(sizeof(t_uniq) * 1);
	if (!uniq)
		exit(EXIT_FAILURE);
	uniq->to_read = -1;
	uniq->to_write = -1;
	uniq->i = 0;
	if (wejdene(comm, uniq) != 1)
		return (-1);
	if (uniq->to_read >= 0)
		comm.read_file = open_file(comm.redir[uniq->to_read]);
	if (uniq->to_write >= 0)
		comm.write_file = open_file2(comm.redir[uniq->to_write]);
	if (uniq->to_read >= 0 && uniq->to_write >= 0)
		rw_redirection(comm, a_list, b_list, str);
	else if (uniq->to_read < 0 && uniq->to_write >= 0)
		w_redirection(comm, a_list, b_list, str);
	else if (uniq->to_read >= 0 && uniq->to_write < 0)
		r_redirection(comm, a_list, b_list, str);
	else
		reflechir(uniq, str, comm);
	return (1);
}

int	uniq_cmd(t_comm comm, t_list **a_list, t_list **b_list)
{
	char	**path;
	int		k;
	char	*str;
	int		i;
	int		j;
	int		ret;
	int		status;
	char	*tmp;
	int		write_file ;

	i = 0;
	k = 0;
	j = 0;
	ret = 0;
	if (comm.error_parse_red == 1)
	{
		printf("bash: syntax error near unexpected token\n");
		return (1);
	}
	path = ft_split(getenv2("PATH", a_list), ':');
	if (if_builtin(comm.cmd) == 0 && !comm.redir[0])
	{
		k = builtin(comm.cmd, a_list, b_list);
		g_retval = k;
		return (k);
	}
	if (access(comm.cmd[0], F_OK) == 0)
		str = comm.cmd[0];
	else if (path)
	{
		while (path[k])
		{
			str = ft_strcat_cmd(path[k], comm.cmd[0]);
			if (access(str, F_OK) == 0)
				k = 0;
			if (access(str, F_OK) == 0)
				break ;
			free(str);
			k++;
		}
	}
	else
	{
		g_retval = 127;
		return (127);
	}
	if (access(str, F_OK) != 0)
	{
		while (comm.redir[j])
		{
			if (ft_strchr(comm.redir[j], '>') > 0)
				open_file2(comm.redir[j]);
			if (ft_strchr(comm.redir[j], '<') > 0)
			{
				if (open_file(comm.redir[j]) == -1)
				{
					g_retval = 1;
					return (-1);
				}
			}
			j++;
		}
		printf("%s: command not found\n", comm.cmd[0]);
		g_retval = 127;
		return (127);
	}
	if (comm.redir[0])
	{
		k = red_uniq_comm(comm, str, a_list, b_list);
		free_str(path);
		g_retval = k;
		return (k);
	}
	else
	{
		k = fork();
		if (k == 0)
		{
			exec_cmd(str, comm);
			exit(0);
		}
		else
		{
			waitpid(k, &status, 0);
			k = WEXITSTATUS(status);
		}
	}
	free_str(path);
	g_retval = k;
	return (k);
}
