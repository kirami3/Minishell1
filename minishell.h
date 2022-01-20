#ifndef MINISHELL_H
#define MINISHELL_H

# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_list
{
	char *cmd;
	struct s_arg *arg;
	struct s_arg *red;
	char **fin;
	int echo_nflag;
	int pipe;
	struct s_list *next;
	struct s_list *prev;
}		t_list;

typedef struct s_arg
{
	char *content;
	struct s_arg *next;
	struct s_arg *prev;
}		t_arg;

typedef struct s_data
{
	char **envp;
}		t_data;

void *ft_memset(char *s, int c, size_t n);
size_t ft_strlen(char *s);
void	ft_lstadd_front(t_arg **lst, t_arg *new1);
char *ft_strdup(char *src);
int	ft_strcmp(char *s1, char *s2);
void	ft_strcat(char **dest, char **src);
t_data	*ft_datanew(char *content, t_data *prev);
char *ft_search_in_envp(t_data *data, char *str);
int ft_strcmp_plus(const char *s1, const char *s2);
int numc(char *s, char c);
void *ft_clean(char **arr, size_t n);
char *ft_osnova(char **s, char c);
char **ft_split(char *s, char c);
void ft_split_free(char **str);
char	*ft_strcpy(char *src);
t_arg	*ft_lstlast(t_arg *lst);
void	ft_lstadd_back(t_arg **lst, t_arg *new);
size_t ft_func(char *s, unsigned int start, size_t len);
char *ft_substr(char *s, unsigned int start, size_t len);
t_arg *ft_argnew(char *content, t_arg *prev);
t_list *ft_lstnew(char *content, t_list *prev);

#endif
