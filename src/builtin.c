#include "../inc/minishell.h"

int	find_builtin(char **str)
{
	if ((ft_strncmp(str[0], "cd", 2) == 0) && ft_strlen(str[0]) == 2)
		return (CD_TYPE);
	else if ((ft_strncmp(str[0], "echo", 4) == 0) && ft_strlen(str[0]) == 4)
		return (ECHO_TYPE);
	else if ((ft_strncmp(str[0], "pwd", 3) == 0) && ft_strlen(str[0]) == 3)
		return (PWD_TYPE);
	else if ((ft_strncmp(str[0], "export", 6) == 0) && ft_strlen(str[0]) == 6)
		return (EXPORT_TYPE);
	else if ((ft_strncmp(str[0], "unset", 5) == 0) && ft_strlen(str[0]) == 5)
		return (UNSET_TYPE);
	else if ((ft_strncmp(str[0], "env", 3) == 0) && ft_strlen(str[0]) == 3)
		return (ENV_TYPE);
	else if ((ft_strncmp(str[0], "exit", 4) == 0) && ft_strlen(str[0]) == 4)
		return (EXIT_TYPE);
	return (-1);
}

int	builtin(char **cmd, t_list **a_list, t_list **b_list)
{
	int	type;

	type = find_builtin(cmd);
	if (type == CD_TYPE)
		return (build_cd(cmd));
	else if (type == ECHO_TYPE)
		return (build_echo(cmd, a_list));
	else if (type == PWD_TYPE)
		return (build_pwd());
	else if (type == EXPORT_TYPE)
		return (build_export(cmd, a_list, b_list));
	else if (type == UNSET_TYPE)
		return (build_unset(cmd, a_list, b_list, 0));
	else if (type == ENV_TYPE)
		return (build_env(a_list));
	else if (type == EXIT_TYPE)
		return (build_exit(cmd));
	return (0);
}
