/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 16:00:00 by ctardy            #+#    #+#             */
/*   Updated: 2022/08/26 16:40:56 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cd_arg(int argc, char **argv)
{
	char	*old;
	char	*current;

	old = check_current();
	if (g_glob->cur_path)
		free(g_glob->cur_path);
	g_glob->cur_path = old;
	g_glob->code = 0;
	if (argc == 1)
	{
		chdir(home_path());
		g_glob->cur_path = check_current();
		current = check_current();
		change_env(old, current);
		return (0);
	}
	cd_(argv[2], old);
	g_glob->cur_path = check_current();
	current = check_current();
	change_env(old, current);
	return (0);
}

void	change_env(char *old, char *current)
{
	t_list	*list;

	list = g_glob->env;
	while (list)
	{
		if (!strncmp(list->name, "OLDPWD", 6))
		{
			free(list->path);
			list->path = old;
		}
		list = list->next;
	}
	list = g_glob->env;
	while (list)
	{
		if (!strncmp(list->name, "PWD", 3))
		{
			free(list->path);
			list->path = current;
		}
		list = list->next;
	}		
}
