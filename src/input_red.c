#include "../inc/minishell.h"

t_lred	*dred_setup(t_lred *dred, int i)
{
	if (i == 1)
	{	
		dred->i = 0;
		dred->count = 0;
		dred->count_temp = 2;
		dred->temp_index = 0;
	}
	else
	{	
		dred->count++;
		dred->count_temp = 2 ;
		dred->temp_index = 0;
	}
	return (dred);
}

t_comm	dleft_loop(t_comm comm, t_lred *dred)
{
	while (comm.redir[dred->i][dred->count_temp] != '\0')
	{
		if (comm.redir[dred->i][dred->count_temp] != 24)
		{
			comm.redir_temp[dred->count][dred->temp_index]
				= comm.redir[dred->i][dred->count_temp];
			dred->temp_index++;
			dred->count_temp++;
		}
		else
			dred->count_temp++;
	}
	return (comm);
}

t_comm	ft_double_left_red(t_comm comm)
{
	t_lred	*dred;

	dred = fill_dred(dred);
	comm.redir_double_input = 0;
	comm.redir_temp = malloc(sizeof(char *) * 150);
	while (comm.redir[dred->i])
	{
		if (comm.redir[dred->i][0] && comm.redir[dred->i][1]
				&& comm.redir[dred->i][2] &&
			(comm.redir[dred->i][0] == '<' && comm.redir[dred->i][1] == '<'
				&& (is_red(comm.redir[dred->i][2]) != 1)))
		{
			comm.redir_temp[dred->count] = malloc(sizeof(char) * 150);
			if (comm.redir[dred->i][dred->count_temp])
			{
				comm = dleft_loop(comm, dred);
				comm.redir_double_input++;
				comm.redir_temp[dred->count][dred->temp_index] = '\0';
				dred = dred_setup(dred, 2);
			}
		}
		dred->i++;
	}
	comm.redir_temp[dred->count] = NULL;
	return (comm);
}

void	ft_redir_temp(char **str, int input)
{
	int		i;
	int		ret;
	char	*line;

	i = 0;
	ret = get_next_line(0, &line);
	while (ret > 0)
	{
		if ((ft_strncmp(line, str[i], ft_strlen(str[i])) == 0)
			&& ft_strlen(line) == ft_strlen(str[i]))
			i++;
		if (i == input)
			return ;
		free(line);
		ret = get_next_line(0, &line);
	}
	return ;
}

char	**double_in(char *all_cmd, t_list **a_list)
{
	char	**str;
	char	*cmd_new;
	t_comm	comm;

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
