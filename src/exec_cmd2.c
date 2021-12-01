#include "../inc/minishell.h"

int	is_same(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] && s2[j])
	{
		if (s1[i] != s2[j])
			break ;
		i++;
		j++;
	}
	if (s1[i] == '=' && s2[j] == '\0')
		return (0);
	if (s1[i] == '\0' && s2[j] == '\0')
		return (0);
	return (1);
}

int	build_unset(char **cmd, t_list **a_list, t_list **b_list, int type)
{
	char	*str;
	int		i;
	t_list	*temp;
	t_list	*del;
	char	*s;

	i = 1;
	str = cmd[i];
	s = malloc(sizeof(char) * 1000);
	if (!s)
		return (1);
	while (cmd[i])
	{
		if (cmd[i][1] == '=')
			str = ft_strcat_ns(cmd[i], "=");
		else
			str = cmd[i];
		if (type == 0)
			temp = (*b_list);
		else
			temp = (*a_list);
		if (type == 0)
			s = &temp->content[11];
		else
			s = temp->content;
		printf("str = %s | s = %s | strlen = %d\n", str, s, ft_strlen(str) + 1);
		if (is_same(s, str) == 0)
		{
			(*b_list) = (*b_list)->next;
			if (cmd[i + 1])
			{
				i++;
				str = cmd[i];
			}
			else
				return (0);
		}
		while (temp->next)
		{
			if (type == 0)
				s = &temp->next->content[11];
			else
				s = temp->next->content;
			if (is_same(s, str) == 0)
				break ;
			temp = temp->next;
		}
		if (is_same(s, str) == 0)
		{
			del = temp->next;
			temp->next = temp->next->next;
		}
		i++;
		str = cmd[i];
	}
	if (type == 0)
		build_unset(cmd, a_list, b_list, 1);
	return (0);
}

int	build_env(t_list **a_list)
{
	t_list	*temp;

	temp = (*a_list);
	while (temp->next)
	{
		printf("%s\n", temp->content);
		temp = temp->next;
	}
	printf("%s\n", temp->content);
	return (0);
}

int	build_exit(char **cmd)
{
	int	i;

	if (cmd[1])
	{
		i = ft_atoi(cmd[1]);
		if (cmd[1][0] != '0' && i == 0)
		{
			printf("exit : %s: numeric argument required\n", cmd[1]);
			exit(2);
		}
		else
			printf("exit\n");
		exit(i);
	}
	else
	{
		printf("exit\n");
		exit(0);
	}
}
