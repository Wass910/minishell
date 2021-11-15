/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:52:08 by idhiba            #+#    #+#             */
/*   Updated: 2021/11/15 14:36:17 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str(char **str)
{
	int	line;

	line = 0;
	while (str[line])
	{
		free(str[line]);
		line++;
	}
	free(str);
}

t_data	path2(t_data data, char *command)
{
	char	*path;
	char	**good_path;
	int		i;

	data.cmd2 = ft_split(command, ' ');
	path = getenv("PATH");
	good_path = ft_split(path, ':');
	i = what_path(good_path, data.cmd2[0]);
	if (i == -1)
	{
		free_str(good_path);
		free_str(data.cmd2);
		free_str(data.cmd1);
		free(data.path1);
		write(1, "The path binary don't exist.\n", 29);
		exit(EXIT_FAILURE);
	}
	data.path2 = ft_strcat_cmd(good_path[i], data.cmd2[0]);
	free_str(good_path);
	return (data);
}

t_data	uniq_path(t_data data, t_comm comm)
{
	char	*path;
	char	**good_path;
	int		i;

	path = getenv("PATH");
	good_path = ft_split(path, ':');
	i = what_path(good_path, comm.cmd[0]);
	if (i == -1)
	{
		free_str(good_path);
		write(1, "The path binary don't exist.\n", 29);
		exit(EXIT_FAILURE);
	}
	data.path1  = ft_strcat_cmd(good_path[i], comm.cmd[0]);
	free_str(good_path);
	return (data);
}