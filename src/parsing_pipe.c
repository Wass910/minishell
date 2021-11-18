
#include "../inc/minishell.h"

t_pip	*ft_lstnew_pip(char *str, int i)
{
	t_pip *parse_pip;

	if (!(parse_pip = (t_pip *)malloc(sizeof(*parse_pip))))
		return (NULL);
    if(ft_double_strchr(str, '>') == -1 || ft_double_strchr(str, '<') == -1)
    {
       printf("Invalid redirection.\n");
        exit(EXIT_FAILURE);
    }
    parse_pip->cmd = str;
    parse_pip->redir_input = ft_redir_strchr(str, '<');
    parse_pip->redir_output = ft_redir_strchr(str, '>');
    parse_pip->redir_double_input = ft_double_strchr(str, '<');
    parse_pip->redir_output_A = ft_double_strchr(str, '>');
    parse_pip->single_quote = ft_strchr(str, 39);
  	parse_pip->double_quote = ft_strchr(str, '"');
    parse_pip->nb_cmd = i;
	parse_pip->next = NULL;
	return (parse_pip);
}

t_pip	*fill_parse_pipe(t_pip *parse_pip, char *str, int i)
{
    t_pip	*new;

	new = malloc(sizeof(*new));
	if (new == NULL)
		exit(EXIT_FAILURE);
    new->cmd = str;
    new->redir_input = ft_redir_strchr(str, '<');
    new->redir_output = ft_redir_strchr(str, '>');
    new->single_quote = ft_strchr(str, 39);
  	new->double_quote = ft_strchr(str, '"');
    new->redir_double_input = ft_double_strchr(str, '<');
    new->redir_output_A = ft_double_strchr(str, '>');
    new->nb_cmd = i;
    new->next = parse_pip;
	//printf("c = %s\n", cmd);
  	// comm.nb_pipe = ft_strchr(cmd, '|');
  	// comm.redir_input = ft_strchr(cmd, '<');
  	// comm.redir_output = ft_strchr(cmd, '>');
	// comm.single_quote = ft_strchr(cmd, 39);
  	// comm.double_quote = ft_strchr(cmd, '"');
	return new;
}

void	print_pipe(t_pip *parse_pip)
{
  int		i = 0 ;
    while(parse_pip)
  	{
          printf("-----------------------------------\n");
    printf("| parse_pip->nb_cmd               : %d            \n", parse_pip->nb_cmd);
    printf("| parse_pip->cmd                  : %s            \n", parse_pip->cmd);
    printf("| parse_pip->redir_input          : %d            \n", parse_pip->redir_input);
    printf("| parse_pip->redir_output         : %d            \n", parse_pip->redir_output);
    printf("| parse_pip->redir_double_input   : %d            \n", parse_pip->redir_double_input);
    printf("| parse_pip->redir_output_A       : %d            \n", parse_pip->redir_output_A);
    printf("| parse_pip->single_quote         : %d            \n", parse_pip->single_quote);
    printf("| parse_pip->double_quote         : %d            \n", parse_pip->double_quote);
  	printf("-----------------------------------\n");
    parse_pip = parse_pip->next;
    i++;
    }
}


void    parsing_pipes(t_comm comm)
{
    t_pip *parse_pip;
    int i;

    i = 0;
    while (comm.cmd[i])
        i++;
    i--;
    parse_pip = ft_lstnew_pip(comm.cmd[i], i + 1);
    while(i-- > 0)
        parse_pip = fill_parse_pipe(parse_pip, comm.cmd[i], i + 1);
    print_pipe(parse_pip);
    //pipex(parse_pip);
}