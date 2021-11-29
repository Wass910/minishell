#include "../inc/minishell.h"

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
			builtin(comm.cmd, a_list, b_list);
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
		builtin(comm.cmd, a_list, b_list);
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
			builtin(comm.cmd, a_list, b_list);
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