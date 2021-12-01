#include "../inc/minishell.h"

t_pipe	*parcing_comm_pip(char *all_cmd, t_comm comm, t_list **a_list, int i)
{
	char	**str;
	char	*cmd_new;
	t_pipe	*new;

	new = malloc(sizeof(*new));
	if (new == NULL)
		exit(EXIT_FAILURE);
	cmd_new = malloc(sizeof(char) * 100);
	cmd_new = split_glitch(all_cmd);
	str = ft_split(cmd_new, ' ');
	cmd_new = parse_quotes(str, a_list, comm);
	new = fill_comm_pip(new, cmd_new);
	new->redir_temp = malloc(sizeof(char *) * 150);
	new->redir_temp[0] = NULL;
	new->nb_cmd = i;
	if (access(new->cmd[0], F_OK) == 0)
		new->path = new->cmd[0];
	else
		new->path = path(new->cmd[0], a_list);
	new->read_file = -1;
	new->write_file = -1;
	if (ft_error_parse_red(new->redir) == 0)
		new->error_syn_red = 1;
	else
		new->error_syn_red = 0;
	if (new->error_syn_red == 0)
		new = open_file_redir(new);
	new->next = NULL;
	return (new);
}

t_pipe	*new_parcing_comm_pip(char *all_cmd, t_comm comm, t_pipe *pipe, t_list **a_list, int i)
{
	char	**str;
	char	*cmd_new;
	t_pipe	*new;

	new = malloc(sizeof(*new));
	if (new == NULL)
		exit(EXIT_FAILURE);
	cmd_new = malloc(sizeof(char) * 100);
	cmd_new = split_glitch(all_cmd);
	str = ft_split(cmd_new, ' ');
	cmd_new = parse_quotes(str, a_list, comm);
	new = fill_comm_pip(new, cmd_new);
	new->redir_temp = malloc(sizeof(char *) * 150);
	new->redir_temp[0] = NULL;
	if (access(new->cmd[0], F_OK) == 0)
		new->path = new->cmd[0];
	else
		new->path = path(new->cmd[0], a_list);
	new->read_file = -1;
	new->write_file = -1;
	new->nb_cmd = i;
	if (ft_error_parse_red(new->redir) == 0)
		new->error_syn_red = 1;
	else
		new->error_syn_red = 0;
	if (new->error_syn_red == 0)
		new = open_file_redir(new);
	new->next = pipe;
	return (new);
}
