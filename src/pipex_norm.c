/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_norm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:55:45 by idhiba            #+#    #+#             */
/*   Updated: 2021/12/07 13:58:02 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	pipex_for_one(char *path, char **cmd)
{
	int		pipefd[2];
	pid_t	pid1;

	if (pipe(pipefd) == -1)
		exit(EXIT_FAILURE);
	pid1 = fork();
	if (pid1 == -1)
		exit(EXIT_FAILURE);
	if (pid1)
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		waitpid(pid1, NULL, 0);
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		execve(path, cmd, NULL);
		exit (0);
	}
}

void	pipex_last(t_pipe *comm_pip, int i)
{
	int		pipefd[2];
	pid_t	pid1;
	int		status;

	dup2(pipefd[1], 1);
	dup2(pipefd[0], 0);
	if (i == 0)
		dup2(1, 0);
}
