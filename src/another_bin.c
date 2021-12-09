/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   another_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:01:09 by idhiba            #+#    #+#             */
/*   Updated: 2021/12/09 16:51:33 by glaverdu         ###   ########.fr       */
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
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
		if (g_line.str && ((ft_strncmp(g_line.str, "wc", 2) == 0
					&& ft_strlen(g_line.str) == 2)
				|| (ft_strncmp(g_line.str, "cat", 3) == 0
					&& ft_strlen(g_line.str) == 3)
				|| (ft_strncmp(g_line.str, "grep", 4) == 0)
				&& ft_strlen(g_line.str) == 4) && g_line.tour > 0)
			printf("$> ");
		g_line.retval = 130;
	}
}

char	*ctrl_c_verif(char *line)
{
	if (line && g_line.str && ((ft_strncmp(g_line.str, "wc", 2) == 0
				&& ft_strlen(g_line.str) == 2)
			|| (ft_strncmp(g_line.str, "cat", 3) == 0
				&& ft_strlen(g_line.str) == 3)
			|| (ft_strncmp(g_line.str, "grep", 4) == 0)
			&& ft_strlen(g_line.str) != 4))
	{
		g_line.tour++;
		rl_replace_line("", 0);
		line = readline("");
		g_line.str[1] = '\0';
	}
	else
	{	
		line = readline("$> ");
		g_line.tour = 0;
	}
	return (line);
}

void	main_bin(char *line, t_list **a_list, t_list **b_list)
{
	line = ctrl_c_verif(line);
	if (g_line.str)
		free(g_line.str);
	if (line)
		g_line.str = ft_strdup(line);
	if (line == NULL)
		ctrld_fill(a_list, b_list);
	if (line[0])
	{
		add_history(line);
		if (!only_space(line) && !unclosed_quotes2(line))
			parcing(line, a_list, b_list);
	}
	if (line)
		free(line);
}
