#include "minishell.h"

t_arg *ft_argnew(char *content, t_arg *prev)
{
	t_arg *tmp;

	tmp = (t_arg *)malloc(sizeof(t_arg));
	if (tmp == NULL)
		return (tmp);
	tmp->content = content;
	tmp->prev = prev;
	tmp->next = NULL;
	return (tmp);
}
