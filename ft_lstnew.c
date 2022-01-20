#include "minishell.h"

t_list	*ft_lstnew(char *content,t_list *prev)
{
	t_list	*tmp;

	tmp = (t_list *)malloc(sizeof(t_list));
	if (tmp == NULL)
		return (tmp);
	tmp->cmd = content;
	tmp->prev = prev;
	tmp->next = NULL;
	return (tmp);
}
