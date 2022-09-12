/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctardy <ctardy@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 07:37:12 by ctardy            #+#    #+#             */
/*   Updated: 2022/08/26 07:42:00 by ctardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_and_sort(t_list *new_lst, t_list *new_lst_sorted)
{
	ft_lstadd_back(&g_glob->env, new_lst);
	ft_lstadd_back(&g_glob->env_sorted, new_lst_sorted);
	sort_list(&g_glob->env_sorted);
	init_rank(g_glob->env_sorted);
}

char	*free_and_dup(char *to_be_freed, char *new)
{
	free(to_be_freed);
	return (ft_strdup(new));
}
