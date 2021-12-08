/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_glitch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:06:53 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/07 11:28:24 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_pars	*glitch_setup(t_pars *glitch)
{
	glitch = malloc(sizeof(t_pars) * 1);
	if (!glitch)
		exit(EXIT_FAILURE);
	glitch->cmd_tsplit = malloc(sizeof(char) * 100);
	if (!glitch->cmd_tsplit)
		exit(EXIT_FAILURE);
	glitch->i = 0;
	glitch->j = 0;
	return (glitch);
}

int	for_quote_unclosed_norme(char *cmd_all)
{
	if (unclosed_quotes(cmd_all))
	{
		printf("Unclosed quotes, check your inport before retrying\n");
		return (1);
	}
	return (0);
}

char	*split_glitch(char *cmd_all)
{
	t_pars	*glitch;
	char	*copy;

	glitch = NULL;
	glitch = glitch_setup(glitch);
	if (for_quote_unclosed_norme(cmd_all) == 1)
		return (NULL);
	while (cmd_all[glitch->i])
	{
		if (cmd_all[glitch->i] == 34 || cmd_all[glitch->i] == 39)
			glitch = cut_pglitch2(glitch, cmd_all);
		else if (is_red(cmd_all[glitch->i]))
			glitch = cut_pglitch(glitch, cmd_all);
		else
		{
			glitch->cmd_tsplit[glitch->j] = cmd_all[glitch->i];
			glitch->j++;
			glitch->i++;
		}
	}
	glitch->cmd_tsplit[glitch->j] = '\0';
	copy = ft_strdup(glitch->cmd_tsplit);
	free(glitch->cmd_tsplit);
	free(glitch);
	return (copy);
}
