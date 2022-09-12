/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:17:47 by ctardy            #+#    #+#             */
/*   Updated: 2022/08/25 01:45:53 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/***************************************************************************
Hi juju, it's Zarley there ! 🐊 This function take the evironnement in form
of char ** and fill a list create for. Cya ! 👋
***************************************************************************/

int	env_size(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (0);
	else if (!env[0])
		return (0);
	while (env[i])
		i++;
	return (i);
}

char	*get_user_ptr(void)
{
	t_list	*env;

	if (!g_glob->env_sorted)
		return (NULL);
	env = g_glob->env_sorted;
	if (!env)
		return (NULL);
	while (env)
	{
		if (!ft_strncmp(env->name, "USER", 4) && ft_strlen(env->name) == 4)
			return (env->path);
		env = env->next;
	}
	return (NULL);
}

t_list	*create_list(char *c_path)
{
	t_list	*first_lst;
	int		i;
	int		j;

	i = 0;
	while (c_path[i] != '=')
		i++;
	j = i;
	i = 0;
	first_lst = ft_lstnew(&c_path[i], j);
	return (first_lst);
}

void	return_list(char **env)
{
	if (!env[0])
	{
		g_glob->env = ft_lstnew_void();
		g_glob->env_sorted = ft_lstnew_void();
		g_glob->cur_path = NULL;
		return ;
	}
	g_glob->env = list_env(env, env_size(env));
	g_glob->env_sorted = list_env(env, env_size(env));
	g_glob->cur_path = NULL;
	sort_list(&g_glob->env_sorted);
	init_rank(g_glob->env_sorted);
}
