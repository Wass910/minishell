/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:52:19 by idhiba            #+#    #+#             */
/*   Updated: 2021/11/18 11:10:52 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	pipex(t_pip *data)
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
	}
}

// void	parsing_pipes()
// {
	
// }
// int	main(int argc, char **argv, char **env)
// {
// 	t_pip	*data;
// 	int i = 4;
// 	char *cmd1 = "ls >outfile1 -l";
// 	char *cmd2 = "wc <outfile2 >outfoul -l ";
// 	int fdout = 1;
// 	int output;

	
// 	data = ft_lstnew_pip(cmd2, i );
// 	data = fill_parse_pipe(data, "grep ><outfile3 x >outfile4 ", i );
// 	data = fill_parse_pipe(data, "cat <outfile5 pipex.c ", i );
// 	data = fill_parse_pipe(data, cmd1, i );
// 	print_pipe(data);
// 	return (0);
// }
