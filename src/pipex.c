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
t_pipe *fill_redir_attribut(t_pipe *parse_pip, int to_read, int to_write)
{
    if(to_read >= 0)
    {
        parse_pip->file_to_in = ft_strcat_red("", parse_pip->redir[to_read]);
        parse_pip->read_file = open_file(parse_pip->redir[to_read]);
    }
    else
    {
      parse_pip->file_to_out = malloc(50);
        parse_pip->file_to_in = NULL;
    }
    if(to_write >= 0)
    {
        parse_pip->file_to_out= ft_strcat_red("", parse_pip->redir[to_write]);
        parse_pip->write_file = open_file2(parse_pip->redir[to_write]);
    }
    else
    { 
        parse_pip->file_to_out = malloc(50);
        parse_pip->file_to_out = NULL;
    }
    printf("to_read = %d fichier = %s\n", to_read, parse_pip->file_to_in);
    return (parse_pip);
}

t_pipe *open_file_redir(t_pipe *parse_pip)
{
    int retnd;
    int i = 0;
    t_pip *tmp;
    int err;
    int to_read = -1;
      int to_write = -1;
    
    if (parse_pip->redir)
    {
        while (parse_pip->redir[i])
        {
            if (parse_pip->redir[i] && ft_strchr(parse_pip->redir[i], '>') > 0)
            {
                retnd = open_file2(parse_pip->redir[i]);
                if (retnd == -1)
                    parse_pip->not_fil_red = 1;
                if (retnd != -1)
                    to_write = i;
            }
            if (parse_pip->redir[i] && ft_strchr(parse_pip->redir[i], '<') > 0)
            {
                retnd = open_file(parse_pip->redir[i]);
                if (retnd == -1)
                    parse_pip->not_fil_red = 1;
                if (retnd != -1)
                    to_read = i;
            }
            i++;
        }
    }
    parse_pip = fill_redir_attribut(parse_pip, to_read, to_write);
    return parse_pip;
}

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


void	pipex_read(t_pipe *comm_pip, int i)
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
		if (i == 1)
			dup2(pipefd[0], 0);
		else
			dup2(1, 0);
		waitpid(pid1, NULL, 0);	
	}
	else
	{
    close(pipefd[0]);
		if (i==1)
			  dup2(pipefd[1], 1);
		execve(comm_pip->path, comm_pip->cmd, NULL);
		exit (0);
	}
}

void	pipex(t_pipe *comm_pip, int i)
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
		if (i == 1)
			dup2(pipefd[0], 0);
		if(i == 0)
      dup2(1, 0);
		waitpid(pid1, NULL, 0);
	}
	else
	{
    close(pipefd[0]);
		if (i==1)
			  dup2(pipefd[1], 1);
		execve(comm_pip->path, comm_pip->cmd, NULL);
		exit (0);
	}
}

void	pipex_write_read(t_pipe *comm_pip, int i)
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
		if (i == 1)
			dup2(pipefd[0], 0);
		waitpid(pid1, NULL, 0);	
	}
	else
	{
    close(pipefd[0]);
		dup2(comm_pip->write_file, 1);
		execve(comm_pip->path, comm_pip->cmd, NULL);
		exit (0);
	}
}

void	pipex_write(t_pipe *comm_pip, int i)
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
		if (i == 1)
			dup2(pipefd[0], 0);
		else
			dup2(1, 0);
		waitpid(pid1, NULL, 0);	
	}
	else
	{
    close(pipefd[0]);
		dup2(comm_pip->write_file, 1);
		execve(comm_pip->path, comm_pip->cmd, NULL);
		exit (0);
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
