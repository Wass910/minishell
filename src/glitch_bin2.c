#include "../inc/minishell.h"

t_doll	*incr_doll(t_doll *doll)
{
	doll->str[doll->j] = '$';
	doll->j++;
	doll->i++;
	return (doll);
}

t_doll	*incr_doll2(t_doll *doll, char *s)
{
	doll->str[doll->j] = s[doll->i];
	doll->j++;
	doll->i++;
	return (doll);
}
