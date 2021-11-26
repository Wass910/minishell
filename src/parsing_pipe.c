
#include "../inc/minishell.h"

t_pip *fill_redir_attribut(t_pip *parse_pip, int to_read, int to_write)
{
	if(to_read >= 0)
	{
		parse_pip->file_to_in = ft_strcat_red("", parse_pip->redir[to_read]);
		parse_pip->read_file = open_file(parse_pip->redir[to_read]);
	}
	else
		parse_pip->file_to_in = NULL;
  	if(to_write >= 0)
    {
		parse_pip->file_to_out= ft_strcat_red("", parse_pip->redir[to_write]);
		parse_pip->write_file = open_file2(parse_pip->redir[to_write]);
	}
	else 
		parse_pip->file_to_out = NULL;
	return (parse_pip);
}

t_pip *open_file_redir(t_pip *parse_pip)
{
	int retnd;
	int i = 0;
	t_pip *tmp;
	int err;
	int to_read = -1;
  	int to_write = -1;
	
	if (parse_pip->redir)
	{
		while (parse_pip->redir[i])
		{
			if (parse_pip->redir[i] && ft_strchr(parse_pip->redir[i], '>') > 0)
			{
				retnd = open_file2(parse_pip->redir[i]);
				if (retnd == -1)
					parse_pip->not_fil_red = 1;
				if (retnd != -1)
					to_write = i;
			}
			if (parse_pip->redir[i] && ft_strchr(parse_pip->redir[i], '<') > 0)
			{
				retnd = open_file(parse_pip->redir[i]);
				if (retnd == -1)
					parse_pip->not_fil_red = 1;
				if (retnd != -1)
					to_read = i;
			}
			i++;
		}
	}
	parse_pip = fill_redir_attribut(parse_pip, to_read, to_write);
	return parse_pip;
}

// char *split_command_one_redir(char*str)
// {
// 	if((str[i] == '>' && str[i + 1] != '>') || str[i] == '<')
// 	{
// 			cmd[j] = ' ';
// 			j++;
// 		}
// 		if(str[i] == '<')
// 		{
// 			count = i + 1;
// 			while(str[count] == ' ')
// 				count++;
// 			if (str[count] == '>')
// 			{
// 				i = count + 1;
// 				count++;
// 				if (str[count] == ' ')
// 				{
// 					while(str[count] == ' ')
// 					{
// 						count++;
// 						i++;
// 					}

// 				}
// 			}
// 		}
// }

char *ft_split_command(char *str)
{
	char *cmd;
	int i;
	int j;
	int count;

	j = 0;
	i = 0;
	cmd = malloc(sizeof(char) * 100);
	i = 0;
	while(str[i] != '\0')
	{
		if((str[i] == '>' && str[i + 1] != '>') || str[i] == '<')
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
				i = count;
				cmd[j] = ' ';
				j++;
				if (str[i] == ' ')
				{
					while(str[i] == ' ')
					{
						count++;
						i++;
					}

				}
				while(str[i] != ' ' && str[i] != '<' && str[i] != '>')
				{
					cmd[j] = str[i];
					j++;
					i++;
				}
			}
		}
		if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] != '>')
		{
			if (str[i + 2] == ' ')
			{
				cmd[j] = ' ';
				j++;
				while(str[i] != ' ')
				{
					cmd[j] = ' ';
					j++;
					cmd[j] = str[i];
					j++;
					i++;
				}
			}
			else
			{
				cmd[j] = ' ';
				j++;
				while(str[i] == '>')
				{
					cmd[j] = str[i];
					j++;
					i++;
				}
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
	parse_pip->cmd[count] = NULL;
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
	parse_pip->redir = malloc(sizeof(char *) * (50));
	while (tmp_all[dest]) 
	{
		if (ft_strchr(tmp_all[dest], '>') > 0 || ft_strchr(tmp_all[dest], '<') > 0)
		{
			if (tmp_all[dest][1])
				parse_pip->redir[count_out] = ft_strcat_red_glu("", tmp_all[dest]);
			else if (tmp_all[dest + 1])
				parse_pip->redir[count_out] = ft_strcat_redf(tmp_all[dest], tmp_all[dest +1]);
			count_out++;
		}
	dest++;
	}
	parse_pip->redir[count_out] = NULL;
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
		new->redir = NULL;
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
	parse_pip->not_fil_red = 0;
  parse_pip = redirection(parse_pip, tmp_all, str);
	parse_pip->path = path(parse_pip->cmd[0]);
  parse_pip->redir_output_A = ft_double_strchr(str, '>');
	parse_pip->redir_double_input = ft_double_strchr(str, '<');
  parse_pip->read_file = 0;
  parse_pip->write_file = 0;
  parse_pip->single_quote = 0;
  parse_pip->double_quote = 0;
  parse_pip->nb_cmd = i;
  parse_pip = open_file_redir(parse_pip);
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
  new->not_fil_red = 0;
	tmp_all = ft_split(str,' ');
	new = redirection(new, tmp_all, str);
	new->path = path(new->cmd[0]);
  free_str(tmp_all);
	new = open_file_redir(new);
	return new;
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
	int j = 0;
	if (parse_pip->redir_temp)
	{
			while (parse_pip->redir_temp[j])
		{
						printf("| parse_pipe->redir_temp            : %s\n", parse_pip->redir_temp[j]);
				j++;
		}
	}
	// printf("| parse_pip->file_to_out          : %s            \n", parse_pip->file_to_out);
  	// printf("| parse_pip->file_to_in           : %s            \n", parse_pip->file_to_in);
	//printf("| parse_pip->redir_output_A       : %d            \n", parse_pip->redir_output_A);
  	//printf("| parse_pip->redir_double_input   : %d            \n", parse_pip->redir_double_input);
	//printf("| parse_pip->single_quote         : %d            \n", parse_pip->single_quote);
  	//printf("| parse_pip->double_quote         : %d            \n", parse_pip->double_quote);
	//printf("| parse_pipe->redir_double_in         : %d            \n", parse_pip->redir_double_input);
	// printf("| parse_pip->error_parse_Red      : %d            \n", parse_pip->error_parse_red);
	// printf("| parse_pip->read_file            : %d            \n", parse_pip->read_file);
	// printf("| parse_pip->write_file           : %d            \n", parse_pip->write_file);
	printf("-----------------------------------\n");
    parse_pip = parse_pip->next;
    i++;
    }
}
// void	free_pip(t_pip *pipe)
// {
//   while (pipe)
// 	{
//     free(path);
//     free_str(pipe->cmd);
//     if (pipe->file_out)
//       free_str(pipe->file_out);
//     if (pipe->file_in)
//       free_str(pipe->file_in);
//     pipe = pipe->next;
//   }
// }

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