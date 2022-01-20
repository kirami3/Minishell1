#include "minishell.h"

void	ft_strcat(char **dest, char **src)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while ((*dest)[i])
		i++;
	if (i == 0)
		*dest = *src;
	if ((*src))
	{
		while ((*src)[j])
		{
			(*dest)[i + j] = (*src)[j];
			j++;
		}
		(*dest)[i + j] = '\0';
	}
}
