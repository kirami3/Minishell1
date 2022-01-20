#include "minishell.h"

t_arg	*ft_lstlast(t_arg *lst)
{
	if (lst)
	{
		while (lst->next != NULL)
		{
			lst = lst->next;
		}
	}
	return (lst);
}
