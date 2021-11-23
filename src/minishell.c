#include "../inc/minishell.h"

void  prompt(void)
{
    write(1, "$>", ft_strlen("$>"));
}

int	open_file(char *filename)
{
  char *str;
  int i;
  filename++;
  filename++;
  i = open(filename, O_RDONLY);
	if (i == -1)
	{
		str = strerror(errno);
    printf("%s: %s\n", filename, str);
		return (-1);
	}
  return (i);
}

void	print_comm(t_comm comm)
{
  int a = 0;

  	printf("-----------------------------------\n");
  	while (comm.cmd[a] != NULL)
    {
      printf("| comm.cmd_sep       : %s            \n", comm.cmd[a]);
      a++;
    }
    a=0;
    if (comm.redir)
    {
      while (comm.redir[a])
        {
            printf("| comm.redir         : %s            \n", comm.redir[a]);
            a++;
        }
    }
    printf("| comm.nb_pipe       : %d            \n", comm.nb_pipe);
    printf("| comm.redir_input   : %d            \n", comm.redir_input);
    printf("| comm.redir_output  : %d            \n", comm.redir_output);
    printf("| comm.single_quote  : %d            \n", comm.single_quote);
    printf("| comm.double_quote  : %d            \n", comm.double_quote);
    printf("| comm.error_parse   : %d            \n", comm.error_parse_red);
  	printf("-----------------------------------\n");
}

// void	good_one_cmd(t_comm comm)
// {
// 	t_data	data;

// 	data = uniq_path(data, comm);
// 	//ft_cant_open(data);
// 	// dup2(data.read_file, STDIN);
// 	// dup2(data.write_file, STDOUT);
// 	create_process(data, comm);
// 	free(data.path1);
// }

int red_uniq_comm(t_comm comm, char *str)
{
  int read_file = -3;
  int write_file = -3;
  int k;
  int retnd;
  int status;
  int i = 0;
  int to_read = -1;
  int to_write = -1;
  while (comm.redir[i])
  {
    if (comm.redir[i] && ft_strchr(comm.redir[i], '>') > 0)
    {
       retnd = open_file2(comm.redir[i]);
      if (retnd == -1)
        return (retnd);
      to_write = i;
    }
    if (comm.redir[i] && ft_strchr(comm.redir[i], '<') > 0)
    {
      retnd = open_file(comm.redir[i]);
      if (retnd == -1)
        return (retnd);
      to_read = i;

    }
    i++;
  }
  if(to_read >= 0)
    read_file = open_file(comm.redir[to_read]);
  if(to_write >= 0)
    write_file = open_file2(comm.redir[to_write]);
  if(to_read >= 0 && to_write >= 0)
  {
    k = fork();
      if (k == 0)
      {
        dup2(write_file,STDOUT);
        dup2(read_file, STDIN);
        exec_cmd(str, comm);
        return (0);
      }
      else
      {
        waitpid(k, &status, 0);
        k = WEXITSTATUS(status);
      }
  }
  if(to_read < 0 && to_write >= 0)
  {
    k = fork();
      if (k == 0)
      {
        dup2(write_file,STDOUT);
        exec_cmd(str, comm);
        return (0);
      }
      else
      {
        waitpid(k, &status, 0);
        k = WEXITSTATUS(status);
      }
  }
  if(to_read >= 0 && to_write < 0)
  {
    k = fork();
      if (k == 0)
      {
        dup2(read_file, STDIN);
        exec_cmd(str, comm);
        return (0);
      }
      else
      {
        waitpid(k, &status, 0);
        k = WEXITSTATUS(status);
      }
  }
  return k;
}

int uniq_cmd(t_comm comm, t_list **a_list, t_list **b_list)
{
    char **path;
    int k;
    char *str;
    int i = 0;
    int status;
    char *tmp;
    int write_file ;
    k = 0;
    if (comm.error_parse_red == 1)
    {
      printf("bash: syntax error near unexpected token\n");
      return 1;
    }
    path = ft_split(getenv2("PATH", a_list), ':');
    if (if_builtin(comm.cmd) == 0)
    {
      //printf("builtin to do.\n");
      comm.retclone = retval;
      k = builtin(comm, a_list, b_list);
      return (k);
    }
    //else
      //printf("continue the parse\n");
    //if(access(comm.cmd[0], F_OK) == 0)
      //printf("command found whithout path\n");
    if (path)
    {
      while (path[k])
      {
        str = ft_strcat_cmd(path[k], comm.cmd[0]);
        if (access(str, F_OK) == 0)
          k = 0;
        if (access(str, F_OK) == 0)
          break;
        k++;
      }
    }
    else
    {
      free(path);
      //printf("%s: No such file or directory\n", comm.cmd[0]);
      return (127);
    }
    if (access(str, F_OK) != 0)
		{
      //printf("%s: command not found\n", comm.cmd[0]);
			return (127);
		}
    //printf("found with path command = %s\n", str);
    if (comm.redir)
    {
      k = red_uniq_comm(comm, str);
    }
    else
    { 
      k = fork();
      if (k == 0)
      {
        exec_cmd(str, comm);
        return (0);
      }
      else
      {
        waitpid(k, &status, 0);
        k = WEXITSTATUS(status);
      }
    }
    free(path);
    return (k);
}

int  redir_comm(t_comm comm, t_list **a_list, t_list **b_list)
{
  print_comm(comm);
    if (comm.nb_pipe > 0)
      parsing_pipes(comm);
    else
      return(uniq_cmd(comm, a_list, b_list));
    return (0);
}

int    parcing(char *all_cmd, t_comm comm, t_list **a_list, t_list **b_list)
{
  int i;

  i = 0;
  if (!all_cmd)
    return 1;
    if (all_cmd && ft_strchr(all_cmd, '|') != 0)
      comm.cmd = ft_split(all_cmd, '|');
    else if(all_cmd && ft_strchr(all_cmd, '|') == 0)
      comm = ft_redir_single(all_cmd, i );
    comm = fill_comm(comm, all_cmd);
    // while (comm.cmd[i])
    // {
    //   comm.cmd[i] = parse_quotes(comm.cmd[i], a_list);
    //   i++;
    // }
    return (redir_comm(comm, a_list, b_list));
}

static void    handle_sigusr1(int s, siginfo_t *siginfo, void *context)
{
	if (s == 2)
		printf("\n$> ");
	if (s==3)
		return;
	if (s==1)
		return;
}

int main(int argc, char **argv, char **envp)
{
		t_comm  comm;
		t_list *a_list;
		t_list *b_list;
		char *line;
		struct sigaction sa;
		(void)argc;

		sa.sa_sigaction = handle_sigusr1;
		sa.sa_flags = SA_SIGINFO;
		comm.env = NULL;
		make_list(&a_list, envp);
		make_list(&b_list, envp);
		sigaction(SIGINT, &sa, NULL);
			sigaction(SIGQUIT, &sa, NULL);
			sigaction(SIGHUP, &sa, NULL);
			kill(SIGINT, 0);
			kill(SIGQUIT, 0);
			kill(SIGHUP, 0);
		while (1)
		{
			line = readline("$> ");
			
			if (line[0])
			{
				add_history(line);
				parcing(line, comm, &a_list, &b_list);
			}
			free(line);
		}
		return 0;
}