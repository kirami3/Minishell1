#include "minishell.h"

void	*ft_memset(char *s, int c, size_t n)
{
	unsigned char	*mas;
	unsigned char	ch;

	mas = (unsigned char *)s;
	ch = (unsigned char)c;
	while (n)
	{
		*mas++ = ch;
		n--;
	}
	return (s);
}
