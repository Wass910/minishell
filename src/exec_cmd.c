#include "../inc/minishell.h"

void	exec_cmd(char *s, t_comm comm)
{
	execve(s, comm.cmd, NULL);
}

int	build_cd(char **cmd)
{
	int		i;
	char	*str;
	char	*s;

	if (!cmd[1])
	{
		str = getenv("HOME");
		if (!str)
			return (-1);
		i = chdir(str);
	}
	else if (cmd[1][0] == '-' && cmd[1][1] == '\0')
	{
		build_pwd();
		return (0);
	}
	else if (cmd[1][0] == '~' && cmd[1][1] == '\0')
	{
		str = getenv("HOME");
		if (!str)
			return (-1);
		i = chdir(str);
	}
	else if (cmd[1][0] == '~' && cmd[1][1] == '/')
	{
		s = malloc(100);
		if (!s)
			return (-1);
		str = getenv("HOME");
		if (!str)
			return (-1);
		i = 1;
		while (cmd[1][i])
		{
			s[i - 1] = cmd[1][i];
			i++;
		}
		s[i - 1] = '\0';
		str = ft_strjoin(str, s);
		i = chdir(str);
		if (i == -1)
		{
			str = strerror(errno);
			printf("cd: %s: %s\n", cmd[1], str);
		}
		free(s);
		return (i);
	}
	else
		i = chdir(cmd[1]);
	if (i == -1)
	{
		str = strerror(errno);
		printf("cd: %s: %s\n", cmd[1], str);
	}
	return (i);
}

int	is_returnvalue(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '$' && s[1] == '?' && s[2] == '\0')
		return (1);
	return (0);
}

int	build_echo(char **cmd, t_list **a_list)
{
	int		i;
	char	*str;

	if (!cmd[1])
	{
		printf("\n");
		return (0);
	}
	if (strncmp(cmd[1], "-n", 2) == 0 && !check_fulln(cmd[1]))
	{
		i = 2;
		while (cmd[i])
		{
			// if (is_returnvalue(cmd[i]))
			// {
			//     str = ft_itoa(retclone);
			//     write(1, str, ft_strlen(str));
			// }
			//else
				write(1, cmd[i], ft_strlen(cmd[i]));
			if (cmd[i + 1])
				write(1, " ", 1);
			i++;
		}
	}
	else
	{
		i = 1;
		while (cmd[i])
		{
			// if (is_returnvalue(cmd[i]))
			// {
			//     str = ft_itoa(retclone);
			//     write(1, str, ft_strlen(str));
			// }
			//else
				write(1, cmd[i], ft_strlen(cmd[i]));
			if (cmd[i + 1])
				write(1, " ", 1);
			i++;
		}
		write(1, "\n", 1);
	}
	return (0);
}

int	build_pwd(void)
{
	char	*str;
	char	s[100];

	str = getcwd(s, 100);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	if (str == NULL)
		return (1);
	return (0);
}

int	build_export(char **cmd, t_list **a_list, t_list **b_list)
{
	static int	done = 0;
	int			i;

	i = 1;
	if (!done)
	{
		add_declare(b_list);
		done = 1;
	}
	if (check_sorted(b_list))
	{
		sort_env(b_list);
	}
	while (cmd[i])
	{
		already_in(a_list, cmd[i], 0);
		already_in(b_list, cmd[i], 1);
		add_line(b_list, cmd, i);
		add_line2(a_list, cmd, i);
		i++;
	}
	if (!cmd[1])
		print_env(b_list);
	return (0);
}
