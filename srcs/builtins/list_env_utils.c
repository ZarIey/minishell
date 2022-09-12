/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_env_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctardy <ctardy@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 22:10:28 by ctardy            #+#    #+#             */
/*   Updated: 2022/08/22 22:38:47 by ctardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*list_env(char **env, int size_env)
{
	t_list	*first_lst;
	t_list	*lst_inter;
	int		i;
	int		j;

	if (!size_env)
		return (NULL);
	i = -1;
	j = 0;
	while (++i < size_env)
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
	}
	return (first_lst);
}

void	init_rank(t_list *lst)
{
	t_list	*inter;
	int		i;

	inter = lst;
	i = 0;
	while (inter)
	{
		inter->index = i;
		i++;
		inter = inter->next;
	}
}

void	swap_list(t_list **previous_next, t_list *last)
{
	t_list	*swap;

	swap = *previous_next;
	*previous_next = last->next;
	swap->next = last->next->next;
	(*previous_next)->next = swap;
}

void	sort_list(t_list **pstack_a)
{
	t_list	*sorted;
	t_list	*last;
	t_list	*prev;

	prev = NULL;
	last = *pstack_a;
	sorted = *pstack_a;
	while (last && last->next)
	{
		if (ft_strncmp(last->name, last->next->name, ft_strlen(last->name)) > 0)
		{
			if (prev == NULL)
				swap_list(pstack_a, last);
			else
				swap_list(&(prev->next), last);
			last = *pstack_a;
			prev = NULL;
		}
		else
		{
			prev = last;
			last = last->next;
		}
	}
}
