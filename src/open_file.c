/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:06:51 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/10 10:35:46 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_pipe	*fill_redir_attribut(t_pipe *parse_pip, int to_read, int to_write)
{
	if (to_read >= 0 && to_write >= 0)
	{
		parse_pip->file_to_in = ft_strcat_red("", parse_pip->redir[to_read]);
		parse_pip->read_file = open_file(parse_pip->redir[to_read]);
		parse_pip->file_to_out = ft_strcat_red("", parse_pip->redir[to_write]);
		parse_pip->write_file = open_file2(parse_pip->redir[to_write]);
	}
	else if (to_write >= 0)
	{
		parse_pip->file_to_out = ft_strcat_red("", parse_pip->redir[to_write]);
		parse_pip->write_file = open_file2(parse_pip->redir[to_write]);
		parse_pip->file_to_in = NULL;
	}
	else if (to_read >= 0)
	{
		parse_pip->file_to_in = ft_strcat_red("", parse_pip->redir[to_read]);
		parse_pip->read_file = open_file(parse_pip->redir[to_read]);
		parse_pip->file_to_out = NULL;
	}
	else
	{
		parse_pip->file_to_in = NULL;
		parse_pip->file_to_out = NULL;
	}
	return (parse_pip);
}

t_open	fill_error_red(t_pipe *parse_pip, t_open open)
{
	while (parse_pip->redir[open.i])
	{
		if (parse_pip->redir[open.i]
			&& ft_strchr(parse_pip->redir[open.i], '<') > 0)
		{
			open.retnd = open_file(parse_pip->redir[open.i]);
			if (open.retnd == -1)
				parse_pip->error_syn_red = 1;
			if (open.retnd != -1)
				open.to_read = open.i;
		}
		open.i++;
	}
	return (open);
}

t_pipe	*open_file_redir(t_pipe *parse_pip)
{
	t_open	open;

	open.i = 0;
	open = open_setup(open);
	if (parse_pip->redir)
	{
		open = fill_error_red(parse_pip, open);
		if (parse_pip->error_syn_red != 1)
		{
			open.i = 0;
			while (parse_pip->redir[open.i])
			{
				if (parse_pip->redir[open.i]
					&& ft_strchr(parse_pip->redir[open.i], '>') > 0)
				{
					open.retnd = open_file2(parse_pip->redir[open.i]);
					if (open.retnd != -1)
						open.to_write = open.i;
				}
				open.i++;
			}
		}
	}
	parse_pip = fill_redir_attribut(parse_pip, open.to_read, open.to_write);
	return (parse_pip);
}

int	open_file2(char *file)
{
	int		i;
	int		count;
	int		red;

	count = 0;
	red = 0;
	if (file[0] == '>' && file[1] == '<')
		red = 45;
	while (file[count++] == '>')
		red++;
	while (file[count] == 24)
		count++;
	if (red == 1)
		i = open(file + count - 1, O_RDWR | O_CREAT | S_IWOTH | O_TRUNC, 0664);
	else if (red == 2)
		i = open(file + count - 1, O_RDWR | O_CREAT | S_IWOTH | O_APPEND, 0664);
	else
		return (-1);
	if (i == -1)
	{
		g_line.retval = 1;
		printf("%s: %s\n", file, strerror(errno));
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
	while (filename[count++] == '<')
		red++;
	while (filename[count] == 24)
		count++;
	if (red == 1)
		i = open(filename + count - 1, O_RDONLY);
	else
		return (-1);
	if (i == -1)
	{
		g_line.retval = 1;
		str = strerror(errno);
		filename++;
		printf("%s: %s\n", filename, str);
		return (-1);
	}
	return (i);
}
