#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int		i;
	unsigned char	*r;
	unsigned char	*t;

	i = 0;
	r = (unsigned char *)s1;
	t = (unsigned char *)s2;
	while (r[i] || t[i])
	{
		if (r[i] != t[i])
			return (r[i] - t[i]);
		i++;
	}
	return (0);
}
