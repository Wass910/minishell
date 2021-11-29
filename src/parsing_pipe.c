
#include "../inc/minishell.h"

char *ft_split_command(char *str)
{
	char *cmd;
	int i;
	int j;
	int count;
	char *file_to_create;
	int a;

	j = 0;
	i = 0;
	a = 0;
	file_to_create = malloc(sizeof(char) * 100);
	if (!file_to_create)
		return (NULL);
	while(str[i] != '\0')
	{
		if (str[i] == '>')
			i++;
		i++;
	}
	cmd = malloc(sizeof(char) * i + 20);
	if (!cmd)
		return (NULL);
	i = 0;
	while(str[i] != '\0')
	{
		if(str[i] == '>' || str[i] == '<')
		{
			cmd[j] = ' ';
			j++;
		}
		if(str[i] == '<')
		{
			count = i + 1;
			while(str[count] == ' ')
				count++;
			if (str[count] == '>')
			{
				i = count + 1;
				count++;
				if (str[count] == ' ')
				{
					while(str[count] == ' ')
					{
						count++;
						i++;
					}

				}
				while(str[count] != ' ' && str[count] != '\0' && str[count] != '<' && str[count] != '>')
				{
					file_to_create[a] = str[count];
					a++;
					count++;
					i++;
				}
				file_to_create[a] = '\0';
				printf("file to create = %s\n", file_to_create);
				
			}
		}
		cmd[j] = str[i];
		j++;
		i++;
	}
	cmd[j] = '\0';
	return cmd;
}

int error_in_red(char *str)
{
	int i;
	int j;
	int a;
	char *file_to_create;

	j = 0;
	i = 0;
	a = 0;
	file_to_create = malloc(sizeof(char) * 100);
	if (!file_to_create)
		return (1);
	while(str[i] != '\0')
	{
		if(str[i] == '>')
		{
			j = i + 1;
			while(str[j] == ' ')
				j++;
			if (str[j] == '<')
					return ERROR_RED;
		}
		if(str[i] == '<')
		{
			j = i + 1;
			while(str[j] == ' ')
				j++;
			if (str[j] == '>' && str[j + 1] == '>')
					return ERROR_RED;
		}
		i++;
	}
	return 0;
}

