#include "minishell.h"

char	*ft_strdup(char *src)
{
	int		i;
	char	*s;

	i = 0;
	s = (char *)malloc(ft_strlen(src) + 1);
	if (!s)
		return (NULL);
	while (src[i])
	{
		s[i] = src[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}
