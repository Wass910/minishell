#include "../inc/minishell.h"

int red_uniq_comm(t_comm comm, char *str, t_list **a_list, t_list **b_list)
{
	comm.read_file = -3;
	comm.write_file = -3;
	int k;
	int retnd;
	int i = 0;
	int to_read = -1;
	int to_write = -1;
	int status;
	while (comm.redir[i])
	{
		if ((comm.redir[i] && (ft_strchr(comm.redir[i], '>') == 1 || ft_strchr(comm.redir[i], '>') == 2)))
		{
			 retnd = open_file2(comm.redir[i]);
			 close(retnd);
			if (retnd == -1)
				return (retnd);
			to_write = i;
		}
		if (comm.redir[i] && ft_strchr(comm.redir[i], '<') == 1 )
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
	else if(to_read < 0 && to_write >= 0)
		 k = w_redirection(comm, a_list, b_list, str);
	else if(to_read >= 0 && to_write < 0)
		k = r_redirection(comm, a_list, b_list, str);
	else
	{
			if (access(str, F_OK) != 0)
			{
				printf("%s: command not found\n", comm.cmd[0]);
				return (1);
			}
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
			k = builtin(comm.cmd, a_list, b_list);
			return (k);
		}
		//else
			//printf("continue the parse\n");
		//if(access(comm.cmd[0], F_OK) == 0)
			//printf("command found whithout path\n");
		if (access(comm.cmd[0], F_OK) == 0)
			str = comm.cmd[0];
		else if (path)
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
			//printf("continue the parse\n");
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