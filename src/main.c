/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:01:09 by idhiba            #+#    #+#             */
/*   Updated: 2021/12/10 18:38:24 by glaverdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_line	g_line;

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

int	check_argc(int argc)
{
	if (argc != 1)
	{
		printf("Too much arguments, usage : './minishell'.\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_list				*a_list;
	t_list				*b_list;
	char				*str;
	static int			done = 0;

	str = NULL;
	argv = NULL;
	g_line.retval = 0;
	if (check_argc(argc))
		exit(EXIT_FAILURE);
	make_list(&a_list, envp);
	make_list(&b_list, envp);
	if (!done)
	{
		add_declare(&b_list);
		done = 1;
	}
	signal(SIGQUIT, inthandler);
	signal(SIGINT, inthandler);
	while (1)
		main_bin(str, &a_list, &b_list);
}
