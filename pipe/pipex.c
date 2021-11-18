/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:52:19 by idhiba            #+#    #+#             */
/*   Updated: 2021/11/18 13:52:05 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_redir_strchr(char *s, int c)
{
	int		i;
	int		nb_chr;

	i = 0;
    nb_chr = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c && s[i - 1] && s[i - 1] != c)
			nb_chr++;
		i++;
	}
	return (nb_chr);
}


int	ft_strchr(char *s, int c)
{
	int		i;
	int		nb_chr;

	i = 0;
    nb_chr = 0;
	while (s && s[i] != '\0')
	{
		if (s[i] == c)
			nb_chr++;
		i++;
	}
	return (nb_chr);
}



char	*path(char *command)
{
	char	*path;
	char	**good_path;
	int		i;
	char    *path_to_go;

	//printf("cmd = %s\n", command);
	path = getenv("PATH");
	good_path = ft_split(path, ':');
	i = what_path(good_path, command);
	if (i == -1)
	{
		free_str(good_path);
		write(1, "The path binary don't exist.\n", 29);
		exit(EXIT_FAILURE);
	}
	path_to_go = ft_strcat(good_path[i], command);
	//printf("datapath1 = %s, datapath2 = %s", data.path1, data.path2);
	free_str(good_path);
	return (path_to_go);
}

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

void	pipex(t_pip *data)
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
		execve(data->path, data->cmd, NULL);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_pip	*data;
	int i = 4;
	char *cmd1 = "ls >outfile1 -l";
	char *cmd2 = "wc <outfile2 >outfoul -l ";
	int fdout = 1;
	int output;

	
	data = ft_lstnew_pip(cmd2, i );
	data = fill_parse_pipe(data, "grep ><outfile3 x >outfile4 ", i );
	data = fill_parse_pipe(data, "cat <outfile5 pipex.c ", i );
	data = fill_parse_pipe(data, cmd1, i );
	print_pipe(data);
	return (0);
}
