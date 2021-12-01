# minishell

void exec_pipe(t_pipe *comm_pip, t_list **a_list, t_list **b_list)
{
	int last_cmd;

	last_cmd = 1;
	while(comm_pip)
	{
		if (ft_error_parse_red(comm_pip->redir) == 0)
		{	
			printf("Minishell: syntax error near unexpected token\n");
			comm_pip->error_syn_red = 1;
		}
		if(!comm_pip->next)
			last_cmd = 0;
		if (comm_pip->write_file >= 0 && comm_pip->read_file == -1)
			pipex_write(comm_pip, last_cmd, a_list, b_list);
		else if (comm_pip->write_file == -1 && comm_pip->read_file == -1)
			pipex(comm_pip, last_cmd, a_list, b_list);
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
}

int pipe_glitch(char *line, t_comm comm, t_list **a_list, t_list **b_list)
{
	char **cmd;
	char	**red_double;
	int j = 0;
	int i = 0;
	t_pipe *comm_pip;
	int nb_cmds;

	cmd = ft_split(line, '|');
	red_double = double_in(line, a_list);
	while	(red_double && red_double[j])
			j++;
	if (red_double && red_double[0])
		ft_redir_temp(red_double, j);
	while (cmd[i])
    	i++;
	nb_cmds = i;
  	i--;
	comm_pip = parcing_comm_pip(cmd[i], comm, a_list, i);
	while(i-- > 0)
		comm_pip = new_parcing_comm_pip(cmd[i], comm, comm_pip, a_list, i);
    print_pipe(comm_pip);
    exec_pipe(comm_pip, a_list, b_list);
  	return 0;
}