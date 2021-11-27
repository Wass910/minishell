/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:52:08 by idhiba            #+#    #+#             */
/*   Updated: 2021/11/26 15:54:32 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

int	what_path(char **path, char *cmd)
{
	int		i;
	char	*str;

	i = 0;
	while (path[i])
	{
		str = ft_strcat_w(path[i], cmd);
		if (access(str, F_OK) == 0)
		{
			free(str);
			return (i);
		}
		free(str);
		i++;
	}
	return (-1);
}

char	*get_path(char **env)
{
	char	*path;
	int		i;

	i = 0;
	while (strncmp(env[i], "PATH=", 5) != 0)
		i++;
	path = env[i] + 5;
	return (path);
}


char	*path(char *command, t_list **a_list)
{
	char	*path;
	char	**good_path;
	int		i;
	char    *path_to_go;

	//printf("cmd = %s\n", command);
	good_path = ft_split(getenv2("PATH", a_list), ':');
	i = what_path(good_path, command);
	if (i == -1)
	{
		free_str(good_path);
		//write(1, "The path binary don't exist.\n", 29);
		return NULL;
	}
	path_to_go = ft_strcat_w(good_path[i], command);
	//printf("datapath1 = %s, datapath2 = %s", data.path1, data.path2);
	free_str(good_path);
	return (path_to_go);
}