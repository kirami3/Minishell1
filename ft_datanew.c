#include "minishell.h"

t_data	*ft_datanew(char **e)
{
	t_data *tmp;

	tmp = (t_data *)malloc(sizeof(t_data));
	if (tmp == NULL)
		return (tmp);
	tmp->envp = e;
	return (tmp);
}
