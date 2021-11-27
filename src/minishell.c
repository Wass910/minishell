#include "../inc/minishell.h"

void  prompt(void)
{
		write(1, "$>", ft_strlen("$>"));
}

int	open_file(char *filename)
{
	char *str;
	int i;
	filename++;
	i = open(filename, O_RDONLY);
	if (i == -1)
	{
		str = strerror(errno);
		printf("%s: %s\n", filename, str);
		return (-1);
	}
	return (i);
}

void	print_pipe(t_pipe *parse_pip)
{
  int		i ;
    while(parse_pip)
  	{
          i = 0;
          printf("-----------------------------------\n");
    printf("| parse_pip->nb_cmd               : %d            \n", parse_pip->nb_cmd);
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
		if (parse_pip->file_to_out)
      printf("| parse_pip->file_out             : %s            \n", parse_pip->file_to_out);
		if (parse_pip->file_to_in)
      printf("| parse_pip->file_in              : %s            \n", parse_pip->file_to_in);
	//printf("| parse_pip->redir_output         : %d            \n", parse_pip->redir_output);
  //	printf("| parse_pip->redir_input          : %d            \n", parse_pip->redir_input);
	//printf("| parse_pip->redir_output_A       : %d            \n", parse_pip->redir_output_A);
  	//printf("| parse_pip->redir_double_input   : %d            \n", parse_pip->redir_double_input);
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

int r_and_w_redirection(t_comm comm, t_list **a_list, t_list **b_list, char *str)
{
	int k;
	int status;
	k = fork();
	if (k == 0)
	{
		if (verif_the_builtin(comm.cmd))
		{
			dup2(comm.write_file,STDOUT);
			dup2(comm.read_file, STDIN);
			exec_cmd(str, comm);
		}
		else
		{
			dup2(comm.write_file,STDOUT);
			dup2(comm.read_file, STDIN);
			builtin(comm, a_list, b_list);
		}
		exit(0);
	}
	else
	{
		waitpid(k, &status, 0);
		k = WEXITSTATUS(status);
	}
	return k;
}

int r_redirection(t_comm comm, t_list **a_list, t_list **b_list, char *str)
{
	int k;
	int status;
	k = fork();
	if (k == 0)
	{
		if (verif_the_builtin(comm.cmd))
		{
		dup2(comm.read_file, STDIN);
		exec_cmd(str, comm);
		}
		else
		{
		dup2(comm.read_file, STDIN);
		builtin(comm, a_list, b_list);
		}
		exit(0);
	}
	else
	{
		waitpid(k, &status, 0);
		k = WEXITSTATUS(status);
	}
	return k;
}

int w_redirection(t_comm comm, t_list **a_list, t_list **b_list, char *str)
{
	int k;
	int status;
	k = fork();
	if (k == 0)
	{
		if (verif_the_builtin(comm.cmd))
		{
			dup2(comm.write_file,STDOUT);
			exec_cmd(str, comm);
		}
		else
		{
			dup2(comm.write_file, STDOUT);
			builtin(comm, a_list, b_list);
		}
		exit(0);
	}
	else
	{
		waitpid(k, &status, 0);
		k = WEXITSTATUS(status);
	}
	return k;
}

int red_uniq_comm(t_comm comm, char *str, t_list **a_list, t_list **b_list)
{
	comm.read_file = -3;
	comm.write_file = -3;
	int k;
	int retnd;
	int i = 0;
	int to_read = -1;
	int to_write = -1;
	int status;
	while (comm.redir[i])
	{
		if ((comm.redir[i] && (ft_strchr(comm.redir[i], '>') == 1 || ft_strchr(comm.redir[i], '>') == 2)))
		{
			 retnd = open_file2(comm.redir[i]);
			 close(retnd);
			if (retnd == -1)
				return (retnd);
			to_write = i;
		}
		if (comm.redir[i] && ft_strchr(comm.redir[i], '<') == 1 )
		{
			retnd = open_file(comm.redir[i]);
			if (retnd == -1)
				return (retnd);
			to_read = i;
		}
		i++;
	}
	if(to_read >= 0)
		comm.read_file = open_file(comm.redir[to_read]);
	if(to_write >= 0)
		comm.write_file = open_file2(comm.redir[to_write]);
	if(to_read >= 0 && to_write >= 0)
		k = r_and_w_redirection(comm, a_list, b_list, str);
	else if(to_read < 0 && to_write >= 0)
		 k = w_redirection(comm, a_list, b_list, str);
	else if(to_read >= 0 && to_write < 0)
		k = r_redirection(comm, a_list, b_list, str);
	else
	{
			if (access(str, F_OK) != 0)
			{
				printf("%s: command not found\n", comm.cmd[0]);
				return (1);
			}
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
	return k;
}

int uniq_cmd(t_comm comm, t_list **a_list, t_list **b_list)
{
		char **path;
		int k;
		char *str;
		int i = 0;
		int status;
		char *tmp;
		int write_file ;
		k = 0;
		//printf("comm = %s\n", comm.cmd[0]);
		if (comm.error_parse_red == 1)
		{
			printf("bash: syntax error near unexpected token\n");
			return 1;
		}
		path = ft_split(getenv2("PATH", a_list), ':');
		if (if_builtin(comm.cmd) == 0 && !comm.redir[0])
		{
			//printf("builtin to do.\n");
			comm.retclone = retval;
			k = builtin(comm, a_list, b_list);
			return (k);
		}
		//else
			//printf("continue the parse\n");
		//if(access(comm.cmd[0], F_OK) == 0)
			//printf("command found whithout path\n");
		if (path)
		{
			while (path[k])
			{
				str = ft_strcat_cmd(path[k], comm.cmd[0]);
				if (access(str, F_OK) == 0)
					k = 0;
				if (access(str, F_OK) == 0)
					break;
				k++;
			}
		}
		else
		{
			free(path);
			//printf("%s: No such file or directory\n", comm.cmd[0]);
			return (127);
		}
		if (access(str, F_OK) != 0 && !comm.redir[0])
		{
			printf("%s: command not found\n", comm.cmd[0]);
			return (127);
		}
		//printf("found with path command = %s\n", str);
		if (comm.redir[0])
		{
			//printf("continue the parse\n");
			k = red_uniq_comm(comm, str, a_list, b_list);
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
		free(path);
		return (k);
}

int  redir_comm(t_comm comm, t_list **a_list, t_list **b_list)
{
			return(uniq_cmd(comm, a_list, b_list));
		return (0);
}

t_comm  ft_double_left_red(t_comm comm)
{
	int i = 0;
	int count = 0;
	int count_temp = 2;
	int temp_index = 0;
	comm.redir_double_input = 0;
	comm.redir_temp = malloc(sizeof(char *) * 150);
	while (comm.redir[i])
	{
		if(comm.redir[i][0] && comm.redir[i][1] && comm.redir[i][2] &&
			(comm.redir[i][0] == '<' && comm.redir[i][1] == '<' && comm.redir[i][2] != '<'))
		{
			comm.redir_temp[count] = malloc(sizeof(char) * 150);
			if (comm.redir[i][count_temp])
			{
				while(comm.redir[i][count_temp] != '\0')
				{
					comm.redir_temp[count][temp_index] = comm.redir[i][count_temp];
					temp_index++;
					count_temp++;  
				}
				comm.redir_double_input++;
				comm.redir_temp[count][temp_index] = '\0';
				count++;
				count_temp = 2 ;
				temp_index = 0;
			} 
		}
		i++;
	}
	comm.redir_temp[count] = NULL;
	return comm;
}

void ft_redir_temp(char **str, int input)
{
	int i = 0;
	int ret;
	char *line;

	ret = get_next_line(0, &line);
	while (ret > 0 )
	{
		if ((ft_strncmp(line, str[i], ft_strlen(str[i])) == 0) &&
			 ft_strlen(line) == ft_strlen(str[i]))
			i++;
		if (i == input)
			return ;
		free(line);
		ret = get_next_line(0, &line);
	}
	return ;
}

int    parcing(char *all_cmd, t_comm comm, t_list **a_list, t_list **b_list)
{
		char **str;
		char *cmd_new;
		int i;

		if (ft_strchr(all_cmd, '|') > 0)
		{
			pipe_glitch(all_cmd,comm, a_list, b_list);
			return (1);
		}
		cmd_new = malloc(sizeof(char) * 100);
		cmd_new = split_glitch(all_cmd);
		printf("after glitch = %s\n", cmd_new);
		str = ft_split(cmd_new, ' ');
		cmd_new = parse_quotes(str, a_list, comm);
		printf("after quote parse  = %s\n", cmd_new);
		comm = fill_comm(comm, cmd_new);
		if (ft_error_parse_red(comm.redir) == 0)
		{
			printf("Minishell: syntax error near unexpected token\n");
			return -1;
		}
		comm = ft_double_left_red(comm);
		if (comm.redir_temp[0])
			ft_redir_temp(comm.redir_temp, comm.redir_double_input);
		print_comm(comm);
		return (redir_comm(comm, a_list, b_list));
}

t_pipe   *parcing_comm_pip(char *all_cmd, t_comm comm, t_list **a_list, int i)
{
		char **str;
		char *cmd_new;
		t_pipe *new;

		new = malloc(sizeof(*new));
		if (new == NULL)
			exit(EXIT_FAILURE);

		cmd_new = malloc(sizeof(char) * 100);
		cmd_new = split_glitch(all_cmd);
		str = ft_split(cmd_new, ' ');
		cmd_new = parse_quotes(str, a_list, comm);
		new = fill_comm_pip(new, cmd_new);
		new->redir_temp = malloc(sizeof(char *) * 150);
		new->redir_temp[0] = NULL;
		new->nb_cmd = i;
		new->path = path(new->cmd[0], a_list);
    new->read_file = -1;
    new->write_file = -1;
		new->next = NULL;
		return (new);
}

t_pipe   *new_parcing_comm_pip(char *all_cmd, t_comm comm, t_pipe *pipe, t_list **a_list, int i)
{
		char **str;
		char *cmd_new;
		t_pipe  *new;


		new = malloc(sizeof(*new));
		if (new == NULL)
			exit(EXIT_FAILURE);
		cmd_new = malloc(sizeof(char) * 100);
		cmd_new = split_glitch(all_cmd);
		str = ft_split(cmd_new, ' ');
		cmd_new = parse_quotes(str, a_list, comm);
		new = fill_comm_pip(new, cmd_new);
		new->redir_temp = malloc(sizeof(char *) * 150);
		new->redir_temp[0] = NULL;
		new->path = path(new->cmd[0], a_list);
    new->read_file = -1;
    new->write_file = -1;
		new->nb_cmd = i;
		
		new->next = pipe;
		return (new);
}

char   **double_in(char *all_cmd, t_list **a_list)
{
		char **str;
		char *cmd_new;
		t_comm comm;

		cmd_new = malloc(sizeof(char) * 100);
		cmd_new = split_glitch(all_cmd);
		str = ft_split(cmd_new, ' ');
		cmd_new = parse_quotes(str, a_list, comm);
		comm = fill_comm(comm, cmd_new);
		comm = ft_double_left_red(comm);
		if (comm.redir_temp[0])
			return (comm.redir_temp);
		return (NULL);
}

int pipe_glitch(char *line, t_comm comm, t_list **a_list, t_list **b_list)
{
	char **cmd;
	char	**red_double;
	int j = 0;
	cmd = ft_split(line, '|');
	int i = 0;
	t_pipe *comm_pip;
	int fd;
	int retclone;
	int nb_cmds;
	red_double = double_in(line, a_list);
	while	(red_double && red_double[j])
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
	while(i-- > 0)
		comm_pip = new_parcing_comm_pip(cmd[i], comm, comm_pip, a_list, i);
  //print_pipe(comm_pip);
  while(comm_pip->next)
	{
		pipex(comm_pip, 1);
		comm_pip = comm_pip->next;
	}
	pipex(comm_pip, 0);
	write(1, "lol\n", 4);
	write(1, "lol1\n", 5);
  return retclone;
}

static void    handle_sigusr1(int s, siginfo_t *siginfo, void *context)
{
	if (s == 2)
		printf("\n$> ");
	if (s==3)
		return;
	if (s==1)
		return;
}

int main(int argc, char **argv, char **envp)
{
		t_comm  comm;
		t_list *a_list;
		t_list *b_list;
		char *line;
		struct sigaction sa;
		(void)argc;

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
				retval = parcing(line, comm, &a_list, &b_list);
			}
			free(line);
		}
		return 0;
}