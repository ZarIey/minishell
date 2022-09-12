/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 18:13:32 by ctardy            #+#    #+#             */
/*   Updated: 2022/08/26 17:52:53 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	size_list(t_p *parsed)
{
	int	i;
	t_p	*list;

	i = 0;
	list = parsed;
	if (!parsed)
		return (0);
	while (list->next != parsed)
	{
		list = list->next;
		i++;
	}
	return (i + 1);
}

int	is_arg(int type)
{
	if (type == TEXT || type == IN_QUOTES || type == IN_D_QUOTES
		|| type == EXEC || type == WHITE_SPACE || type == BUILTIN)
		return (1);
	return (0);
}

int	size_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	*space_guardian_arg(char *str, int type)
{
	int		i;
	char	*inter;

	i = 0;
	inter = str;
	if (inter[0] == 32)
	{
		if (check_space(inter) > 0 && type == WHITE_SPACE)
			inter = " ";
		return (inter);
	}
	return (inter);
}

char	*join_quotes(char *name, char *path)
{
	char	*joined;
	char	linker;	
	
	linker = '=';
	joined = join_christophe(name, linker);
	joined = ft_strjoin(joined, path);
	printf("Valeur de JOINED /*/*/*/*/ %s\n", joined);
	return (joined);
}

int	handle_quotes_argv(t_p *lexer)
{
	char	*name_exp;
	char	*path_exp;
	char	*c_path;
	t_p		*list;
	int		size_l;
	
	list = lexer;
	size_l = size_list(list);
	c_path = NULL;
	
	if (list->type == BUILTIN && !ft_strncmp(list->str, "export", 6))
	{
		list = list->next->next;
		if (list->type == TEXT)
		{
			name_exp = list->str;
			list = list->next;
			if (list->type == IN_D_QUOTES || list->type == IN_QUOTES)
			{
				path_exp = list->str;
				c_path = join_quotes(name_exp, path_exp);
				if (!check_existing(name_exp, path_exp, 0))
					add_list(c_path, name_exp);
				free(c_path);
				return (1);
			}
		}
	}
	return (0);
}

char	**creation_argv(t_p *lexer)
{
	char	**tab;
	t_p		*list;
	int		i;
	int		size;

	i = 0;
	list = lexer;
	if (handle_quotes_argv(lexer))
		return(NULL);
	size = size_list(list);
	tab = ft_calloc(500, 500);
	while (i < size)
	{
		if (is_arg(list->type))
		{
			if (list->type == WHITE_SPACE && (i == size - 1))
			{
				tab[i] = NULL;
				return (tab);
			}
			tab[i] = ft_strdup(space_guardian_arg(list->str, list->type));
			i++;
		}
		list = list->next;
	}
	tab[i] = NULL;
	return (tab);
}

char	*ft_strjoin_list(t_list *list_env)
{
	char	*str;
	char	*str2;
	char	*env_pers;
	t_list	*list;

	list = list_env;
	str = join_christophe(list->name, list->linker);
	str2 = ft_strjoin(str, list->path);
	env_pers = ft_strjoin(str2, "\n");
	return (env_pers);
}

char	**env_from_list(t_list *list_env, int size)
{
	int		i;
	t_list	*list;
	char	*joined_list;
	char	**env_pers;

	i = 0;
	list = list_env;
	env_pers = malloc(sizeof(char *) * size + 1);
	if (!env_pers)
		return (NULL);
	while (i < size)
	{
		joined_list = ft_strjoin_list(list);
		env_pers[i] = ft_strdup(joined_list);
		free(joined_list);
		i++;
		list = list->next;
	}	
	env_pers[i] = NULL;
	return (env_pers);
}

char	*is_fine(char *str, int i)
{
	while (str[i])
	{
		if (str[i] >= 65 && str[i] <= 90)
			str[i] = str[i] + 32;
		i++;
	}
	return (str);
}

char	*cut_str(char *str)
{
	int		i;
	int		j;
	char	clean_str[1024];
	char	*return_str;

	i = 0;
	j = 0;
	while (str[i])
		i++;
	while (str[i] != '/')
		i--;
	i++;
	while (str[i])
	{
		clean_str[j] = str[i];
		i++;
		j++;
	}
	clean_str[j] = '\0';
	return_str = clean_str;
	return (return_str);
}