t_pip	*initializing_cmd(t_pip *parse_pip, char **tmp_all)
{
	int dest;
	int count;

	parse_pip->cmd = malloc(sizeof(char *) * (50));
	if (!parse_pip->cmd)
		return (NULL);
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

t_pip	*initializing_red(t_pip *parse_pip, char **tmp_all)
{
	int count_out;
	int count_in;
	int dest;
	dest = 0;
	count_out = 0;
	count_in = 0;
	parse_pip->file_out = malloc(sizeof(char *) * (50));
	if (!parse_pip->file_out)
		return(NULL);
	parse_pip->file_in = malloc(sizeof(char *) * (50));
	if (!parse_pip->file_in)
		return(NULL);
	while (tmp_all[dest]) 
	{
		if (ft_strchr(tmp_all[dest], '>') > 0)
		{
			if (tmp_all[dest][1])
				parse_pip->file_out[count_out] = ft_strcat_red_glu("", tmp_all[dest]);
			else if (tmp_all[dest + 1])
				parse_pip->file_out[count_out] = ft_strcat_redf(tmp_all[dest], tmp_all[dest +1]);
			count_out++;
		}
		if (ft_strchr(tmp_all[dest], '<') > 0)
		{
			if (tmp_all[dest][1])
				parse_pip->file_in[count_in] = ft_strcat_red_glu("", tmp_all[dest]);
			else if (tmp_all[dest + 1])
				parse_pip->file_in[count_in] = ft_strcat_redf(tmp_all[dest], tmp_all[dest +1]);
			count_in++;
		}
	dest++;
	}
	parse_pip = initializing_cmd(parse_pip, tmp_all);
	return parse_pip;	
}

t_pip	*check_initializing_red(t_pip *parse_pip, char **tmp_all, char *str)
{
	char *cmd;
	char **to_parse;
	cmd = ft_split_command(str);
	if (error_in_red(str) == ERROR_RED)
		parse_pip->error_parse_red = 1;
	to_parse = ft_split(cmd, ' ');
	parse_pip = initializing_red(parse_pip, to_parse);
	return parse_pip;	
}

t_pip   *redirection(t_pip *new, char **tmp_all, char *str)
{
  if (new->redir_input > 0 || new->redir_output > 0)
	{
		new = check_initializing_red(new, tmp_all, str);
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
	char **tmp_all;
	
	if (!(parse_pip = (t_pip *)malloc(sizeof(*parse_pip))))
		return (NULL);
  tmp_all = ft_split(str, ' ');
  parse_pip->error_parse_red = 0;
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
	new->error_parse_red = 0;
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
	//printf("| parse_pip->redir_output_A       : %d            \n", parse_pip->redir_output_A);
  	//printf("| parse_pip->redir_double_input   : %d            \n", parse_pip->redir_double_input);
	//printf("| parse_pip->single_quote         : %d            \n", parse_pip->single_quote);
  	//printf("| parse_pip->double_quote         : %d            \n", parse_pip->double_quote);
	printf("| parse_pip->error_parse_Red      : %d            \n", parse_pip->error_parse_red);
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
	t_pip *tmp;
	int cmd_begin = 0;
	int err = 0;
	char **str_err;

    i = 0;
    while (comm.cmd[i])
    { 
     // printf("cmd = %s\n", comm.cmd[i]);
         i++;

    }
    i--;
    nb_cmds  = i + 1;
    parse_pip = ft_lstnew_pip(comm.cmd[i], i + 1);
    while(i-- > 0)
        parse_pip = fill_parse_pipe(parse_pip, comm.cmd[i], i + 1);
	//print_pipe(parse_pip);
	tmp = parse_pip;
	i = 0;
	while(tmp)
	{
		if(tmp->path == NULL)
		{
			printf("%s :commande not found\n", tmp->cmd[0]);
			cmd_begin = i + 1;
		}
		i++;
		tmp = tmp->next;
	}
	printf("cmd = %d\n", cmd_begin);
	while (cmd_begin > 0)
	{
		parse_pip = parse_pip->next;
		cmd_begin--;
		nb_cmds--;
	}
	//print_pipe(parse_pip);
	if (parse_pip)
	{
		if(nb_cmds == 1)
		{
			if (ft_strncmp(parse_pip->cmd[0], "cat", 3) == 0 || 
					ft_strncmp(parse_pip->cmd[0], "grep", 4) == 0)
				return ;
			else if (ft_strncmp(parse_pip->cmd[0], "wc", 3) == 0 && parse_pip->cmd[1])
			{
				printf("0\n");
				return ;
			}
			else if (ft_strncmp(parse_pip->cmd[0], "wc", 3) == 0 && !parse_pip->cmd[1])
			{
				printf("      0       0       0\n");
				return ;
			}
			else
				pipex_for_one(parse_pip);
		}
		else
		{
			if (ft_strncmp(parse_pip->cmd[0], "cat", 3) == 0 || 
					ft_strncmp(parse_pip->cmd[0], "grep", 4) == 0 || 
					ft_strncmp(parse_pip->cmd[0], "wc", 3) == 0)
			{
				while (ft_strncmp(parse_pip->cmd[0], "cat", 3) == 0 || 
					ft_strncmp(parse_pip->cmd[0], "grep", 4) == 0 || 
					ft_strncmp(parse_pip->cmd[0], "wc", 3) == 0)
				{
					parse_pip = parse_pip->next;
					nb_cmds--;
				}
			}
			if(nb_cmds == 1)
				pipex_for_one(parse_pip);
			else
				pipex(parse_pip, nb_cmds);
		
		}
	}
	return ;

      
    //pipex(parse_pip);
}