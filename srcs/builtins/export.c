/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 04:03:35 by jcauchet          #+#    #+#             */
/*   Updated: 2022/08/26 17:44:00 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/***************************************************************************
Oh it's you again ? You waited me to explain you how this export 🚀 works and 
what it is for ? 😂  Well, unfortunately i bas my ownes couilles ! But whatever
i'll still do it. 
Export can create a variable in the shell 🐢  if it doesn't exist.
However, it replaces the value by the new one you describe.
He can rajoute des mots at la fin of the phrase too with '+='
***************************************************************************/

#include "../../includes/minishell.h"

void	add_list(char *c_path, char *name_exp)
{
	t_list	*new_lst;
	t_list	*new_lst_sorted;
	int		flag;

	flag = 0;
	if (check_equal(name_exp) == 1)
	{
		flag = 1;
		name_exp = delete_equal(name_exp);
	}
	new_lst = ft_lstnew(c_path, (ft_strlen(name_exp)));
	new_lst_sorted = ft_lstnew(c_path, (ft_strlen(name_exp)));
	new_lst = check_name(new_lst);
	new_lst_sorted = check_name(new_lst_sorted);
	if (flag == 1)
	{
		new_lst->print = 2;
		new_lst_sorted->print = 2;
		free(name_exp);
	}
	if (new_lst->print == 0)
	{
		printf("minishell: export: `%s': not a valid identifier\n",
			new_lst->name);
		g_glob->code = 1;
	}
	add_and_sort(new_lst, new_lst_sorted);
}

int	check_existing(char *name_exp, char *path_exp, int i)
{
	t_list	*env;
	t_list	*sorted;

	env = g_glob->env;
	name_exp = delete_equal(name_exp);
	sorted = g_glob->env_sorted;
	while (env)
	{
		while (sorted)
		{
			if (!ft_strncmp(sorted->name, name_exp, comp(name_exp, sorted)))
			{
				sorted->path = free_and_dup(sorted->path, path_exp);
				i = 1;
			}
			sorted = sorted->next;
		}
		if (!strncmp(env->name, name_exp, comp(name_exp, env)))
			env->path = free_and_dup(env->path, path_exp);
		env = env->next;
	}
	free (name_exp);
	return (i);
}

int	size_possibilities(	char *name_exp, char *path_exp)
{
	int	size;

	size = 0;
	if ((name_exp[ft_strlen(name_exp) - 1] == '=') && ft_strlen(name_exp) == 2)
		size = 3;
	else if (name_exp[ft_strlen(name_exp) - 1] == '=')
		size = ft_strlen(name_exp);
	else if ((ft_strlen(name_exp) && (!path_exp || ft_strlen(path_exp) <= 1)))
			size = ft_strlen(name_exp) + 1;
	else if (ft_strlen(name_exp) > 2 || ft_strlen(path_exp) > 2)
			size = ft_strlen(name_exp) + ft_strlen(path_exp) + 1;
	else if (ft_strlen(name_exp) == 1 && ft_strlen(path_exp) == 1)
		size = 3;
	else if (ft_strlen(name_exp) == 1 && ft_strlen(path_exp) == 2)
		size = 4;
	return (size);
}

void	exporting(char *c_path, char **many_arg, int size, int i)
{
	char	*name_exp;
	char	*path_exp;

	while (many_arg[i])
	{
		name_exp = return_name(&c_path[size]);
		path_exp = return_path(&c_path[size]);
		if (!check_existing(name_exp, path_exp, 0))
			add_list(many_arg[i], name_exp);
		size += size_possibilities(name_exp, path_exp);
		if (name_exp)
			free(name_exp);
		if (path_exp)
			free(path_exp);
		i++;
	}
}

int	export_(char **argv, int size)
{
	char	*c_path;
	char	**many_arg;
	int		i;

	size = 0;
	i = 0;
	c_path = export_setup(argv);
	g_glob->code = 0;
	if (!c_path)
	{
		print_list_export(g_glob->env_sorted);
		return (-1);
	}
	many_arg = ft_split(c_path, ' ');
	i = 0;
	exporting(c_path, many_arg, size, i);
	free_tab(many_arg);
	if ((!argv[4] && argv[3]) || argv[4])
		free(c_path);
	return (0);
}
