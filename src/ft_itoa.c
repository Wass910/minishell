/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:51:45 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/03 16:28:01 by glaverdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	ft_norme_itoa(int n)
{
	if (n < 0)
	{	
		n = -1 * (n);
		ft_putchar('-');
	}
	if (n == 0)
		ft_putchar('0');
	return (n);
}

int	ft_count2(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		i = 1;
	if (n == 0)
	{
		i = 1;
		return (i);
	}
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_strrev(char *str)
{
	int		i;
	int		y;
	char	*tmp;

	y = 0;
	i = 0;
	while (str[i] != '\0')
		i++;
	tmp = (char *)malloc(sizeof(char) * (i + 1));
	if (tmp == NULL)
		return (0);
	i--;
	while (i >= 0)
	{
		tmp[y] = str[i];
		i--;
		y++;
	}
	tmp[y] = '\0';
	return (tmp);
}

char	*ft_itoa(int n)
{
	char	*alpha;
	char	*str;
	char	*test;
	int		i;

	i = 0;
	str = malloc(sizeof(char) * (ft_count2(n) + 1));
	if (str == NULL)
		return (0);
	alpha = "0123456789abcdef";
	n = ft_norme_itoa(n);
	while (n > 0)
	{
		str[i] = alpha[n % 10];
		i++;
		n = n / 10;
	}
	str[i] = '\0';
	test = ft_strrev(str);
	free(str);
	return (test);
}
