#include "minishell.h"

t_list *arr;

void ft_set(char **line)
{
         *line = (char*)malloc(sizeof(char) * 1);
         ft_memset(*line, 0, sizeof(*line));
}

void ft_skip_space(char **line)
{
	while (**line == ' ' && **line != '\0')
		(*line)++;
}

char *lsh_read_line(void)
{
	char *inpt;

	inpt = readline(" ");
	add_history(inpt);
	printf("%s", inpt);
	printf("\n");
	return (inpt);
}

int lsh_execute(char **args)
{
	return (0);
}

char *ft_realloc(char *gen)
{
	size_t i;
	char *dest;

	i = ft_strlen(gen);
	dest = (char*)malloc(sizeof(char) * (i + 1));
	dest = ft_strdup(gen);
	return (dest);
}

char *ft_parsing_cmd(char **line, t_list *arr)
{
	char *gen;
	int i;

	i = 0;
	gen = (char*)malloc(sizeof(char) * 1);
	ft_memset(gen, 0, sizeof(gen));
	ft_skip_space(line);
	while (**line != '\0' && **line != ' ')
	{
		if (**line != '\'' && **line != '\"')
		{
			gen = ft_realloc(gen);
			gen[i] = **line;
			i++;
		}
		(*line)++;
	}
	gen = ft_realloc(gen);
	gen[i] = '\0';
	return (gen);
}

void ft_red_plus(char **line, char **s)
{
	int i;

	i = 0;
	while (**line != ' ' && **line != '\0')
	{
		*s = ft_realloc(*s);
		(*s)[i] = **line;
		i++;
		(*line)++;
	}
	(*s)[i] = '\0';
}

void ft_parsing_redirect(char **line)
{
	t_arg *ra;
	t_arg *tm1 = NULL;
	char *s;	
	int z;

	z = 2;
	if (arr->red)
		tm1 = arr->red;
	if (line[0][0] != '\0' && (line[0][0] == '>' || line[0][0] == '<' ||  ((line[0][1] == '>' || line[0][1] == '<') && line[0][0] == '2')))
	{
		while (**line != '\0' && z != 0 && **line != ' ')
		{
			ft_set(&s);
			ft_red_plus(line, &s);
			ra = ft_argnew(s, tm1);
			arr->red = ra;
			tm1 = ra;
			ra = ra->next;
			ft_skip_space(line);
			z--;
		}
	}
}

void ft_parsing_flag(char **line)
{
	int c;


	c = 0;
	if ((*line)[c] == '-' && (*line)[c + 1] == 'n' && !ft_strcmp("echo", arr->cmd))
	{
		arr->echo_nflag = 1;
		(*line) += 2;
	}
	else
		arr->echo_nflag = 0;
}

void ft_quote(char **line, char **l)
{
	int i;
	char *s;

	i = 0;
	ft_set(&s);
	if (**line == '\'' && **line != '\0')
	{
		(*line)++;
		while (**line != '\'' && **line != '\0')
		{
			s = ft_realloc(s);
			if (**line != '\'')
				s[i] = **line;
			i++;
			(*line)++;
		}
		(*line)++;
	}
	s = ft_realloc(s);
	s[i] = '\0';
	ft_strcat(l, &s);
}

void ft_char(char **line, char **l)
{
	int i;
	char *s;

	i = 0;
	ft_set(&s);
	while (**line != '\'' && **line != '\"' && **line != '\0' && **line != ' ' && **line != '$' && **line != '>' && **line != '<' && **line != '2')
	{
		s = ft_realloc(s);
		s[i] = **line;
		i++;
		(*line)++;
	}
	if (s)
	{
		s[i] = '\0';
		ft_strcat(l, &s);
	}
}

int	ft_path_parsing(char **line, char **s, t_data *data)
{
	char *st;
	int i;
	char *path;

	i = 0;
	if (**line == '$')
	{
		(*line)++;
		ft_set(&st);
		while (**line != ' ' && **line != '\0' && **line != '\"' && **line != '\'')
		{
			st = ft_realloc(st);
			st[i] = **line;
			(*line)++;
			i++;
		}
		st = ft_realloc(st);
		st[i] = '\0';
		path = ft_search_in_envp(data, st);
		if (path != NULL)
			ft_strcat(s, &path);
	}
	if (path)
		return (ft_strlen(path));
	else
		return (0);
}

