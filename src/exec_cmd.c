/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:05:34 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/10 18:37:40 by glaverdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exec_cmd(char *s, t_comm comm)
{
	execve(s, comm.cmd, NULL);
}

int	cut_cd(char **cmd, int i, char *str)
{
	char	*s;

	s = malloc(100);
	if (!s)
		return (-1);
	str = getenv("HOME");
	if (!str)
		return (-1);
	i = 1;
	while (cmd[1][i])
	{
		s[i - 1] = cmd[1][i];
		i++;
	}
	s[i - 1] = '\0';
	str = ft_strjoin(str, s);
	i = chdir(str);
	if (i == -1)
	{
		str = strerror(errno);
		printf("cd: %s: %s\n", cmd[1], str);
	}
	free(s);
	return (i);
}

int	pwd_shortcut_cd(void)
{
	build_pwd();
	return (0);
}

int	build_cd(char **cmd)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	if (!cmd[1] || (cmd[1][0] == '~' && cmd[1][1] == '\0'))
	{
		str = getenv("HOME");
		if (!str)
			return (-1);
		i = chdir(str);
	}
	else if (cmd[1][0] == '-' && cmd[1][1] == '\0')
		return (pwd_shortcut_cd());
	else if (cmd[1][0] == '~' && cmd[1][1] == '/')
		return (cut_cd(cmd, i, str));
	else
		i = chdir(cmd[1]);
	if (i == -1)
	{
		str = strerror(errno);
		printf("cd: %s: %s\n", cmd[1], str);
	}
	return (i);
}

int	build_export(char **cmd, t_list **a_list, t_list **b_list)
{
	int			i;

	i = 1;
	if (check_sorted(b_list))
	{
		sort_env(b_list);
	}
	while (cmd[i])
	{
		already_in(a_list, cmd[i], 0);
		already_in(b_list, cmd[i], 1);
		add_line(b_list, cmd, i);
		add_line2(a_list, cmd, i);
		i++;
	}
	if (!cmd[1])
		print_env(b_list);
	return (0);
}
