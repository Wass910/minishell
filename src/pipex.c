/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:52:19 by idhiba            #+#    #+#             */
/*   Updated: 2021/11/18 16:40:39 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	pipex(t_pip *data, int i)
{
	int pipefd[2];
	pid_t pid1;

	if (pipe(pipefd) == -1)
		exit(EXIT_FAILURE);
	pid1 = fork();
	if (pid1 == -1)
		exit(EXIT_FAILURE);
	if (pid1)
	{
		close(pipefd[1]);
			dup2(pipefd[0], STDIN);
		waitpid(pid1, NULL, 0);	
		//execve(data->next->path, data->next->cmd, NULL);
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT);
		execve(data->path, data->cmd, NULL);
		return ;
	}
}
