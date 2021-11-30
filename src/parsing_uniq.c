#include "../inc/minishell.h"

int    parcing(char *all_cmd, t_comm comm, t_list **a_list, t_list **b_list)
{

		char **str;
		char *cmd_new;
		int i;

		printf("ret val p = %d\n", retval);
		if (ft_strchr(all_cmd, '|') > 0)
		{
			pipe_glitch(all_cmd,comm, a_list, b_list);
			return (1);
		}
		cmd_new = malloc(sizeof(char) * 100);
		cmd_new = split_glitch(all_cmd);
		printf("after glitch = %s\n", cmd_new);
		str = ft_split(cmd_new, ' ');
		cmd_new = parse_quotes(str, a_list, comm);
		if (!cmd_new)
			return(1);
		printf("after quote parse  = %s\n", cmd_new);
		comm = fill_comm(comm, cmd_new);
		if (ft_error_parse_red(comm.redir) == 0)
		{
			printf("Minishell: syntax error near unexpected token\n");
			return -1;
		}
		int j = 0, k = 0;
		while (comm.cmd[j])
		{
			while (comm.cmd[j][k])
			{
				if (comm.cmd[j][k] == 25)
					comm.cmd[j][k] = 32;
				k++;
			}
			k = 0;
			j++;
		}
		j = 0;
		k = 0;
		while (comm.redir[j])
		{
			while (comm.redir[j][k])
			{
				if (comm.redir[j][k] == 25)
					comm.redir[j][k] = 32;
				k++;
			}
			k = 0;
			j++;
		}
		comm = ft_double_left_red(comm);
		if (comm.redir_temp[0])
			ft_redir_temp(comm.redir_temp, comm.redir_double_input);
		print_comm(comm);
		return(uniq_cmd(comm, a_list, b_list));
}