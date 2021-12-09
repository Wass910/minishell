/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:01:09 by idhiba            #+#    #+#             */
/*   Updated: 2021/12/09 09:57:56 by glaverdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_retval = 0;

int	only_space(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] && s[i] != 32 && s[i] != 9)
			return (0);
		i++;
	}
	return (1);
}

int	unclosed_quotes2(char *s)
{
	int	i;
	int	j;
	int	type;

	i = 0;
	j = 0;
	type = 0;
	while (s[i])
	{
		if (s[i] == 34 || s[i] == 39)
		{
			type = s[i];
			i++;
			while (s[i] && s[i] != type)
				i++;
			if (!s[i])
			{
				printf("Unclosed quotes, check your inport before retrying\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

void	inthandler(int sig)
{
	if (sig == 2)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("\0", 0);
		rl_redisplay();
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_list				*a_list;
	t_list				*b_list;
	char				*line;
	int					i;

	argv = NULL;
	if (argc != 1)
	{
		printf("Too much arguments, usage : './minishell'.\n");
		exit(EXIT_FAILURE);
	}
	make_list(&a_list, envp);
	make_list(&b_list, envp);
	signal(SIGQUIT, inthandler);
	signal(SIGINT, inthandler);
	while (1)
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
		{
			free_list(&a_list);
			free_list(&b_list);
			printf("exit\n");
			return (0);
		}
		if (line[0])
		{
			add_history(line);
			if (!only_space(line) && !unclosed_quotes2(line))
				i = parcing(line, &a_list, &b_list);
		}
		if (line)
			free(line);
	}
	return (0);
}
