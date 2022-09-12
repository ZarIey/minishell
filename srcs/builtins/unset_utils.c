/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctardy <ctardy@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 09:03:19 by ctardy            #+#    #+#             */
/*   Updated: 2022/08/26 10:22:46 by ctardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_existing_unset(char *name_exp, char *path_exp, int i)
{
	t_list	*env;
	t_list	*sorted;
	int		j;

	j = 0;
	while (name_exp[j])
		j++;
	env = g_glob->env;
	sorted = g_glob->env_sorted;
	while (env)
	{
		while (sorted)
		{
			if (!ft_strncmp(sorted->name, name_exp, comp(name_exp, sorted)))
			{
				free(sorted->path);
				sorted->path = ft_strdup(path_exp);
				if (!(ft_strncmp(sorted->path, "", ft_strlen(sorted->path))))
					sorted->print = 0;
				i = 1;
			}
			sorted = sorted->next;
		}
		if (!strncmp(env->name, name_exp, comp(name_exp, env)))
		{
			free(env->path);
			env->path = ft_strdup(path_exp);
		}
		env = env->next;
	}
	return (i);
}
