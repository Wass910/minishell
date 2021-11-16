#include "minishell.h"

void	print_comm(t_comm comm)
{
  int		i;
  int a = 0;

  	printf("-----------------------------------\n");
  	while (comm.cmd[a] != NULL)
    {
      printf("| comm.cmd_sep       : %s            \n", comm.cmd[a]);
      a++;
    }
    printf("| comm.nb_pipe       : %d            \n", comm.nb_pipe);
    printf("| comm.redir_input   : %d            \n", comm.redir_input);
    printf("| comm.redir_output  : %d            \n", comm.redir_output);
    printf("| comm.single_quote  : %d            \n", comm.single_quote);
    printf("| comm.double_quote  : %d            \n", comm.double_quote);
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

int uniq_cmd(t_comm comm, t_list **a_list, t_list **b_list)
{
    char **path;
    int k;
    char *str;

    k = 0;
    path = ft_split(getenv("PATH"), ':');
    //print_comm(&comm);
    if (if_builtin(comm.cmd) == 0)
    {
      printf("builtin to do.\n");
      return (builtin(comm, a_list, b_list));
    }
    else
      printf("continue the parse\n");
    if(access(comm.cmd[0], F_OK) == 0)
      printf("command found whithout path\n");
    while (path[k])
    {
      str = ft_strcat_cmd(path[k], comm.cmd[0]);
      if (access(str, F_OK) == 0)
        k = 0;
      if (access(str, F_OK) == 0)
        break;
      free(str);
      k++;
    }
    printf("found with path command = %s\n", str);
    free_str(path);
    k = fork();
    if (k == 0)
      exec_cmd(str, comm);
    return (0);
}

int  redir_comm(t_comm comm, t_list **a_list, t_list **b_list)
{
    if (comm.nb_pipe > 0)
      parsing_pipes(comm);
    else
      return(uniq_cmd(comm, a_list, b_list));
    return (0);
}

void    parcing(char *all_cmd, t_comm comm, t_list **a_list, t_list **b_list)
{
    //char  *all_cmd;
    //char **bg;
    int i = 1;
    
    // all_cmd = NULL;
    // while (str[i])
    // {
    //     all_cmd = ft_strcat(all_cmd, str[i]);
    //     i++;
    // }
    if (ft_strchr(all_cmd, '|') != 0)
      comm.cmd = ft_split(all_cmd, '|');
    else
      comm.cmd = ft_split(all_cmd, ' ');
    comm = fill_comm(comm, all_cmd);
    //print_comm(comm);
    redir_comm(comm, a_list, b_list);
}

void  prompt(void)
{
    write(1, "$>", ft_strlen("$>"));
}

int main(int argc, char **argv, char **envp)
{
    t_comm  comm;
    t_list *a_list;
    t_list *b_list;
    char *line;

    make_list(&a_list, envp);
    make_list(&b_list, envp);
    while (1)
    {
      line = readline(argv[1]);
      parcing(line, comm, &a_list, &b_list);
      free(line);
    }
    //parcing(argv, comm);
    //variable = readline(NULL);
    // variable = getenv(argv[1]);
    // variable = ft_strcat(variable, "/salut");
    return 0;
}