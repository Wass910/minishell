#ifndef MINISHELL_H
# define MINISHELL_H
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

typedef struct	s_comm
{
	char **cmd;
    int nb_pipe;
    int redir_output;
    int redir_input;
}				t_comm;

void	ft_lstadd_front(t_comm **alst, t_comm *new);
t_comm	*ft_add_back(t_comm **alst, t_comm *new);
char	**ft_split(char *s, char c);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	ft_strlen(char *s);
int if_builtin(char **str);
char	*ft_strcat(char *dest, char *src);
int	ft_strchr(char *s, int c);
t_comm	fill_comm(t_comm comm, char *cmd);
char			*ft_strjoin(char const *s1, char const *s2);

#endif