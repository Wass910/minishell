/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_norm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:55:45 by idhiba            #+#    #+#             */
/*   Updated: 2021/12/10 18:05:38 by glaverdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	pipex_for_one(char *path, char **cmd)
{
	int		pipefd[2];
	pid_t	pid1;
	int		status;

	if (pipe(pipefd) == -1)
		exit(EXIT_FAILURE);
	pid1 = fork();
	if (pid1 == -1)
		exit(EXIT_FAILURE);
	if (pid1)
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		waitpid(pid1, &status, 0);
		g_line.retval = WEXITSTATUS(status);
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		execve(path, cmd, NULL);
		exit (0);
	}
}

void	pipex_last(int i)
{
	int		pipefd[2];

	dup2(pipefd[0], 0);
	if (i == 0)
		dup2(1, 0);
}

void	check_gline(void)
{
	if (g_line.retemp == 1)
	{
		g_line.retemp = 0;
		g_line.retval = 130;
	}
}

void	free_both(t_del *del)
{
	free(del->temp2[0]);
	free(del->temp2[1]);
}
