/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:52:19 by idhiba            #+#    #+#             */
/*   Updated: 2021/11/24 01:13:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	open_file2(char *filename)
{
  int i;
  char *str;
  filename++;
  filename++;
	i = open(filename, O_RDWR | O_CREAT | S_IWOTH, 0664);
  if (i == -1)
  {
    str = strerror(errno);
    printf("%s: %s\n", filename, str);
    return (-1);
  }
  return (i);
}


void	pipex(t_pip *parse_pip, int nb_cmds)
{
	int pipefd[2];
	pid_t pid1;
	int i;

    i = 0;
    while (nb_cmds > 0)
    {
      if (pipe(parse_pip->pipefd) == -1)
        exit(EXIT_FAILURE);
      pid1 = fork();
      if (pid1 == -1)
        exit(EXIT_FAILURE);
      if (pid1)
      {
		      close(parse_pip->pipefd[1]);
          dup2(parse_pip->pipefd[0], STDIN);
		  if (nb_cmds == 1)
		  {
			    dup2(STDIN, pipefd[0]);
    	  	dup2(STDOUT,pipefd[1]);
		  }
        waitpid(pid1, NULL, 0);	
      }
      else
      {
        close(parse_pip->pipefd[0]);
        if(nb_cmds != 1 && !parse_pip->file_out)
			    dup2(parse_pip->pipefd[1], STDOUT);
		    if (nb_cmds != 1)
        	execve(parse_pip->path, parse_pip->cmd, NULL);
		    else
			    execve(parse_pip->next->path, parse_pip->next->cmd, NULL);
		    exit(0);
      }
	  nb_cmds--;
	  if (nb_cmds != 1)
		  {
				parse_pip = parse_pip->next;
		  }
    }
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
