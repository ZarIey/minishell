/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 20:51:05 by jcauchet          #+#    #+#             */
/*   Updated: 2022/08/23 01:25:05 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fake_heredoc(t_p **nav)
{
	char	*args;

	(*nav)->type = USELESS;
	while (1)
	{
		args = readline("> ");
		if (!args)
			break ;
		if (ft_strncmp((*nav)->str, args, ft_strlen((*nav)->str))
			&& ft_strlen(args) == ft_strlen((*nav)->str))
			break ;
		free(args);
	}
	free(args);
}

void	real_heredoc(t_p **nav, t_fd *fds)
{
	char	*args;

	(*nav)->type = USELESS;
	fds->fd_in = open(".tmp", O_RDWR | O_CREAT | O_APPEND, 0777);
	fds->type = L_DCHEV;
	while (1)
	{
		args = readline("> ");
		if (!args)
			break ;
		if (!ft_strncmp((*nav)->str, args, ft_strlen((*nav)->str))
			&& ft_strlen(args) == ft_strlen((*nav)->str))
			break ;
		ft_putstr_fd(args, fds->fd_in);
		ft_putstr_fd("\n", fds->fd_in);
		free(args);
	}
	free(args);
	close(fds->fd_in);
	fds->fd_in = open(".tmp", O_RDONLY, 0777);
}

void	open_heredoc(t_p **nav, t_fd *fds, int type)
{
	if (type == L_DCHEV)
		fake_heredoc(nav);
	else
		real_heredoc(nav, fds);
}

int	heredoc_handler(t_p **parsed, t_fd *fds)
{
	t_p	*nav;
	int	type;
	int	i;
	int	last;

	i = 0;
	last = -1;
	nav = *parsed;
	while (nav)
	{
		if (nav->type == L_DCHEV_L || nav->type == L_DCHEV)
		{
			type = (int)nav->type;
			nav = nav->next;
			last = i;
			if (nav->type == WHITE_SPACE)
				open_heredoc(&nav->next, fds, type);
			else
				open_heredoc(&nav, fds, type);
		}
		i++;
		nav = nav->next;
	}
	return (last);
}
