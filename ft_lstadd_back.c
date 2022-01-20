#include "minishell.h"

void	ft_lstadd_back(t_arg **lst, t_arg *new)
{
	t_arg	*tmp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	else
	{
		tmp = ft_lstlast(*(lst));
		tmp->next = new;
	}
}
