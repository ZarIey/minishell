/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 14:08:19 by jcauchet          #+#    #+#             */
/*   Updated: 2022/08/18 22:19:17 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	change_t_p(t_p	**parsed, int i)
{
	t_p	*nav;

	if (i)
	{
		(void)nav;
		(*parsed)->prev->next = NULL;
		(*parsed)->prev = NULL;
	}
	else
	{
		nav = *parsed;
		while (nav->next)
			nav = nav->next;
		nav->next = *parsed;
		(*parsed)->prev = nav;
	}
}

t_fd	mem_fds(void)
{
	return ((t_fd){dup(0), dup(1), dup(2), -2, -2, -2, 0});
}

void	find_last_r(t_p **parsed, int type)
{
	t_p		*nav;
	int		new_type;

	if (type == L_CHEV)
		new_type = L_CHEV_L;
	else if (type == R_CHEV)
		new_type = R_CHEV_L;
	else if (type == R_DCHEV)
		new_type = R_DCHEV_L;
	else
		new_type = L_DCHEV_L;
	nav = (*parsed)->prev;
	while (nav != *parsed)
	{
		if ((int)nav->type == type)
		{
			nav->type = new_type;
			return ;
		}
		nav = nav->prev;
	}
	if ((int)nav->type == type)
		nav->type = new_type;
}

void	redirections_setup(t_p **parsed)
{
	find_last_r(parsed, L_CHEV);
	find_last_r(parsed, R_CHEV);
	find_last_r(parsed, L_DCHEV);
	find_last_r(parsed, R_DCHEV);
}

int	check_if_hd(t_p **parsed)
{
	t_p	*nav;

	nav = *parsed;
	while (nav->next != *parsed)
	{
		if (nav->type == L_DCHEV)
			return (1);
		nav = nav->next;
	}
	if (nav->type == L_DCHEV)
		return (1);
	return (0);
}
