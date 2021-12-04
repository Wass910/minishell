/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:06:49 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/03 16:54:47 by glaverdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_retval = 0;

void	pipex_for_one(char *path, char **cmd)
{
	int		pipefd[2];
	pid_t	pid1;

	if (pipe(pipefd) == -1)
		exit(EXIT_FAILURE);
	pid1 = fork();
	if (pid1 == -1)
		exit(EXIT_FAILURE);
	if (pid1)
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		waitpid(pid1, NULL, 0);
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		execve(path, cmd, NULL);
		exit (0);
	}
}

void	pipex_last(t_pipe *comm_pip, int i)
{
	int		pipefd[2];
	pid_t	pid1;
	int		status;

	if (pipe(pipefd) == -1)
		exit(EXIT_FAILURE);
	pid1 = fork();
	if (pid1 == -1)
		exit(EXIT_FAILURE);
	if (pid1)
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		if (i == 0)
			dup2(1, 0);
		waitpid(pid1, &status, 0);
	}
	else
		dup2(pipefd[1], 1);
}

void	exec_pipe(t_pipe *comm_pip, t_list **a_list, t_list **b_list)
{
	int		last_cmd;
	int		error;
	char	**cmd;
	char	str[10] = "ls ef";

	last_cmd = 1;
	error = 0;
	cmd = ft_split(str, ' ');
	while (comm_pip)
	{
		if (comm_pip->error_syn_red == 1 || !comm_pip->path)
		{
			error = 1;
			while (comm_pip && (comm_pip->error_syn_red == 1
					|| !comm_pip->path))
			{
				comm_pip = comm_pip->next;
			}	
			if (!comm_pip)
				pipex_last(comm_pip, 0);
		}
		if (comm_pip)
		{
			if (!comm_pip->next)
				last_cmd = 0;
			if (comm_pip->write_file >= 0 && comm_pip->read_file == -1)
				pipex_write(comm_pip, last_cmd, a_list, b_list);
			else if (comm_pip->write_file == -1 && comm_pip->read_file == -1)
			{
				if (error != 0)
					pipex_for_one(NULL, cmd);
				pipex(comm_pip, last_cmd, a_list, b_list);
			}
			else if (comm_pip->write_file == -1 && comm_pip->read_file >= 0)
			{	
				dup2(comm_pip->read_file, 0);
				pipex_read(comm_pip, last_cmd, a_list, b_list);
			}
			else
			{	
				dup2(comm_pip->read_file, 0);
				pipex_write_read(comm_pip, last_cmd, a_list, b_list);
			}
			comm_pip = comm_pip->next;
		}
		error = 0;
	}
}

int	error_synthax_red(t_pipe *comm_pip)
{
	while (comm_pip)
	{
		if (ft_error_parse_red(comm_pip->redir) == 0)
		{	
			printf("Minishell: syntax error near unexpected token\n");
			return 1;
		}
		comm_pip = comm_pip->next;
	}
	return 0;
}

void	not_valid_comm(t_pipe *comm_pip)
{
	while (comm_pip)
	{
		if (comm_pip->path == NULL && comm_pip->cmd[0])
			printf("%s: command not found\n", comm_pip->cmd[0]);
		comm_pip = comm_pip->next;
	}
}

int	end_comm(t_pipe *parse_pip)
{
	while (parse_pip->next)
		parse_pip = parse_pip->next;
	if (!parse_pip->path)
		return (1);
	return (0);	
}

void	all_good_red(t_pipe *comm_pip)
{
	t_pipe	*temp;
	t_pipe	*temp2;
	int		i;

	i = 0;
	temp2 = comm_pip;
	temp = comm_pip;
	while (temp)
	{
		if (temp->error_syn_red == 1)
			i++;
		temp = temp->next;
	}
	if  (i == 0)
	{
		while (comm_pip)
		{
			comm_pip = open_file_redir(comm_pip);
			comm_pip = comm_pip->next;
		}

	}
}

int	pipe_glitch(char *line, t_list **a_list, t_list **b_list)
{
	char	**cmd;
	char	**red_double;
	int		j;
	int		i;
	t_pipe	*comm_pip;
	int		retclone;
	int		nb_cmds;
	int		last_cmd;

	j = 0;
	last_cmd = 1;
	i = 0;
	retclone = 0;
	cmd = ft_split(line, '|');
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
	{
		printf("to input = %s\n", red_double[j]);
			j++;
	}
	if (red_double && red_double[0])
		ft_redir_temp(red_double, j);
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
	return (0);
}

int	unclosed_quotes2(char *s)
{
	int	i;
	int	j;
	int	type;

	i = 0;
	j = 0;
	type = 0;
	while (s[i])
	{
		if (s[i] == 34 || s[i] == 39)
		{
			type = s[i];
			i++;
			while (s[i] && s[i] != type)
				i++;
			if (!s[i])
			{
				printf("Unclosed quotes, check your inport before retrying\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

void  inthandler(int sig)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("\0", 0);
	rl_redisplay();
}

int	main(int argc, char **argv, char **envp)
{
	t_list				*a_list;
	t_list				*b_list;
	char				*line;
	int					i;

	argv = NULL;
	if (argc != 1)
	{
		printf("Too much arguments, usage : './minishell'.\n");
		exit(EXIT_FAILURE);
	}
	make_list(&a_list, envp);
	make_list(&b_list, envp);
	signal(SIGQUIT, inthandler);
	signal(SIGINT, inthandler);
	while (1)
	{
		if (g_retval != 200)
		{
			rl_replace_line("", 0);
			line = readline("$> ");
		}
		if(g_retval == 200)
		{
			rl_replace_line("", 0);
			line = readline("");
			g_retval = 1;
		}
		if (line == NULL)
		{
			printf("exit\n");
			return (0);
		}
		if (line[0])
		{
			add_history(line);
			if (!only_space(line) && !unclosed_quotes2(line))
				i = parcing(line, &a_list, &b_list);
		}
		if (line)
			free(line);
	}
	return (0);
}
