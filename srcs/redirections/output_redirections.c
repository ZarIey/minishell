/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 23:18:48 by jcauchet          #+#    #+#             */
/*   Updated: 2022/08/20 14:19:43 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redirect_to_file(t_p **nav, t_fd *fds, int type, int last)
{
	(*nav)->type = USELESS;
	if (type == R_CHEV || type == R_CHEV_L)
		fds->curr_fd = open((*nav)->str, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		fds->curr_fd = open((*nav)->str, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (type != last)
		close(fds->curr_fd);
	else
		fds->fd_out = fds->curr_fd;
}

int	which_one(t_p **parsed)
{
	t_p	*nav;
	int	type;

	type = -1;
	nav = *parsed;
	while (nav)
	{
		if (nav->type == R_CHEV_L)
			type = (int)R_CHEV_L;
		else if (nav->type == R_DCHEV_L)
			type = (int)R_DCHEV_L;
		nav = nav->next;
	}
	return (type);
}

void	output_handler(t_p **parsed, t_fd *fds)
{
	t_p	*nav;
	int	type;
	int	last;

	nav = *parsed;
	last = which_one(parsed);
	while (nav)
	{
		if (nav->type == R_CHEV || nav->type == R_CHEV_L
			|| nav->type == R_DCHEV || nav->type == R_DCHEV_L)
		{
			type = nav->type;
			nav = nav->next;
			if (nav->type == WHITE_SPACE)
				redirect_to_file(&nav->next, fds, type, last);
			else
				redirect_to_file(&nav, fds, type, last);
		}
		nav = nav->next;
	}
}
