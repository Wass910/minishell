/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_bin3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:05:31 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/10 18:13:35 by glaverdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*fill_doll_norm(t_doll *doll)
{
	char	*s;

	doll->str[doll->j] = '\0';
	s = ft_strdup_free(doll->str);
	free(doll);
	return (s);
}

char	*ft_strcat_free(char *dest, char *src)
{
	unsigned int	i;
	unsigned int	j;
	char			*tmp;

	tmp = malloc(sizeof(char) * (ft_count_str(dest, src) + 2));
	if (!tmp)
		return (0);
	i = 0;
	while (dest && dest[i] != '\0')
	{
		tmp[i] = dest[i];
		i++;
	}
	tmp[i] = ' ';
	i++;
	j = 0;
	while (src && src[j] != '\0')
	{
		tmp[i] = src[j];
		i++;
		j++;
	}
	tmp[i] = '\0';
	free(src);
	return (tmp);
}

char	*ft_norm_ctrl(void)
{
	g_line.tour = 0;
	if (g_line.retval == 130)
		return (readline(""));
	return (readline("$> "));
}

void	norm_for_double_input(t_comm comm)
{
	if (comm.redir_temp[0])
		ft_redir_temp(comm.redir_temp, comm.redir_double_input);
	else
		free_str(comm.redir_temp);
}

char	*sret_ret(char *s, char *sret)
{
	sret = ft_strcat_cote(s, "\0");
	free(s);
	return (sret);
}
