/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:52:19 by idhiba            #+#    #+#             */
/*   Updated: 2021/11/26 17:23:17 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	open_file2(char *filename)
{
  int i;
  int count = 0;
  char *str;
  while(filename[count] == '>')
  {
    count++;
  }
  if (count == 1)
	  i = open(filename+count, O_RDWR | O_CREAT | S_IWOTH | O_TRUNC, 0664);
  else 
    i = open(filename+count, O_RDWR | O_CREAT | S_IWOTH | O_APPEND, 0664);
  if (i == -1)
  {
    str = strerror(errno);
    printf("%s: %s\n", filename, str);
    return (-1);
  }
  return (i);
}

// int	open_file2(char *filename)
// {
//   filename++;
//   filename++;
// 	if (access(filename, F_OK) == 0)
// 		return (open(filename, O_RDWR));
// 	else
// 		return (open(filename, O_CREAT | S_IWOTH));
// 	return (-1);
// }
void pipex_suits(t_pipe *parse_pip)
{
  int i;
  int pipefd[2];
  
  i = fork();
    if (i)
    {
      dup2(STDIN, pipefd[0]);
      dup2(STDOUT,pipefd[1]);
      waitpid(i, NULL, 0);
    }
    else{
        execve(parse_pip->path, parse_pip->cmd, NULL);
    }
  return ;
}

void	pipex(t_pipe *parse_pip, int nb_cmds)
{
	int pipefd[2];
	pid_t pid1;

    while (nb_cmds > 1)
    {
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
      }
      else
      {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT);
        execve(parse_pip->path, parse_pip->cmd, NULL);
        return ;
      }
      parse_pip = parse_pip->next;
      nb_cmds--;
    }
    pipex_suits(parse_pip);
    return; 
}

void	pipex_for_one(t_pip *parse_pip)
{
	int pipefd[2];
	pid_t pid1;
	int i;

      if (pipe(parse_pip->pipefd) == -1)
        exit(EXIT_FAILURE);
      pid1 = fork();
      if (pid1 == -1)
        exit(EXIT_FAILURE);
      if (pid1)
      {
        waitpid(pid1, NULL, 0);	
      }
      else
      {
        execve(parse_pip->path, parse_pip->cmd, NULL);
        kill(SIGHUP, 0);
		    exit(0);
      }

}
