#include "../inc/minishell.h"

t_pipe	*fill_comm_pip(t_pipe *comm, char *cmd)
{
	t_fill	*fill;

	fill = fill_setup();
	comm->cmd = malloc(sizeof(char *) * 50);
	comm->redir = malloc(sizeof(char *) * 50);
	while (cmd[fill->i])
	{
		if (cmd[fill->i] == 24)
			fill_if1pip(comm, fill, cmd);
		else if (fill->i == 0 && cmd[fill->i] == 32)
			fill_elsepip1(comm, fill, cmd);
		else if (is_red(cmd[fill->i]))
			fill_elsepip2(comm, fill, cmd);
		else if (cmd[fill->i] == 32 && cmd[fill->i + 1]
			&& cmd[fill->i + 1] == 32)
			fill_elsepip3(comm, fill);
		else if (cmd[fill->i] == 32 && cmd[fill->i + 1]
			&& cmd[fill->i + 1] != 32)
			fill->i++;
		else
			fill_elsepip4(comm, fill, cmd);
	}
	comm->cmd[fill->arg] = NULL;
	comm->redir[fill->red] = NULL;
	return (comm);
}

t_comm	fill_comm(char *cmd)
{
	t_comm	comm;
	t_fill	*fill;

	fill = fill_setup();
	comm.redir = NULL;
	comm = setup_cmd(comm, 1, 0, 0);
	while (cmd[fill->i])
	{
		if (cmd[fill->i] == 24)
			fill_if1(comm, fill, cmd);
		else if (fill->i == 0 && cmd[fill->i] == 32)
			fill_else4(comm, fill);
		else if (is_red(cmd[fill->i]))
			fill_else1(comm, fill, cmd);
		else if (cmd[fill->i] == 32 && cmd[fill->i + 1]
			&& cmd[fill->i + 1] == 32)
			fill_else2(comm, fill);
		else if (cmd[fill->i] == 32 && cmd[fill->i + 1]
			&& cmd[fill->i + 1] != 32)
			fill->i++;
		else
			fill_else3(comm, fill, cmd);
	}
	comm = setup_cmd(comm, 0, fill->arg, fill->red);
	return (comm);
}

int	ft_error_parse_red(char **str)
{
	int	i;
	int	count;
	int	red;

	red = 0;
	count = 0;
	i = 0;
	while (str[i])
	{
		while (is_red(str[i][count]) == 1)
		{
			red++;
			count++;
		}
		if (red > 2 || !str[i][count])
			return (0);
		red = 0;
		count = 0;
		if (str[i][0] == '>' && str[i][1] && str[i][1] == '<')
			return (0);
		i++;
	}
	return (1);
}
