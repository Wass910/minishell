#include "../inc/minishell.h"

t_pipe	*fill_redir_attribut(t_pipe *parse_pip, int to_read, int to_write)
{
	if (to_read >= 0)
	{
		parse_pip->file_to_in = ft_strcat_red("", parse_pip->redir[to_read]);
		parse_pip->read_file = open_file(parse_pip->redir[to_read]);
	}
	else
	{
		parse_pip->file_to_out = malloc(50);
		parse_pip->file_to_in = NULL;
	}
	if (to_write >= 0)
	{
		parse_pip->file_to_out = ft_strcat_red("", parse_pip->redir[to_write]);
		parse_pip->write_file = open_file2(parse_pip->redir[to_write]);
	}
	else
	{
		parse_pip->file_to_out = malloc(50);
		parse_pip->file_to_out = NULL;
	}
	return (parse_pip);
}

t_pipe	*open_file_redir(t_pipe *parse_pip)
{
	int		retnd;
	int		i;
	int		to_read;
	int		to_write;

	i = 0;
	to_read = -1;
	to_write = -1;
	if (parse_pip->redir)
	{
		while (parse_pip->redir[i])
		{
			if (parse_pip->redir[i] && ft_strchr(parse_pip->redir[i], '<') > 0)
			{
				retnd = open_file(parse_pip->redir[i]);
				if (retnd == -1)
					parse_pip->error_syn_red = 1;
				if (retnd != -1)
					to_read = i;
			}
			i++;
		}
		if (parse_pip->error_syn_red != 1)
		{
			i = 0;
			while (parse_pip->redir[i])
			{
				if (parse_pip->redir[i]
					&& ft_strchr(parse_pip->redir[i], '>') > 0)
				{
					retnd = open_file2(parse_pip->redir[i]);
					if (retnd != -1)
						to_write = i;
				}
				i++;
			}
		}
	}
	parse_pip = fill_redir_attribut(parse_pip, to_read, to_write);
	return (parse_pip);
}

int	open_file2(char *filename)
{
	int		i;
	int		count;
	int		red;
	char	*str;

	count = 0;
	red = 0;
	if (filename[0] == '>' && filename[1] == '<')
		red = 45;
	while (filename[count] == '>')
	{
		count++;
		red++;
	}
	while (filename[count] == 24)
		count++;
	if (red == 1)
		i = open(filename + count, O_RDWR | O_CREAT | S_IWOTH | O_TRUNC, 0664);
	else if (red == 2)
		i = open(filename + count, O_RDWR | O_CREAT | S_IWOTH | O_APPEND, 0664);
	else
		return (-1);
	if (i == -1)
	{
		str = strerror(errno);
		printf("%s: %s\n", filename, str);
		return (-1);
	}
	return (i);
}

int	open_file(char *filename)
{
	char	*str;
	int		i;
	int		count;
	int		red;

	count = 0;
	red = 0;
	while (filename[count] == '<')
	{
		count++;
		red++;
	}
	while (filename[count] == 24)
		count++;
	if (red == 1)
		i = open(filename + count, O_RDONLY);
	else
		return (-1);
	if (i == -1)
	{
		str = strerror(errno);
		filename++;
		printf("%s: %s\n", filename, str);
		return (-1);
	}
	return (i);
}
