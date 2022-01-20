#include "minishell.h"

char	*ft_strcpy(char *src)
{
	char	*dst;
	int i;

	i = 0;
	dst = (char*)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!src || !dst)
		return (NULL);
	else {
		while (src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (dst);
}
