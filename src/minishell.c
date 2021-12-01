#include "../inc/minishell.h"

int g_retval = 0;

void	print_pipe(t_pipe *parse_pip)
{
  	int	i;
	while(parse_pip)
  	{
		  i = 0;
		  printf("-----------------------------------\n");
	if (parse_pip->cmd)
	{
		while (parse_pip->cmd[i])
		{
			printf("| parse_pip->cmd                  : %s            \n", parse_pip->cmd[i]);
	  	i++;
		}
	}
	i = 0;
	if (parse_pip->redir)
	{
		while (parse_pip->redir[i])
		{
				printf("| parse_pip->redir                : %s            \n", parse_pip->redir[i]);
	  		i++;
		}
	}
	i= 0;
	if (parse_pip->redir_temp)
	{
		while (parse_pip->redir_temp[i])
		{
				printf("| parse_pip->redir_temp              : %s            \n", parse_pip->redir_temp[i]);
	  		i++;
		}
	}
	printf("| parse_pip->path                 : %s            \n", parse_pip->path);
	printf("| parse_pip->read_file            : %d            \n", parse_pip->read_file);
	printf("| parse_pip->write_File           : %d            \n", parse_pip->write_file);
	printf("| parse_pip->error_syn_red        : %d            \n", parse_pip->error_syn_red);
		if (parse_pip->file_to_out)
			printf("| parse_pip->file_out             : %s            \n", parse_pip->file_to_out);
		if (parse_pip->file_to_in)
			printf("| parse_pip->file_in              : %s            \n", parse_pip->file_to_in);
	//printf("| parse_pip->single_quote         : %d            \n", parse_pip->single_quote);
  	//printf("| parse_pip->double_quote         : %d            \n", parse_pip->double_quote);
	//printf("| parse_pip->error_parse_Red      : %d            \n", parse_pip->error_parse_red);
	printf("-----------------------------------\n");
	parse_pip = parse_pip->next;
	i++;
	}
}

void	print_comm(t_comm comm)
{
	int a = 0;

		printf("-----------------------------------\n");
		while (comm.cmd[a] != NULL)
		{
			printf("| comm.cmd_sep           : %s            \n", comm.cmd[a]);
			a++;
		}
		a=0;
		if (comm.redir)
		{
			while (comm.redir[a])
				{
						printf("| comm.redir             : %s            \n", comm.redir[a]);
						a++;
				}
		}
		int j = 0;
		while (comm.redir_temp[j])
		{
						printf("| comm.redir_temp        : %s\n", comm.redir_temp[j]);
				j++;
		}
		// printf("| comm.nb_pipe        : %d            \n", comm.nb_pipe);
		// printf("| comm.redir_input    : %d            \n", comm.redir_input);
		// printf("| comm.redir_output   : %d            \n", comm.redir_output);
		// printf("| comm.single_quote   : %d            \n", comm.single_quote);
		// printf("| comm.double_quote   : %d            \n", comm.double_quote);
		// printf("| comm.error_parse    : %d            \n", comm.error_parse_red);
		printf("| comm.redir_double_in   : %d            \n", comm.redir_double_input);
		printf("-----------------------------------\n");
}

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

void	error_synthax_red(t_pipe *comm_pip)
{
	while (comm_pip)
	{
		if (ft_error_parse_red(comm_pip->redir) == 0)
		{	
			printf("Minishell: syntax error near unexpected token\n");
			return ;
		}
		comm_pip = comm_pip->next;
	}
}

void	not_valid_comm(t_pipe *comm_pip)
{
	while (comm_pip)
	{
		if (comm_pip->path == NULL)
			printf("%s: command not found\n", comm_pip->cmd[0]);
		comm_pip = comm_pip->next;
	}
}

int	pipe_glitch(char *line, t_comm comm, t_list **a_list, t_list **b_list)
{
	char	**cmd;
	char	**red_double;
	int		j;
	int		i;
	t_pipe	*comm_pip;
	int		fd;
	int		retclone;
	int		nb_cmds;
	int		last_cmd;

	j = 0;
	last_cmd = 1;
	i = 0;
	cmd = ft_split(line, '|');
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
	comm_pip = parcing_comm_pip(cmd[i], comm, a_list, i);
	while (i-- > 0)
		comm_pip = new_parcing_comm_pip(cmd[i], comm, comm_pip, a_list);
	print_pipe(comm_pip);
	error_synthax_red(comm_pip);
	not_valid_comm(comm_pip);
	exec_pipe(comm_pip, a_list, b_list);
	return (retclone);
}

static void	handle_sigusr1(int s, siginfo_t *siginfo, void *context)
{
	if (s == 2)
		printf("\n$> ");
	if (s == 3)
		return ;
	if (s == 1)
		return ;
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

int	main(int argc, char **argv, char **envp)
{
	t_comm				comm;
	t_list				*a_list;
	t_list				*b_list;
	char				*line;
	struct sigaction	sa;

	if (argc != 1)
	{
		printf("Too much arguments, usage : './minishell'.\n");
		exit(EXIT_FAILURE);
	}
	sa.sa_sigaction = handle_sigusr1;
	sa.sa_flags = SA_SIGINFO;
	comm.env = NULL;
	make_list(&a_list, envp);
	make_list(&b_list, envp);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGHUP, &sa, NULL);
	kill(SIGINT, 0);
	kill(SIGQUIT, 0);
	kill(SIGHUP, 0);
	while (1)
	{
		line = readline("$> ");
		if (line[0])
		{
			add_history(line);
			if (!only_space(line) && !unclosed_quotes2(line))
				parcing(line, comm, &a_list, &b_list);
		}
		free(line);
	}
	free_comm(comm);
	return (0);
}
