
#include "../inc/minishell.h"

t_pip	*initializing_redout(t_pip *parse_pip, char **tmp_all)
{
	int count;
	int dest;
	dest = 0;
	count = 0;
	while (tmp_all[dest]) 
	{
		if (ft_strchr(tmp_all[dest], '>') > 0 && ft_strchr(tmp_all[dest], '<') <= 0)
		{
			if (tmp_all[dest][1])
				parse_pip->file_out[count] = ft_strcat_red_glu("", tmp_all[dest]);
			else if (tmp_all[dest + 1])
				parse_pip->file_out[count] = ft_strcat_redf(tmp_all[dest], tmp_all[dest +1]);
			count++;
		}
	dest++;
	}
	parse_pip->cmd = malloc(sizeof(char *) * (50));
	dest = 0;
	count = 0;
	while (tmp_all[dest]) 
	{
		if (ft_strchr(tmp_all[dest], '>') == 0 && ft_strchr(tmp_all[dest], '<') == 0)
		{
			parse_pip->cmd[count] = ft_strcat_red("", tmp_all[dest]);
			count++;
		}
		else
			if (!tmp_all[dest][1])
				dest++;
		dest++;
	}
	return parse_pip;	
}

t_pip	*initializing_redin(t_pip *parse_pip, char **tmp_all)
{
	int count;
	int dest;
	dest = 0;
	count = 0;
	while (tmp_all[dest]) 
	{
		if (ft_strchr(tmp_all[dest], '<') > 0 && ft_strchr(tmp_all[dest], '>') <= 0)
		{
			if (tmp_all[dest][1])
				parse_pip->file_in[count] = ft_strcat_red_glu("", tmp_all[dest]);
			else if (tmp_all[dest + 1])
				parse_pip->file_in[count] = ft_strcat_redf(tmp_all[dest], tmp_all[dest +1]);
			count++;
		}
	dest++;
	}
	parse_pip->cmd = malloc(sizeof(char *) * (50));
	dest = 0;
	count = 0;
	while (tmp_all[dest]) 
	{
		if (ft_strchr(tmp_all[dest], '<') == 0)
		{
			parse_pip->cmd[count] = ft_strcat_red("", tmp_all[dest]);
			count++;
		}
		else
			if (!tmp_all[dest][1])
				dest++;
		dest++;
	}
	return parse_pip;	
}

t_pip   *redirection(t_pip *new, char **tmp_all, char *str)
{
  if (new->redir_input > 0 && new->redir_output <= 0)
	{
		new->file_in = malloc(sizeof(char *) * (new->redir_input + 1));
		new = initializing_redin(new, tmp_all);
		new->file_out = NULL;
	}
	else if (new->redir_output > 0 && new->redir_input <= 0)
	{
		new->file_out = malloc(sizeof(char *) * (new->redir_output + 1));
		new->file_in = NULL;
		new = initializing_redout(new, tmp_all);
	}
	else if (new->redir_output > 0 && new->redir_input > 0)
	{
		new->file_out = malloc(sizeof(char *) * (new->redir_output + 1));
		new->file_in = malloc(sizeof(char *) * (new->redir_input + 1));
		new = initializing_redin(new, tmp_all);
		new = initializing_redout(new, tmp_all);
	}
	else
	{
		new->cmd = ft_split(str,' ');
		new->file_out = NULL;
		new->file_in = NULL;
	}
  return new;
}

t_pip	*ft_lstnew_pip(char *str, int i)
{
	t_pip *parse_pip;
	int dest = 0;
	int count = 0;
	char **tmp_all;
	
	if (!(parse_pip = (t_pip *)malloc(sizeof(*parse_pip))))
		return (NULL);
  tmp_all = ft_split(str, ' ');
	parse_pip->redir_output = ft_redir_strchr(str, '>');
	parse_pip->redir_input = ft_redir_strchr(str, '<');
  parse_pip = redirection(parse_pip, tmp_all, str);
	parse_pip->path = path(parse_pip->cmd[0]);
  parse_pip->redir_output_A = ft_double_strchr(str, '>');
	parse_pip->redir_double_input = ft_double_strchr(str, '<');
  parse_pip->read_file = 0;
  parse_pip->write_file = 0;
  parse_pip->single_quote = 0;
  parse_pip->double_quote = 0;
  parse_pip->nb_cmd = i;
	parse_pip->next = NULL;
  free_str(tmp_all);
	return (parse_pip);
}