void	ft_db_quote(char **line, char **l, t_data *data)
{
        int i;
        char *se;

        i = 0;
	ft_set(&se);
        if (**line == '\"' && **line != '\0')
        {
                (*line)++;
                while (**line != '\"' && **line != '\0')
                {
                        se = ft_realloc(se);
                        if (**line != '\"' && **line != '$')
                                se[i] = **line;
			if (**line == '$')
			{
				i += ft_path_parsing(line, &se, data) - 1;
				(*line)--;
			}
                        i++;
                        (*line)++;
                }
		(*line)++;
		se = ft_realloc(se);
		se[i] = '\0';
	 	ft_strcat(l, &se);
	}
}

void ft_parsing_arg(char **line, t_data *data)
{
	t_arg *tm = NULL;
	t_arg *ar = NULL;
	char *l = NULL;
	
	while (**line != '\0' && !(line[0][0] == '|'))// && line[0][1] != '|'))
	{
		ft_set(&l);
		while (**line != ' ' && **line != '\0')
		{
			ft_quote(line, &l);
			ft_char(line, &l);
			ft_db_quote(line, &l, data);
			ft_path_parsing(line, &l, data);
			ft_parsing_redirect(line);
		}
		if (ft_strlen(l) != 0 && (**line == ' ' || **line == '\0'))
		{
			ar = ft_argnew(l, tm);
			arr->arg = ar;
		//	ft_lstadd_back(&(arr->arg), ar);
			tm = ar;
			ar = arr->arg->next;
		}
		if (**line != '\0')
			(*line)++;
	}
//	while (arr->arg != NULL)
//	{
	//	printf("ARG LIST %s\n", arr->arg->content);
	//	arr->arg = arr->arg->prev;
//	}
/*	while (arr->red != NULL)
	{
		printf("RED LIST %s\n", arr->red->content);
		arr->red = arr->red->prev;
	}*/
}

void ft_parsing_post_cmd(char **line, t_data *data)
{
	arr->red = NULL;
	arr->arg = NULL;
	ft_parsing_redirect(line);
	ft_parsing_flag(line);
	ft_skip_space(line);
	ft_parsing_arg(line, data);
	ft_skip_space(line);
}

int ft_count_arg(t_arg *som)
{
	t_arg	*tmp;
	int i;

	i = 0;
	tmp = som;
	while (tmp != NULL)
	{
		tmp = tmp->prev;
		i++;
	}
	return (i);
}

void	ft_list_to_arr()
{
	int i;
	int j;
	
	i = ft_count_arg(arr->arg);
	j = ft_count_arg(arr->red);
	arr->fin = (char**)malloc(sizeof(char*) * (i + j)  + 1);
	arr->fin[i+j+1] = NULL;
	while (i > 0)
	{
		arr->fin[i+j] = (char*)malloc(sizeof(char) * ft_strlen(arr->arg->content));
		ft_strcat(&arr->fin[i+j], &arr->arg->content);
		i--;
		arr->arg = arr->arg->prev;
	}
	while (j > 0)
	{
		arr->fin[i+j] = (char*)malloc(sizeof(char) * ft_strlen(arr->red->content));
		ft_strcat(&arr->fin[i+j], &arr->red->content);
		j--;
		arr->red = arr->red->prev;
	}
	arr->fin[0] = (char*)malloc(sizeof(char) * ft_strlen(arr->cmd));
	ft_strcat(&arr->fin[i], &arr->cmd);
	while (arr->fin[i] != NULL)
	{
		printf("FIN %s\n", arr->fin[i]);
		i++;
	}
}

void ft_line_parsing(char *line, t_data *data)
{
	t_list *tmp = NULL;
	char *some;

	while (*line != '\0' && *line != '|')
	{
		ft_skip_space(&line);
		some = ft_parsing_cmd(&line, arr);
		if (ft_strlen(some) != 0)
		{
			arr = ft_lstnew(some, tmp);
			printf("CMD %s\n", arr->cmd);
			ft_skip_space(&line);
			if (*line != '\0')
				ft_parsing_post_cmd(&line, data);
		}
		printf("CHAR ~%c~\n", *line);
		if (*line != '\0' && line[0] == '|' && line[1] != '|')
		{
			line += 2;
			arr->pipe = 1;
		}
		else
			arr->pipe = 0;
		printf("NFLAG %d\n", arr->echo_nflag);
		printf("PIPEFG %d\n", arr->pipe);
		ft_list_to_arr();
		tmp = arr;
		if (*line != '\0')
			arr = arr->next;
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	}
}

void lsh_loop(char **envp)
{
	char *line;
	char **args;
	t_data *data;
	int status = 1;

	while (status)
	{
		printf(" > ");
		line = lsh_read_line();
		data = ft_datanew(envp);
		ft_line_parsing(line, data);
		status = lsh_execute(args);

	//	free(line);
	}
}

int main(int argc, char **argv, char **envp)
{
	lsh_loop(envp);
	return(0);
	//return EXIT_SUCCESS;
}
