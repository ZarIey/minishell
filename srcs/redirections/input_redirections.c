/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 21:24:50 by jcauchet          #+#    #+#             */
/*   Updated: 2022/08/20 14:19:27 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	open_file(t_p **nav, t_fd *fds)
{
	fds->curr_fd = open((*nav)->str, O_RDONLY, 0777);
	(*nav)->type = USELESS;
	if (fds->curr_fd < 0)
	{
		printf("minishell: %s: no such file or directory\n", (*nav)->str);
		fds->curr_fd = -2;
	}
}

int	refresh_fds(t_fd *fds)
{
	if (fds->fd_in > -1)
	{
		close(fds->fd_in);
		unlink(".tmp");
	}
	fds->type = L_CHEV;
	fds->fd_in = fds->curr_fd;
	return (STOP);
}

void	input_handler(t_p **parsed, t_fd *fds, int i)
{
	t_p	*nav;
	int	j;
	int	type;

	j = 0;
	nav = *parsed;
	while (nav)
	{
		if (nav->type == L_CHEV || nav->type == L_CHEV_L)
		{
			type = nav->type;
			nav = nav->next;
			if (nav->type == WHITE_SPACE)
				open_file(&nav->next, fds);
			else
				open_file(&nav, fds);
			if (j > i && type == L_CHEV_L)
				refresh_fds(fds);
			else
				close(fds->curr_fd);
		}
		j++;
		nav = nav->next;
	}
}
