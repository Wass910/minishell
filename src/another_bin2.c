/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   another_bin2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:07:07 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/09 17:46:56 by glaverdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	replace_n_free(t_list *del, char *s, char *str, t_list *temp)
{
	del = temp->next;
	temp->next = temp->next->next;
	if (del->content)
		free(del->content);
	free(del);
	free(str);
	free(s);
	return ;
}

void	replace_n_free2(t_list *del, char *s, char *str, t_list *temp)
{
	del = temp->next;
	temp->next = temp->next->next;
	if (del->content)
		free(del->content);
	free(del);
	free(str);
	free(s);
	return ;
}

void	replace_n_free3(t_list *temp, char *s, char *str, t_list **a_list)
{
	temp = (*a_list);
	(*a_list) = (*a_list)->next;
	if (temp->content)
		free(temp->content);
	free(temp);
	free(s);
	free(str);
	return ;
}

int	ft_count_str(char *s1, char *s2)
{
	int	i;
	int	e;

	i = 0;
	e = 0;
	while (s1 != NULL && s1[i] != '\0')
		i++;
	while (s2 && s2[e] != '\0')
	{
		e++;
		i++;
	}
	i = i + 2;
	return (i);
}


// #include "../inc/minishell.h"

// void	cat_while(t_cat *scat, char *src)
// {
// 	scat->tmp[scat->i] = src[scat->j];
// 	scat->i++;
// 	scat->j++;
// }

// void	ctrld_fill(t_list **a_list, t_list **b_list)
// {
// 	free_list(a_list);
// 	free_list(b_list);
// 	printf("exit\n");
// 	exit(0);
// }

// void	inthandler(int sig)
// {
// 	if (sig == 2)
// 	{
// 		rl_replace_line("", 0);
// 		printf("\n");
// 		rl_on_new_line();
// 		rl_redisplay();
// 		if (g_line.str && (((ft_strncmp(g_line.str, "wc", 2) == 0) && (ft_strlen(g_line.str) == 2)) || ((ft_strncmp(g_line.str, "cat", 3) == 0) && (ft_strlen(g_line.str) == 3)) || ((ft_strncmp(g_line.str, "grep", 4) == 0) && (ft_strlen(g_line.str) == 4))) && g_line.tour > 0)
// 			printf("$> ");
// 		g_line.retval = 130;
// 	}
// }

// char	*ctrl_c_verif(char *line)
// {
// 	if (line && g_line.str && ((ft_strncmp(g_line.str, "wc", 2) == 0
// 				&& ft_strlen(g_line.str) == 2)
// 			|| (ft_strncmp(g_line.str, "cat", 3) == 0
// 				&& ft_strlen(g_line.str) == 3)
// 			|| (ft_strncmp(g_line.str, "grep", 4) == 0)
// 			&& ft_strlen(g_line.str) != 4))
// 	{
// 		g_line.tour++;
// 		rl_replace_line("", 0);
// 		line = readline("");
// 		g_line.str[1] = '\0';
// 	}
// 	else
// 	{	
// 		line = readline("$> ");
// 		g_line.tour = 0;
// 	}
// 	return (line);
// }

// void	main_bin(char *line, t_list **a_list, t_list **b_list)
// {
// 	line = ctrl_c_verif(line);
// 	if (g_line.str)
// 		free(g_line.str);
// 	if (line)
// 		g_line.str = ft_strdup(line);
// 	if (line == NULL)
// 		ctrld_fill(a_list, b_list);
// 	if (line[0])
// 	{
// 		add_history(line);
// 		if (!only_space(line) && !unclosed_quotes2(line))
// 			parcing(line, a_list, b_list);
// 	}
// 	if (line)
// 		free(line);
// }
