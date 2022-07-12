/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctardy <ctardy@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:17:47 by ctardy            #+#    #+#             */
/*   Updated: 2022/06/24 16:35:40 by ctardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/***************************************************************************
Hi juju, it's Zarley there ! 🐊 This function take the evironnement in form
of char ** and fill a list create for. Cya ! 👋
***************************************************************************/

t_global	*g_global;

int	env_size(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

t_list	*list_env(char **env, int size_env)
{
	t_list	*first_lst;
	t_list	*lst_inter;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < size_env)
	{
		while (env[i][j] != '=')
			j++;
		if (i == 0)
		{
			first_lst = ft_lstnew(env[i], j);
			j = 0;
			i++;
			continue ;
		}
		lst_inter = ft_lstnew(env[i], j);
		ft_lstadd_back(&first_lst, lst_inter);
		j = 0;
		i++;
	}
	return (first_lst);
}

void	init_rank(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst->index = i++;
		lst = lst->next_sort;
	}
}


void	swap_list(t_list **previous_next, t_list *last)
{
	t_list	*swap;

	swap = *previous_next;
	*previous_next = last->next_sort;
	swap->next_sort = last->next_sort->next_sort;
	(*previous_next)->next_sort = swap;
}

t_list	*sort_list(t_list **pstack_a)
{
	t_list	*last;
	t_list	*prev;

	prev = NULL;
	last = *pstack_a;
	while (last && last->next_sort)
	{
		if (ft_strncmp(last->name, last->next_sort->name, 3) > 0)
		{
			if (prev == NULL)
				swap_list(pstack_a, last);
			else
				swap_list(&(prev->next_sort), last);
			last = *pstack_a;
			prev = NULL;
		}
		else
		{
			prev = last;
			last = last->next_sort;
		}
	}
	return (*pstack_a);
}

void	return_list(char **env)
{
	t_list	*list;

	g_global = malloc(sizeof(t_global));
	g_global->env = list_env(env, env_size(env));
	list = (g_global->env);
	g_global->env = sort_list(&list);
	init_rank(g_global->env);
}

// int main(int argc, char **argv, char **env)
// {
// 	(void)argc;
// 	(void)argv;
// 	return_list(env);
// 	print_list(g_global->env);
// }
