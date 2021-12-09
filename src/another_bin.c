/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   another_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:01:09 by idhiba            #+#    #+#             */
/*   Updated: 2021/12/09 22:56:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	cat_while(t_cat *scat, char *src)
{
	scat->tmp[scat->i] = src[scat->j];
	scat->i++;
	scat->j++;
}

void	ctrld_fill(t_list **a_list, t_list **b_list)
{
	free_list(a_list);
	free_list(b_list);
	printf("exit\n");
	exit(0);
}

void	inthandler(int sig)
{
	if (sig == 2)
	{
		g_line.retval = 130;
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
		if (g_line.str && (((ft_strncmp(g_line.str, "wc", 2) == 0)
					&& (ft_strlen(g_line.str) == 2))
				|| ((ft_strncmp(g_line.str, "cat", 3) == 0)
					&& (ft_strlen(g_line.str) == 3))
				|| ((ft_strncmp(g_line.str, "grep", 4) == 0)
					&& (ft_strlen(g_line.str) != 4))|| ((ft_strncmp(g_line.str, "/bin/wc", 7) == 0) && (ft_strlen(g_line.str) == 7)) || ((ft_strncmp(g_line.str, "/bin/cat", 8) == 0)
					&& (ft_strlen(g_line.str) != 8)) || ((ft_strncmp(g_line.str, "/bin/grep", 9) == 0) && (ft_strlen(g_line.str) != 9))) && g_line.tour > 0)
			printf("$> ");
		g_line.tour++;
	}
}

char	*ctrl_c(void)
{
	int i = 0;
	if (g_line.str && (((ft_strncmp(g_line.str, "wc", 2) == 0)
				&& (ft_strlen(g_line.str) == 2))
			|| ((ft_strncmp(g_line.str, "cat", 3) == 0)
				&& (ft_strlen(g_line.str) == 3))
			|| ((ft_strncmp(g_line.str, "grep", 4) == 0) && (ft_strlen(g_line.str) != 4)) || ((ft_strncmp(g_line.str, "/bin/wc", 7) == 0) && (ft_strlen(g_line.str) == 7)) || ((ft_strncmp(g_line.str, "/bin/cat", 8) == 0)
			&& (ft_strlen(g_line.str) != 8)) || ((ft_strncmp(g_line.str, "/bin/grep", 9) == 0) && (ft_strlen(g_line.str) != 9))))
	{
		while (g_line.str[i])
			i++;
		g_line.str[i] = '\0';
		g_line.tour++;
		rl_replace_line("", 0);
		return (readline(""));
	}
	else
	{
		g_line.tour = 0;
		return (readline("$> "));
	}
}

void	main_bin(char *line, t_list **a_list, t_list **b_list)
{
	line = ctrl_c();;
	if (line)
	{
		if (g_line.str)
			free(g_line.str);
		g_line.str = ft_strdup(line);
	}
	if (line == NULL)
		ctrld_fill(a_list, b_list);
	if (line[0])
	{
		add_history(line);
		if (!only_space(line) && !unclosed_quotes2(line))
			parcing(line, a_list, b_list);
		g_line.retval = 0;
	}
	if (line)
		free(line);
}
