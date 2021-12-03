# minishell

void  inthandler(int sig)
{
    signal(sig, SIG_IGN);
	if (sig == SIGINT)
	{ 	
		printf("\n");
		rl_on_new_line();
   		rl_redisplay();
		printf("$> ");
	}

}

int	main(int argc, char **argv, char **envp)
{
	t_comm				comm;
	t_list				*a_list;
	t_list				*b_list;
	char				*line;

	argv = NULL;
	if (argc != 1)
	{
		printf("Too much arguments, usage : './minishell'.\n");
		exit(EXIT_FAILURE);
	}
	comm.env = NULL;
	make_list(&a_list, envp);
	make_list(&b_list, envp);
	while (1)
	{
		signal(SIGINT, inthandler);
		signal(SIGQUIT, inthandler);
		line = readline("$> ");
		if (line == NULL)
		{
			printf("exit\n");
			return (0);
		}
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
