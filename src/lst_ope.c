#include "../inc/minishell.h"

t_pipe	*fill_comm_pip(t_pipe *comm ,char *cmd)
{
	int i = 0;
	int red = 0;
	int redindex = 0;
	int arg = 0;
	int argindex = 0;
	comm->cmd = malloc(sizeof(char *) * 50);
	comm->redir = malloc(sizeof(char *) * 50);
	while (cmd[i])
	{
		if(cmd[i] == 24)
		{
			comm->cmd[arg] = malloc(sizeof(char) * 400);
			i++;
			while (cmd[i] && cmd[i] != 32)
			{
				comm->cmd[arg][argindex] = cmd[i];
				i++;
				argindex++;
			}
			comm->cmd[arg][argindex] = '\0';
			arg++;
			argindex = 0;
		}
		else if (i == 0 && cmd[i] == 32)
		{
			comm->cmd[arg] = malloc(sizeof(char) * 2);
			comm->cmd[arg][argindex] = '\0';
			arg++;
			i++;
		}
		else if(is_red(cmd[i]))
		{
			if (cmd[i] == '<' && cmd[i + 1] && cmd[i + 1] == '<' && cmd[i + 2] 
				&& (cmd[i + 2] != '<' && cmd[i + 2] != '>'))
			{
				while (cmd[i] && cmd[i] != 32 && cmd[i] != 24)
					i++;
			}
			else
			{
				comm->redir[red] = malloc(sizeof(char) * 400);
				while (cmd[i] && cmd[i] != 32)
				{
					comm->redir[red][redindex] = cmd[i];
					i++;
					redindex++;
				}
				comm->redir[red][redindex] = '\0';

				red++;
				redindex = 0;
			}
		}
		else if (cmd[i] == 32 && cmd[i + 1] && cmd[i + 1] == 32)
		{
			comm->cmd[arg] = malloc(sizeof(char) * 5);
			comm->cmd[arg][argindex] = '\0';
			argindex = 0;
			arg++;
			i += 2;
		}
		else if (cmd[i] == 32 && cmd[i + 1] && cmd[i + 1] != 32)
			i++;
		else
		{
			comm->cmd[arg] = malloc(sizeof(char) * 400);
			while (cmd[i] && cmd[i] != 32)
			{
				comm->cmd[arg][argindex] = cmd[i];
				i++;
				argindex++;
			}
			comm->cmd[arg][argindex] = '\0';
			argindex = 0;
			arg++;
		}
	}
	comm->cmd[arg] = NULL;
	comm->redir[red] = NULL;
	return (comm);
}

t_comm	fill_comm(t_comm comm ,char *cmd)
{
	int i = 0;
	int red = 0;
	int redindex = 0;
	int arg = 0;
	int argindex = 0;
	comm.cmd = malloc(sizeof(char *) * 50);
	comm.redir = malloc(sizeof(char *) * 50);
	while (cmd[i])
	{
		if(cmd[i] == 24)
		{
			comm.cmd[arg] = malloc(sizeof(char) * 400);
			i++;
			while (cmd[i] && cmd[i] != 32)
			{
				comm.cmd[arg][argindex] = cmd[i];
				i++;
				argindex++;
			}
			comm.cmd[arg][argindex] = '\0';
			arg++;
			argindex = 0;
		}
		else if (i == 0 && cmd[i] == 32)
		{
			comm.cmd[arg] = malloc(sizeof(char) * 2);
			comm.cmd[arg][argindex] = '\0';
			arg++;
			i++;
		}
		else if(is_red(cmd[i]))
		{
			comm.redir[red] = malloc(sizeof(char) * 400);
			while (cmd[i] && cmd[i] != 32)
			{
				comm.redir[red][redindex] = cmd[i];
				i++;
				redindex++;
			}
			comm.redir[red][redindex] = '\0';
			red++;
			redindex = 0;
		}
		else if (cmd[i] == 32 && cmd[i + 1] && cmd[i + 1] == 32)
		{
			comm.cmd[arg] = malloc(sizeof(char) * 5);
			comm.cmd[arg][argindex] = '\0';
			argindex = 0;
			arg++;
			i += 2;
		}
		else if (cmd[i] == 32 && cmd[i + 1] && cmd[i + 1] != 32)
			i++;
		else
		{
			comm.cmd[arg] = malloc(sizeof(char) * 400);
			while (cmd[i] && cmd[i] != 32)
			{
				comm.cmd[arg][argindex] = cmd[i];
				i++;
				argindex++;
			}
			comm.cmd[arg][argindex] = '\0';
			argindex = 0;
			arg++;
		}
	}
	comm.cmd[arg] = NULL;
	comm.redir[red] = NULL;
	return (comm);
}

int		ft_error_parse_red(char **str)
{
	int i;
	int count;
	int red = 0;

	count = 0;
	i = 0;
	while(str[i])
	{
		while (is_red(str[i][count]) == 1)
		{
			red++;
			count++;
		}
		if(red > 2 || !str[i][count])
			return 0;
		red = 0;
		count = 0;
		if (str[i][0] == '>' && str[i][1] && str[i][1] =='<')
			return 0;
		i++;
	}
	return 1;
}