t_pip	*fill_parse_pipe(t_pip *parse_pip, char *str, int i)
{
    t_pip	*new;
	char	**tmp_all;
	int count = 0;
	int dest = 0;
	
	new = malloc(sizeof(*new));
	if (new == NULL)
		exit(EXIT_FAILURE);
  new->nb_cmd = i;
	new->next = parse_pip;
	new->redir_output = ft_redir_strchr(str, '>');
	new->redir_input = ft_redir_strchr(str, '<');
  new->redir_output_A = ft_double_strchr(str, '>');
	new->redir_double_input = ft_double_strchr(str, '<');
  new->read_file = 0;
  new->write_file = 0;
  new->single_quote = 0;
  new->double_quote = 0;
	tmp_all = ft_split(str,' ');
	new = redirection(new, tmp_all, str);
	new->path = path(new->cmd[0]);
  free_str(tmp_all);
	return new;
}

void	print_pipe(t_pip *parse_pip)
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
	if (parse_pip->file_out)
	{
		while (parse_pip->file_out[i])
    	{
        	printf("| parse_pip->file_out             : %s            \n", parse_pip->file_out[i]);
      		i++;
    	}
	}
	i= 0;
	if (parse_pip->file_in)
	{
		while (parse_pip->file_in[i])
    	{
        	printf("| parse_pip->file_in              : %s            \n", parse_pip->file_in[i]);
      		i++;
    	}
	}
    printf("| parse_pip->path                 : %s            \n", parse_pip->path);
	printf("| parse_pip->redir_output         : %d            \n", parse_pip->redir_output);
  	printf("| parse_pip->redir_input          : %d            \n", parse_pip->redir_input);
	printf("-----------------------------------\n");
    parse_pip = parse_pip->next;
    i++;
    }
}
void	free_pip(t_pip *pipe)
{
  while (pipe)
	{
    free(path);
    free_str(pipe->cmd);
    if (pipe->file_out)
      free_str(pipe->file_out);
    if (pipe->file_in)
      free_str(pipe->file_in);
    pipe = pipe->next;
  }
}

void    parsing_pipes(t_comm comm)
{
    t_pip *parse_pip;
    int i;
    int nb_cmds;
    pid_t pid1;
    int pipefd[2];
    int file;

    file = open("outfile", O_CREAT | S_IWOTH);
    i = 0;
    while (comm.cmd[i])
    { 
      printf("cmd = %s\n", comm.cmd[i]);
         i++;

    }
    i--;
    nb_cmds  = i + 1;
    parse_pip = ft_lstnew_pip(comm.cmd[i], i + 1);
    while(i-- > 0)
        parse_pip = fill_parse_pipe(parse_pip, comm.cmd[i], i + 1);
    print_pipe(parse_pip);
    //free_pip(parse_pip);
    while (nb_cmds > 1)
    {
      int pipefd[2];
      pid_t pid1;

      if (pipe(pipefd) == -1)
        exit(EXIT_FAILURE);
      pid1 = fork();
      if (pid1 == -1)
        exit(EXIT_FAILURE);
      if (pid1)
      {
        close(pipefd[1]);
          dup2(pipefd[0], STDIN);
        waitpid(pid1, NULL, 0);	
        //execve(data->next->path, data->next->cmd, NULL);
      }
      else
      {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT);
        execve(parse_pip->path, parse_pip->cmd, NULL);
        return ;
      }
      parse_pip = parse_pip->next;
      nb_cmds--;
    }
    i = fork();
    if (i)
    {
      dup2(STDIN, pipefd[0]);
      dup2(STDOUT,pipefd[1]);
        waitpid(i, NULL, 0);
    }
    else{
        execve(parse_pip->path, parse_pip->cmd, NULL);
    }  
    // dup2(STDIN, pipefd[0]);
    // dup2(STDOUT,pipefd[1]);
    // execve(parse_pip->path, parse_pip->cmd, NULL);
    return ;

      
    //pipex(parse_pip);
}