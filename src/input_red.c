#include "../inc/minishell.h"

t_comm	ft_double_left_red(t_comm comm)
{
	int	i;
	int	count;
	int	count_temp;
	int	temp_index;

	i = 0;
	count = 0;
	count_temp = 2;
	temp_index = 2;
	comm.redir_double_input = 0;
	comm.redir_temp = malloc(sizeof(char *) * 150);
	while (comm.redir[i])
	{
		if (comm.redir[i][0] && comm.redir[i][1] && comm.redir[i][2] &&
			(comm.redir[i][0] == '<' && comm.redir[i][1] == '<'
				&& (is_red(comm.redir[i][2]) != 1)))
		{
			comm.redir_temp[count] = malloc(sizeof(char) * 150);
			if (comm.redir[i][count_temp])
			{
				while (comm.redir[i][count_temp] != '\0')
				{
					if (comm.redir[i][count_temp] != 24)
					{
						comm.redir_temp[count][temp_index]
							= comm.redir[i][count_temp];
						temp_index++;
						count_temp++;
					}
					else
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
