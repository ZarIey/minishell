/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recreate_and_exec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 10:07:12 by jcauchet          #+#    #+#             */
/*   Updated: 2022/08/23 23:24:21 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_p	*add_type_new(t_p **new)
{
	t_p	*nav;

	nav = *new;
	while (nav->next != *new)
	{
		nav->type = find_type(nav->str);
		nav = nav->next;
	}
	nav->type = find_type(nav->str);
	return (*new);
}

t_p	*free_new(t_p **new)
{
	free((*new));
	*new = NULL;
	return (NULL);
}

t_p	*new_parsed(t_p **parsed)
{
	t_p	*new;
	t_p	*nav;

	nav = *parsed;
	new = parsed_init();
	while (nav)
	{
		if (!is_redirection(nav) && nav->type != WHITE_SPACE
			&& nav->type != USELESS)
		{
			add_elmt_p(&new, nav->str);
			add_elmt_p(&new, " ");
		}
		nav = nav->next;
	}
	change_t_p(parsed, 0);
	free_parsed(parsed);
	if (new->str)
		add_type_new(&new);
	else
		return (free_new(&new));
	return (new);
}
