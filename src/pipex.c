/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:52:19 by idhiba            #+#    #+#             */
/*   Updated: 2021/11/30 16:45:53 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	dup_read_norme(int i, int *pipefd)
{
	close(pipefd[0]);
	if (i == 1)
		dup2(pipefd[1], 1);
}

void	dup_read(t_pipe *comm_pip, t_list **a_list,
	t_list **b_list)
{
	if (verif_the_builtin(comm_pip->cmd) == 0)
		builtin(comm_pip->cmd, a_list, b_list);
	else
		execve(comm_pip->path, comm_pip->cmd, NULL);
	exit (0);
}

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
		g_retval = WEXITSTATUS(status);
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
		g_retval = WEXITSTATUS(status);
	}
	else
	{
		dup_read_norme(i, pipefd);
		dup_read(comm_pip, a_list, b_list);
	}
}

void	dup_write(t_pipe *comm_pip, t_list **a_list,
	t_list **b_list, int *pipefd)
{
	close(pipefd[0]);
	dup2(comm_pip->write_file, 1);
	if (verif_the_builtin(comm_pip->cmd) == 0)
		builtin(comm_pip->cmd, a_list, b_list);
	else
		execve(comm_pip->path, comm_pip->cmd, NULL);
	exit (0);
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
		g_retval = WEXITSTATUS(status);
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
		g_retval = WEXITSTATUS(status);
	}
	else
		dup_write(comm_pip, a_list, b_list, pipefd);
}
