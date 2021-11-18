#include "../inc/minishell.h"

// int	open_file2(char *filename)
// {
// 	if (access(filename, F_OK) == 0)
// 		return (open(filename, O_RDWR));
// 	else
// 		return (open(filename, O_CREAT | S_IWOTH));
// 	return (-1);
// }

// int	open_file(char *filename, t_data data)
// {
// 	if (open(filename, __O_DIRECTORY) != -1)
// 	{
// 		write(1, "the file is a directory.\n", 25);
// 		free(data.path1);
// 		free(data.path2);
// 		free_str(data.cmd1);
// 		free_str(data.cmd2);
// 		exit(EXIT_FAILURE);
// 	}
// 	if (access(filename, F_OK) == 0)
// 		return (open(filename, O_RDONLY));
// 	else
// 	{
// 		write(1, "The file doesn't exist.\n", 24);
// 		free(data.path1);
// 		free(data.path2);
// 		free_str(data.cmd1);
// 		free_str(data.cmd2);
// 		exit(EXIT_FAILURE);
// 	}
// 	return (-1);
// }

void	create_multi_process(t_data data)
{
	if (pipe(data.pipefd) == -1)
		exit(EXIT_FAILURE);
	data.pid1 = fork();
	if (data.pid1 == -1)
		exit(EXIT_FAILURE);
	if (data.pid1 == 0)
	{
		dup2(data.pipefd[1], STDOUT);
		close(data.pipefd[0]);
		close(data.pipefd[1]);
		execve(data.path1, data.cmd1, NULL);
	}
	data.pid2 = fork();
	if (data.pid2 == -1)
		exit(EXIT_FAILURE);
	if (data.pid2 == 0)
	{
		dup2(data.pipefd[0], STDIN);
		close(data.pipefd[0]);
		close(data.pipefd[1]);
		execve(data.path2, data.cmd2, NULL);
	}
}

// void	ft_cant_open(t_data data)
// {
// 	if (data.read_file == -1 || data.write_file == -1)
// 	{
// 		free(data.path1);
// 		free(data.path2);
// 		free_str(data.cmd1);
// 		free_str(data.cmd2);
// 		write(1, "Can't open this file, sorry.\n", 29);
// 		exit(EXIT_FAILURE);
// 	}
// }

int	pipex(t_pip *parse_pip)
{
	t_data	data;

	//print_comm(&comm);
	//printf("oui\n");
	//parse_pip = path1(comm.cmd[0]);
	//printf("datapath1 = %s", data.path1);
	//data = path2(data, comm.cmd[1]);
	//ft_cant_open(data);
	// dup2(data.read_file, STDIN);
	// dup2(data.write_file, STDOUT);
	create_multi_process(data);
	free(data.path1);
	free(data.path2);
	free_str(data.cmd1);
	free_str(data.cmd2);
	return (0);
}