char	**resize_tab(char **tab)
{
	char	**retab;
	char	*save;
	int		i;

	i = 0;
	save = tab[0];
	retab = malloc(sizeof(char *) * size_tab(tab) + 1);
	if (!retab)
		return (NULL);
	while (tab[i])
	{
		if (i == 0)
		{
			retab[0] = ft_strdup(cut_str(save));
			i++;
			continue ;
		}
		retab[i] = ft_strdup(tab[i]);
		i++;
	}
	retab[i] = NULL;
	return (retab);
}

char	**check_space_tab(char **tab)
{
	int		i;
	int		j;

	i = 0;
	j = 1;
	if (check_space(tab[i]) > 0)
	{
		free(tab[i]);
		while (tab[i] && tab)
		{
			tab[i] = tab[j];
			i++;
			j++;
		}
	}
	return (tab);
}

int	access_path(char **retab, char **env_pers)
{
	int		id;

	if (!g_glob->env)
		return (1);
	id = fork();
	if (!id)
	{
		execve(retab[0], &retab[0], NULL);
		exit(0);
	}
	waitpid(0, NULL, 0);
	free_tab(env_pers);
	free_tab(retab);
	return (0);
}

char	**retab(char **tab)
{
	int		i;
	char	*str;
	
	i = 0;
	str = NULL;
	while (tab[i])
		str = ft_strjoin(str, tab[i++]);
	free_tab(tab);
	tab = ft_split(str, ' ');
	free(str);
	return (tab);
}

int	find_builtin(char **tab)
{
	char	**env_pers;
	int		i;

	i = 0;
	env_pers = env_from_list(g_glob->env, ft_lstsize(g_glob->env));
	tab = check_space_tab(tab);
	tab[i] = is_fine(tab[i], 0);
	if (access(tab[i], F_OK) == 0)
	{
		tab = retab(tab);
		return (access_path(tab, env_pers));
	}
	if (is_builtin(tab[i]) == 1)
	{
		if (ft_strlen(tab[i]) == 4 && !ft_strncmp(tab[i], "echo", 4))
		{
			echo_(size_tab(tab), tab);
			free_tab(tab);
			free_tab(env_pers);
			return (1);
		}
		else if (ft_strlen(tab[i]) == 2 && !ft_strncmp(tab[i], "cd", 2))
		{
	
			cd_arg(size_tab(tab), tab);
			free_tab(tab);
			free_tab(env_pers);
			return (1);
		}
		else if (ft_strlen(tab[i]) == 3 && !ft_strncmp(tab[i], "pwd", 3))
		{
			
			pwd_(tab);
			free_tab(tab);
			free_tab(env_pers);
			return (1);
		}
		else if (ft_strlen(tab[i]) == 3 && !ft_strncmp(tab[i], "env", 3))
		{
			
			env_(g_glob->env, tab);
			free_tab(tab);
			free_tab(env_pers);
			return (1);
		}
		else if (ft_strlen(tab[i]) == 6 && !ft_strncmp(tab[i], "export", 6))
		{
			export_(tab, -1);
			free_tab(tab);
			free_tab(env_pers);
			return (1);
		}
		else if (ft_strlen(tab[i]) == 5 && !ft_strncmp(tab[i], "unset", 5))
		{
			
			unset_(tab, -1, tab);
			free_tab(tab);
			free_tab(env_pers);
			return (1);
		}
	 	else if (ft_strlen(tab[i]) == 4 && !ft_strncmp(tab[i], "exit", 4))
		{
			 
				 exit_(size_tab(tab), tab);
			free_tab(tab);
			free_tab(env_pers);
			return (1);
		}
	}
	if (is_exec(tab[i]) == 1)
	{
		i = 0;
		tab = retab(tab);
		cmd_main(tab, env_pers);
		free_tab(tab);
		free_tab(env_pers);
		return (1); // or return whatever you want, Christophe.
	}
	else
		printf("minishell: command not found: %s\n", tab[i]);
	g_glob->code = 127;
	free_tab(env_pers);
	free_tab(tab);
	return (0);
}
