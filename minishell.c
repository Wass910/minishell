#include "minishell.h"

void	print_comm(t_comm *comm)
{
  int		i;
  int a = 0;

  	printf("-----------------------------------\n");
  	while (comm->cmd[a])
    {
      printf("| comm->cmd_sep       : %s            \n", comm->cmd[a]);
      a++;
    }
    printf("| comm->nb_pipe       : %d            \n", comm->nb_pipe);
    printf("| comm->redir_input   : %d            \n", comm->redir_input);
    printf("| comm->redir_output  : %d            \n", comm->redir_output);
    printf("| comm->single_quote  : %d            \n", comm->single_quote);
    printf("| comm->double_quote  : %d            \n", comm->double_quote);
  	printf("-----------------------------------\n");
}

void	uniq_cmd(t_comm comm)
{
	t_data	data;

	data = uniq_path(data, comm);
	//ft_cant_open(data);
	// dup2(data.read_file, STDIN);
	// dup2(data.write_file, STDOUT);
	create_process(data, comm);
	free(data.path1);
}

void  redir_comm(t_comm comm)
{
    if (comm.nb_pipe > 0)
      pipex(comm);
    else
      uniq_cmd(comm);
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
    redir_comm(comm);
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