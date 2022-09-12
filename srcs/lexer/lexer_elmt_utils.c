/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_elmt_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:06:58 by jcauchet          #+#    #+#             */
/*   Updated: 2022/08/21 17:41:35 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_l	*create_new_elmt(char *str)
{
	t_l	*new;

	new = malloc(sizeof(t_l));
	if (!new)
		return (NULL);
	new->str = ft_strdup(str);
	new->type = find_type(str);
	free(g_glob->curr);
	g_glob->curr = NULL;
	return (new);
}

t_l	*add_elmt_l(t_l **elmt, char *str)
{
	t_l	*head;
	t_l	*new;

	if (!*elmt)
	{
		*elmt = create_new_elmt(str);
		(*elmt)->next = *elmt;
		(*elmt)->prev = *elmt;
		return (*elmt);
	}
	new = create_new_elmt(str);
	if ((*elmt)->next == *elmt && (*elmt)->prev == *elmt)
	{
		new->next = *elmt;
		new->prev = *elmt;
		(*elmt)->next = new;
		(*elmt)->prev = new;
		return (*elmt);
	}
	head = *elmt;
	new->prev = head->prev;
	head->prev->next = new;
	head->prev = new;
	new->next = head;
	return (*elmt);
}
