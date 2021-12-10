/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:52:19 by idhiba            #+#    #+#             */
/*   Updated: 2021/12/10 16:04:51 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	pipex_read(t_pipe *comm_pip, int i, t_list **a_list, t_list **b_list)
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
		if (i == 1)
			dup2(pipefd[0], 0);
		else
			dup2(1, 0);
		waitpid(pid1, &status, 0);
		g_line.retval = WEXITSTATUS(status);
	}
	else
	{
		dup_read_norme(i, pipefd);
		dup_read(comm_pip, a_list, b_list);
	}
}

void	pipex(t_pipe *comm_pip, int i, t_list **a_list, t_list **b_list)
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
		if (i == 0)
			dup2(1, 0);
		waitpid(pid1, &status, 0);
		g_line.retval = WEXITSTATUS(status);
	}
	else
	{
		dup_read_norme(i, pipefd);
		dup_read(comm_pip, a_list, b_list);
	}
}

void	pipex_write_read(t_pipe *comm_pip,
	int i, t_list **a_list, t_list **b_list)
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
		if (i == 1)
			dup2(pipefd[0], 0);
		else
			dup2(1, 0);
		waitpid(pid1, &status, 0);
		g_line.retval = WEXITSTATUS(status);
	}
	else
		dup_write(comm_pip, a_list, b_list, pipefd);
}

void	pipex_write(t_pipe *comm_pip, int i, t_list **a_list, t_list **b_list)
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
		if (i == 1)
			dup2(pipefd[0], 0);
		else
			dup2(1, 0);
		waitpid(pid1, &status, 0);
		g_line.retval = WEXITSTATUS(status);
	}
	else
		dup_write(comm_pip, a_list, b_list, pipefd);
}
