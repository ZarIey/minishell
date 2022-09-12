/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 18:23:33 by ctardy            #+#    #+#             */
/*   Updated: 2022/08/23 21:28:45 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	if (!tab[0])
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_list_end_2(t_list *env)
{
	t_list	*next;

	while (env)
	{
		next = env->next;
		free(env->head);
		free(env->name);
		free(env->path);
		free(env);
		env = next;
	}
}

void	free_list_end(t_list *l_env, t_list *l_sorted, int flag)
{
	t_list	*env;
	t_list	*next;

	env = l_env;
	if (flag == 0 || flag == 2)
	{
		while (env)
		{
			next = env->next;
			free(env->head);
			free(env->name);
			free(env->path);
			free(env);
			env = next;
		}
	}
	env = l_sorted;
	if (flag == 1 || flag == 2)
		free_list_end_2(env);
}
