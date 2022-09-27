/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:06:52 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/02 14:06:53 by glaverdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_pars	*cut_pglitch(t_pars *glitch, char *cmd_all)
{
	if (glitch->i >= 1 && !is_red(cmd_all[glitch->i - 1]))
	{
		glitch->cmd_tsplit[glitch->j] = 32;
		glitch->j++;
	}
	glitch->cmd_tsplit[glitch->j] = cmd_all[glitch->i];
	glitch->i++;
	glitch->j++;
	while (cmd_all[glitch->i] == 32)
		glitch->i++;
	while (is_red(cmd_all[glitch->i] || cmd_all[glitch->i == ' ']))
	{
		glitch->cmd_tsplit[glitch->j] = cmd_all[glitch->i];
		glitch->i++;
		glitch->j++;
	}
	return (glitch);
}

t_pars	*cut_pglitch2(t_pars *glitch, char *cmd_all)
{
	glitch->c = cmd_all[glitch->i];
	glitch->cmd_tsplit[glitch->j] = cmd_all[glitch->i];
	glitch->i++;
	glitch->j++;
	glitch->pass_space_for_redir = glitch->i;
	while (cmd_all[glitch->pass_space_for_redir] == 32)
		glitch->pass_space_for_redir++;
	if (is_red(cmd_all[glitch->pass_space_for_redir]))
	{
		glitch->cmd_tsplit[glitch->j] = 24;
		glitch->j++;
	}
	while (cmd_all[glitch->i] != glitch->c)
	{
		if (cmd_all[glitch->i] == 32)
			glitch->cmd_tsplit[glitch->j] = 25;
		else
			glitch->cmd_tsplit[glitch->j] = cmd_all[glitch->i];
		glitch->j++;
		glitch->i++;
	}
	glitch->cmd_tsplit[glitch->j] = cmd_all[glitch->i];
	glitch->i++;
	glitch->j++;
	return (glitch);
}
