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
      printf("| comm.cmd_sep        : %s            \n", comm.cmd[a]);
      a++;
    }
    a=0;
    if (comm.redir)
    {
      while (comm.redir[a])
        {
            printf("| comm.redir          : %s            \n", comm.redir[a]);
            a++;
        }
    }
    // printf("| comm.nb_pipe        : %d            \n", comm.nb_pipe);
    // printf("| comm.redir_input    : %d            \n", comm.redir_input);
    // printf("| comm.redir_output   : %d            \n", comm.redir_output);
    // printf("| comm.single_quote   : %d            \n", comm.single_quote);
    // printf("| comm.double_quote   : %d            \n", comm.double_quote);
    // printf("| comm.error_parse    : %d            \n", comm.error_parse_red);
    // printf("| comm.redir_output_A : %d            \n", comm.redir_output_A);
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
int r_and_w_redirection(t_comm comm, t_list **a_list, t_list **b_list, char *str)
{
  int k;
  int status;
  k = fork();
  if (k == 0)
  {
    if (verif_the_builtin(comm.cmd))
    {
      dup2(comm.write_file,STDOUT);
      dup2(comm.read_file, STDIN);
      exec_cmd(str, comm);
    }
    else
    {
      dup2(comm.write_file,STDOUT);
      dup2(comm.read_file, STDIN);
      builtin(comm, a_list, b_list);
    }
    exit(0);
  }
  else
  {
    waitpid(k, &status, 0);
    k = WEXITSTATUS(status);
  }
  return k;
}

int r_redirection(t_comm comm, t_list **a_list, t_list **b_list, char *str)
{
  int k;
  int status;
  k = fork();
  if (k == 0)
  {
    if (verif_the_builtin(comm.cmd))
    {
    dup2(comm.read_file, STDIN);
    exec_cmd(str, comm);
    }
    else
    {
    dup2(comm.read_file, STDIN);
    builtin(comm, a_list, b_list);
    }
    exit(0);
  }
  else
  {
    waitpid(k, &status, 0);
    k = WEXITSTATUS(status);
  }
  return k;
}

int w_redirection(t_comm comm, t_list **a_list, t_list **b_list, char *str)
{
  int k;
  int status;
  k = fork();
  if (k == 0)
  {
    if (verif_the_builtin(comm.cmd))
    {
      dup2(comm.write_file,STDOUT);
      exec_cmd(str, comm);
    }
    else
    {
      dup2(comm.write_file, STDOUT);
      builtin(comm, a_list, b_list);
    }
    exit(0);
  }
  else
  {
    waitpid(k, &status, 0);
    k = WEXITSTATUS(status);
  }
  return k;
}

int red_uniq_comm(t_comm comm, char *str, t_list **a_list, t_list **b_list)
{
  comm.read_file = -3;
  comm.write_file = -3;
  int k;
  int retnd;
  int i = 0;
  int to_read = -1;
  int to_write = -1;
  printf("oui\n");
  while (comm.redir[i])
  {
    if (comm.redir[i] && ft_strchr(comm.redir[i], '>') == 1)
    {
       retnd = open_file2(comm.redir[i]);
       close(retnd);
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
    comm.read_file = open_file(comm.redir[to_read]);
  if(to_write >= 0)
    comm.write_file = open_file2(comm.redir[to_write]);
  if(to_read >= 0 && to_write >= 0)
    k = r_and_w_redirection(comm, a_list, b_list, str);
  if(to_read < 0 && to_write >= 0)
     k = w_redirection(comm, a_list, b_list, str);
  if(to_read >= 0 && to_write < 0)
    k = r_redirection(comm, a_list, b_list, str);
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
    //printf("comm = %s\n", comm.cmd[0]);
    if (comm.error_parse_red == 1)
    {
      printf("bash: syntax error near unexpected token\n");
      return 1;
    }
    path = ft_split(getenv2("PATH", a_list), ':');
    if (if_builtin(comm.cmd) == 0 && !comm.redir[0])
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
    if (access(str, F_OK) != 0 && !comm.redir[0])
		{
      printf("%s: command not found\n", comm.cmd[0]);
			return (127);
		}
    //printf("found with path command = %s\n", str);
    if (comm.redir[0])
    {
      printf("continue the parse\n");
      k = red_uniq_comm(comm, str, a_list, b_list);
      return (k);
    }
    else
    { 
      k = fork();
      if (k == 0)
      {
        exec_cmd(str, comm);
        exit(0);
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
    //print_comm(comm);
    // if (comm.nb_pipe > 0)
    //   parsing_pipes(comm);
    // else
      return(uniq_cmd(comm, a_list, b_list));
    // return (0);
}

t_comm  ft_double_left_red(t_comm comm)
{
  int i = 0;
  int count = 0;
  int count_temp = 2;
  int temp_index = 0;
  comm.redir_temp = malloc(sizeof(char *) * 150);
  while (comm.redir[i])
  {
    if(comm.redir[i][0] && comm.redir[i][1] && 
      (comm.redir[i][0] == '<' && comm.redir[i][1] == '<'))
    {
      comm.redir_temp[count] = malloc(sizeof(char) * 150);
      if (comm.redir[i][count_temp])
      {
        while(comm.redir[i][count_temp] != '\0')
        {
          comm.redir_temp[count][temp_index] = comm.redir[i][count_temp];
          temp_index++;
          count_temp++;  
        }
        comm.redir_temp[count][temp_index] = '\0';
        count++;
        count_temp = 2 ;
        temp_index = 0;
      } 
    }
    i++;
  }
  comm.redir_temp[count] = NULL;
  return comm;
}

int    parcing(char *all_cmd, t_comm comm, t_list **a_list, t_list **b_list)
{
    char **str;
    char *cmd_new;
    int i;
    cmd_new = malloc(sizeof(char) * 100);
    cmd_new = split_glitch(all_cmd);
    printf("after glitch = %s\n", cmd_new);
    str = ft_split(cmd_new, ' ');
    cmd_new = parse_quotes(str, a_list, comm);
    printf("after quote parse  = %s\n", cmd_new);
    comm = fill_comm(comm, cmd_new);
    if (ft_error_parse_red(comm.redir) == 0)
    {
      printf("Minishell: syntax error near unexpected token\n");
      return -1;
    }
    comm = ft_double_left_red(comm);
    print_comm(comm);
    // if (all_cmd && ft_strchr(all_cmd, '|') != 0)
    // {  
    //   comm.cmd = ft_split(all_cmd, '|');
    //   return (redir_comm(comm, a_list, b_list));
    // }
    // str = ft_split(all_cmd, ' ');
    // cmd_new = parse_quotes(str, a_list, comm);
    // if(all_cmd && ft_strchr(all_cmd, '|') == 0)
    //    comm = ft_redir_single(cmd_new);
    // comm = fill_comm(comm, all_cmd);
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
				retval = parcing(line, comm, &a_list, &b_list);
			}
			free(line);
		}
		return 0;
}