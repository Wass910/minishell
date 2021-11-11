#include "minishell.h"

void	print_comm(t_comm *comm)
{
  int		i;

  i = 0;
  while (comm)
  {
  	printf("-----------------------------------\n");
  	printf("| comm->nb_of_com    : %d                            \n", comm->nb_of_cmd);
  	printf("| comm->cmd_sep      : %s            \n", comm->cmd);
    printf("| comm->nb_pipe      : %d            \n", comm->nb_pipe);
    printf("| comm->redir_input  : %d            \n", comm->redir_input);
    printf("| comm->redir_output : %d            \n", comm->redir_output);
  	printf("-----------------------------------\n");
  	comm = comm->next;
  	i++;
  }
}

void    parcing(char *str, t_comm *comm)
{
    char **cmd;
    int i = 3;

    cmd = ft_split(str, ';');
    i = 0;
    while (cmd[i])
    {
        comm = fill_comm(comm, cmd[i], i);
        i++;
    }
    print_comm(comm);
}

int main(int argc, char **argv)
{
    int i = 0;
    t_comm  *comm;
    char *variable;
    char **cmd;

    comm = NULL;
    parcing(argv[1], comm);
    // variable = getenv(argv[1]);
    // variable = ft_strcat(variable, "/salut");
    return 0;
}