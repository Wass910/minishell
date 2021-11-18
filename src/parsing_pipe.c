
#include "../inc/minishell.h"

// t_pip	*ft_lstnew_pip(char *str, int i)
// {
// 	t_pip *parse_pip;

// 	if (!(parse_pip = (t_pip *)malloc(sizeof(*parse_pip))))
// 		return (NULL);
//     if(ft_double_strchr(str, '>') == -1 || ft_double_strchr(str, '<') == -1)
//     {
//        printf("Invalid redirection.\n");
//         exit(EXIT_FAILURE);
//     }
//     parse_pip->cmd = str;
//     parse_pip->redir_input = ft_redir_strchr(str, '<');
//     parse_pip->redir_output = ft_redir_strchr(str, '>');
//     parse_pip->redir_double_input = ft_double_strchr(str, '<');
//     parse_pip->redir_output_A = ft_double_strchr(str, '>');
//     parse_pip->single_quote = ft_strchr(str, 39);
//   	parse_pip->double_quote = ft_strchr(str, '"');
//     parse_pip->nb_cmd = i;
// 	parse_pip->next = NULL;
// 	return (parse_pip);
// }

// t_pip	*fill_parse_pipe(t_pip *parse_pip, char *str, int i)
// {
//     t_pip	*new;

// 	new = malloc(sizeof(*new));
// 	if (new == NULL)
// 		exit(EXIT_FAILURE);
//     new->cmd = str;
//     new->redir_input = ft_redir_strchr(str, '<');
//     new->redir_output = ft_redir_strchr(str, '>');
//     new->single_quote = ft_strchr(str, 39);
//   	new->double_quote = ft_strchr(str, '"');
//     new->redir_double_input = ft_double_strchr(str, '<');
//     new->redir_output_A = ft_double_strchr(str, '>');
//     new->nb_cmd = i;
//     new->next = parse_pip;
// 	//printf("c = %s\n", cmd);
//   	// comm.nb_pipe = ft_strchr(cmd, '|');
//   	// comm.redir_input = ft_strchr(cmd, '<');
//   	// comm.redir_output = ft_strchr(cmd, '>');
// 	// comm.single_quote = ft_strchr(cmd, 39);
//   	// comm.double_quote = ft_strchr(cmd, '"');
// 	return new;
// }

// void	print_pipe(t_pip *parse_pip)
// {
//   int		i = 0 ;
//     while(parse_pip)
//   	{
//           printf("-----------------------------------\n");
//     printf("| parse_pip->nb_cmd               : %d            \n", parse_pip->nb_cmd);
//     printf("| parse_pip->cmd                  : %s            \n", parse_pip->cmd);
//     printf("| parse_pip->redir_input          : %d            \n", parse_pip->redir_input);
//     printf("| parse_pip->redir_output         : %d            \n", parse_pip->redir_output);
//     printf("| parse_pip->redir_double_input   : %d            \n", parse_pip->redir_double_input);
//     printf("| parse_pip->redir_output_A       : %d            \n", parse_pip->redir_output_A);
//     printf("| parse_pip->single_quote         : %d            \n", parse_pip->single_quote);
//     printf("| parse_pip->double_quote         : %d            \n", parse_pip->double_quote);
//   	printf("-----------------------------------\n");
//     parse_pip = parse_pip->next;
//     i++;
//     }
// }

