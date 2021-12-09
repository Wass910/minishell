/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   another_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:01:09 by idhiba            #+#    #+#             */
/*   Updated: 2021/12/08 16:36:50 by user42           ###   ########.fr       */
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

int	check_argc(int argc)
{
	if (argc != 1)
	{
		printf("Too much arguments, usage : './minishell'.\n");
		return (1);
	}
	return (0);
}

void	main_bin(char *line, t_list **a_list, t_list **b_list)
{
	if (g_retval != 200)
	{
		rl_replace_line("", 0);
		line = readline("$> ");
	}
	if (g_retval == 200)
	{
		rl_replace_line("", 0);
		line = readline("");
		g_retval = 1;
	}
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
