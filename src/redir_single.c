#include "../inc/minishell.h"

t_comm	initializing_cmd_single(t_comm parse_pip, char **tmp_all)
{
	int dest;
	int count;

	parse_pip.cmd = malloc(sizeof(char *) * (50));
	if (!parse_pip.cmd)
		return (parse_pip);
	dest = 0;
	count = 0;
	while (tmp_all[dest]) 
	{
		if (ft_strchr(tmp_all[dest], '>') == 0 && ft_strchr(tmp_all[dest], '<') == 0)
		{
			parse_pip.cmd[count] = ft_strcat_red("", tmp_all[dest]);
			count++;
		}
		else
			if (!tmp_all[dest][1])
				dest++;
		dest++;
	}
	parse_pip.cmd[count] = NULL;
	return parse_pip;
}

t_comm	initializing_red_single(t_comm parse_pip, char **tmp_all)
{
	int count_out;
	int count_in;
	int dest;
	dest = 0;
	count_out = 0;
	count_in = 0;
	parse_pip.redir = malloc(sizeof(char *) * (50));
	if (!parse_pip.redir)
		return(parse_pip);
	while (tmp_all[dest]) 
	{
		if (ft_strchr(tmp_all[dest], '>') > 0 || ft_strchr(tmp_all[dest], '<') > 0)
		{
			if (tmp_all[dest][1])
				parse_pip.redir[count_out] = ft_strcat_red_glu("", tmp_all[dest]);
			else if (tmp_all[dest + 1])
				parse_pip.redir[count_out] = ft_strcat_redf(tmp_all[dest], tmp_all[dest +1]);
			count_out++;
		}
	dest++;
	}
	parse_pip.redir[count_out] = NULL;
	parse_pip = initializing_cmd_single(parse_pip, tmp_all);
	return parse_pip;	
}

t_comm	check_initializing_red_single(t_comm parse_pip, char **tmp_all, char *str)
{
	char *cmd;
	char **to_parse;

	cmd = ft_split_command(str);
	if (error_in_red(str) == ERROR_RED)
		parse_pip.error_parse_red = 1;
	to_parse = ft_split(cmd, ' ');
	parse_pip = initializing_red_single(parse_pip, to_parse);
	return parse_pip;	
}

t_comm   redirection_single(t_comm new, char **tmp_all, char *str)
{
  if (new.redir_input > 0 || new.redir_output > 0)
	{
		new = check_initializing_red_single(new, tmp_all, str);
	}
	else
	{
		new.cmd = ft_split(str,' ');
		new.redir = NULL;

	}
  return new;
}

t_comm	ft_redir_single(char *str, int i)
{
	t_comm parse_pip;
	char **tmp_all;
	
  tmp_all = ft_split(str, ' ');
  parse_pip.error_parse_red = 0;
	parse_pip.redir_output = ft_redir_strchr(str, '>');
	parse_pip.redir_input = ft_redir_strchr(str, '<');
  parse_pip = redirection_single(parse_pip, tmp_all, str);
	parse_pip.path = NULL;
  free_str(tmp_all);
	return (parse_pip);
}