t_pip	*initializing_redout(t_pip *parse_pip, char **tmp_all)
{
	int count;
	int dest;
	dest = 0;
	count = 0;
	//printf("input = %d\n", parse_pip->redir_input);
	while (tmp_all[dest]) 
	{
		if (ft_strchr(tmp_all[dest], '>') > 0)
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
		if (ft_strchr(tmp_all[dest], '<') > 0)
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

t_pip	*ft_lstnew_pip(char *str, int i)
{
	t_pip *parse_pip;
	int dest = 0;
	int count = 0;
	char **tmp_all;
	
	if (!(parse_pip = (t_pip *)malloc(sizeof(*parse_pip))))
		return (NULL);
	parse_pip->redir_output = ft_redir_strchr(str, '>');
	parse_pip->redir_input = ft_redir_strchr(str, '<');
    parse_pip->nb_cmd = i;
	tmp_all = ft_split(str, ' ');
	if (parse_pip->redir_input > 0 && parse_pip->redir_output <= 0)
	{
		parse_pip->file_in = malloc(sizeof(char *) * (parse_pip->redir_input + 1));
		parse_pip = initializing_redin(parse_pip, tmp_all);
		parse_pip->file_out = NULL;
	}
	else if (parse_pip->redir_output > 0 && parse_pip->redir_input <= 0)
	{
		parse_pip->file_out = malloc(sizeof(char *) * (parse_pip->redir_output + 1));
		parse_pip->file_in = NULL;
		parse_pip = initializing_redout(parse_pip, tmp_all);
	}
	else if (parse_pip->redir_output > 0 && parse_pip->redir_input > 0)
	{
		parse_pip->file_out = malloc(sizeof(char *) * (parse_pip->redir_output + 1));
		parse_pip->file_in = malloc(sizeof(char *) * (parse_pip->redir_input + 1));
		parse_pip = initializing_redin(parse_pip, tmp_all);
		parse_pip = initializing_redout(parse_pip, tmp_all);
	}
	else
	{
		parse_pip->cmd = ft_split(str,' ');
		parse_pip->file_out = NULL;
		parse_pip->file_in = NULL;
	}
	//printf("cmd = %s\n", str);
	parse_pip->path = path(parse_pip->cmd[0]);
	parse_pip->next = NULL;
	return (parse_pip);
}

int	where_redir(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		i++;
		if (ft_strchr(str[i], '>') > 0)
			return i;
	} 
	return 0;
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
    //new->path = path(new->cmd[0]);
    new->nb_cmd = i;
	new->next = parse_pip;
	new->redir_output = ft_redir_strchr(str, '>');
	new->redir_input = ft_redir_strchr(str, '<');
	tmp_all = ft_split(str,' ');
	// while(tmp_all[dest])
    // {
    //     printf("dest = %s\n", tmp_all[dest]);
    //     dest++;
    // }
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
	// if (new->redir_input > 0)
	// {
	// 	new = initializing_redin(new, tmp_all);
	// }
	// else
	// {
	// 	new->cmd = ft_split(str,' ');
	// 	new->file_in = NULL;
	// }
	//printf("| parse_pip->file_in              : %s            \n", parse_pip->file_in[0]);
	new->path = path(new->cmd[0]);
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


// int	main(int argc, char **argv, char **env)
// {
// 	t_pip	*data;
// 	int i = 4;
// 	char *cmd1 = "ls >outfile1 -l";
// 	char *cmd2 = "wc <outfile2 >outfoul -l ";
// 	int fdout = 1;
// 	int output;

	
// 	data = ft_lstnew_pip(cmd2, i );
// 	data = fill_parse_pipe(data, "grep ><outfile3 x >outfile4 ", i );
// 	data = fill_parse_pipe(data, "cat <outfile5 pipex.c ", i );
// 	data = fill_parse_pipe(data, cmd1, i );
// 	print_pipe(data);
// 	return (0);
// }

void    parsing_pipes(t_comm comm)
{
    t_pip *parse_pip;
    int i;

    i = 0;
    while (comm.cmd[i])
    { 
      printf("cmd = %s\n", comm.cmd[i]);
         i++;

    }i--;
    parse_pip = ft_lstnew_pip(comm.cmd[i], i + 1);
    while(i-- > 0)
        parse_pip = fill_parse_pipe(parse_pip, comm.cmd[i], i + 1);
    //print_pipe(parse_pip);
    //pipex(parse_pip);
}