#include "minishell.h"

void	print_comm(t_comm *comm)
{
  int		i;
  int a = 0;

  	printf("-----------------------------------\n");
  	while (comm->cmd[a])
    {
      printf("| comm->cmd_sep      : %s            \n", comm->cmd[a]);
      a++;
    }
    printf("| comm->nb_pipe      : %d            \n", comm->nb_pipe);
    printf("| comm->redir_input  : %d            \n", comm->redir_input);
    printf("| comm->redir_output : %d            \n", comm->redir_output);
  	printf("-----------------------------------\n");

}

void    parcing(char **str, t_comm comm)
{
    char  *all_cmd;
    char **bg;
    int i = 1;
    
    all_cmd = NULL;
    while (str[i])
    {
        all_cmd = ft_strcat(all_cmd, str[i]);
        i++;
    }
    if (ft_strchr(all_cmd, '|') != 0)
      comm.cmd = ft_split(all_cmd, '|');
    else
      comm.cmd = ft_split(all_cmd, ' ');
    comm = fill_comm(comm, all_cmd);
    print_comm(&comm);
}

int main(int argc, char **argv)
{
    t_comm  comm;
    char *variable;

    parcing(argv, comm);
    // variable = getenv(argv[1]);
    // variable = ft_strcat(variable, "/salut");
    return 0;
}