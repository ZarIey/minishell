/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctardy <ctardy@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:55:44 by ctardy            #+#    #+#             */
/*   Updated: 2022/06/27 14:57:37 by ctardy           ###   ########.fr       */
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

char	*add_on_path(char *complet_path, char *path_export, char *saved_path)
{
	int		i;
	int		size;
	char	*path_join;
	char	*clean_p;

	i = 0;
	size = (ft_strlen(complet_path));
	while (complet_path[i] != '=')
		i++;
	i--;
	if (complet_path[i] == '+')
	{
		i = i + 2;
		clean_p = clean_path(saved_path);
		path_join = ft_strjoin(clean_p, ft_substr(complet_path, i, size));
		path_join = make_path(path_join);
		return (path_join);
	}
	make_path(path_export);
	return (path_export);
}

void	export(char *complet_path, t_list *lst_env)
{
	t_list	*new_lst;
	char	*name_export;
	char	*path_export;
	char	*saved_path;
	int		i;

	if (!complet_path)
		return ;
	name_export = return_name(complet_path);
	path_export = return_path(complet_path);
	i = 0;
	while (lst_env)
	{
		saved_path = ft_substr(lst_env->path, 0, ft_strlen(lst_env->path));
		if (strncmp(lst_env->name, name_export, ft_strlen(name_export)) == 0)
		{
			free(lst_env->path);
			lst_env->path = add_on_path(complet_path, path_export, saved_path);
			return ;
		}
		lst_env = lst_env->next_sort;
	}
	new_lst = ft_lstnew(complet_path, (ft_strlen(name_export) + 1));
	ft_lstadd_back(&g_global->env, new_lst);
	sort_list(&g_global->env);
}

// int main (int argc, char **argv, char **env)
// {
// 	(void)argc;
// 	t_list	*list;
// 	return_list(env);
// 	list = g_global->env;
// 	char *complet_path = argv[1];
// 	export(complet_path, list);
// 	//g_global->env = list;
// 	print_list(g_global->env);
// //	while(1);
// //	export(complet_path);	
// }