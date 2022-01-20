#include "minishell.h"

void	ft_lstadd_front(t_arg **lst, t_arg *new1)
{
	if (lst && new1)
	{
		new1->next = *lst;
		*lst = new1;
	}
}
