/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:52:08 by idhiba            #+#    #+#             */
/*   Updated: 2021/11/30 16:20:42 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	char	**good_path;
	int		i;
	char	*path_to_go;

	if (command == NULL)
		return (NULL);
	good_path = ft_split(getenv2("PATH", a_list), ':');
	i = what_path(good_path, command);
	if (i == -1)
	{
		free_str(good_path);
		return (NULL);
	}
	path_to_go = ft_strcat_w(good_path[i], command);
	free_str(good_path);
	return (path_to_go);
}
