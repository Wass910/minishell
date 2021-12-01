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

char	*split_glitch(char *cmd_all)
{
	t_pars	*glitch;

	glitch = glitch_setup(glitch);
	if (unclosed_quotes(cmd_all))
	{
		printf("Unclosed quotes, check your inport before retrying\n");
		return (NULL);
	}
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
	return (glitch->cmd_tsplit);
}
