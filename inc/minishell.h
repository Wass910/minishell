#ifndef MINISHELL_H
# define MINISHELL_H
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <readline/readline.h> 
#include <readline/history.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define BUFFER_SIZE 1024
# define CD_TYPE 0
# define ECHO_TYPE 1
# define PWD_TYPE 2
# define EXPORT_TYPE 3
# define UNSET_TYPE 4
# define ENV_TYPE 5
# define EXIT_TYPE 6

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_data{
	char	**cmd1;
	char	*path1;
	char	**cmd2;
	char	*path2;
	int		read_file;
	int		write_file;
	int		pid1;
	int		pid2;
	int		pipefd[2];
}				t_data;

typedef struct s_pip{
	char	*cmd;
	int		nb_cmd;
	char	*path;
	int		read_file;
	int		write_file;
	int 	redir_output;
    int 	redir_input;
	int 	redir_output_A;
    int 	redir_double_input;
	int 	single_quote;
    int 	double_quote;
	int		pid1;
	int		pid2;
	int		pipefd[2];
	struct s_pip *next;
}		t_pip;

typedef struct	s_comm
{
	char **env;
	char **expenv;
	char **cmd;
    int nb_pipe;
    int redir_output;
    int redir_input;
    int single_quote;
    int double_quote;
}				t_comm;

void	ft_lstadd_front(t_comm **alst, t_comm *new);
t_comm	*ft_add_back(t_comm **alst, t_comm *new);
char	**ft_split(char *s, char c);
int	ft_strncmp( char *s1,  char *s2, int n);
int	ft_strlen(char *s);
int if_builtin(char **str);
char	*ft_strcat(char *dest, char *src);
int	ft_strchr(char *s, int c);
t_comm	fill_comm(t_comm comm, char *cmd);
char			*ft_strjoin(char const *s1, char const *s2);
char	*ft_strcat_cmd(char *dest, char *src);
t_data	path2(t_data data, char *command);
t_data	path1(char *command);
void	free_str(char **str);
int	pipex(t_pip *parse_pip);
void	create_process(t_data data, t_comm comm);
t_data	uniq_path(t_data data, t_comm comm);
int	get_next_line(int fd, char **line);
void	*ft_calloc(int count, int size);
char	*ft_strjoin_free(char *s1, char *s2, int f);
char	*ft_substr(char *s, int start, int len);
char	*ft_strchr_gnl(char *s, int c);
void	print_comm(t_comm comm);
void	exec_cmd(char *s, t_comm comm);
int		builtin(t_comm comm, t_list **a_list, t_list **b_list);
int		build_cd(t_comm comm);
int		build_echo(t_comm comm, t_list **a_list);
int		build_pwd();
int		build_export(t_comm comm, t_list **a_list, t_list **b_list);
int		build_unset(t_comm comm, t_list **a_list, t_list **b_list, int type);
int		build_env(t_list **a_list);
int		build_exit(t_comm comm);
void    parsing_pipes(t_comm comm);
int	ft_double_strchr(char *s, int c);
int	ft_redir_strchr(char *s, int c);
char	*ft_strcat_ns(char *dest, char *src);
char	*ft_strjoin(char const *s1, char const *s2);
int		check_fulln(char *str);
int check_inenv(char *str, t_list **a_list);
void sort_env(t_list **b_list);
int check_sorted(t_list **b_list);
void print_env(t_list **b_list);
void add_declare(t_list **b_list);
void add_line(t_list **b_list, t_comm comm, int j);
char	*ft_strdup(char *s1);
char **make_expenv(t_comm comm);
void make_list(t_list **a_list, char **envp);
void	flstadd_back(t_list **alst, t_list *new);
void	flstclear(t_list **lst, void (*del)(void*));
void	flstadd_front(t_list **alst, t_list *new);
void	flstdelone(t_list *lst, void (*del)(void *));
void	flstiter(t_list *lst, void (*f)(void *));
t_list	*flstlast(t_list *lst);
t_list	*flstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*flstnew(void *content);
int	flstsize(t_list *lst);
char	*ft_strcat_cote(char *dest, char *src);
void add_line2(t_list **b_list, t_comm comm, int j);
int	ft_atoi(const char *str);
int is_same(char *s1, char *s2);
char *getenv2(char *s, t_list **a_list);
void    already_in(t_list **a_list, char *str, int j);
int is_alphanum(char *s);

#endif