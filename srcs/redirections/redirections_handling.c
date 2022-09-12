/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_handling.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 14:22:14 by jcauchet          #+#    #+#             */
/*   Updated: 2022/08/25 15:19:04 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_if_r(t_p **parsed)
{
	t_p	*nav;
	int	i;

	nav = *parsed;
	i = STOP;
	while (nav->next != *parsed)
	{
		if (is_redirection(nav))
			i = 1;
		nav = nav->next;
	}
	if (is_redirection(nav))
		i = 1;
	return (i);
}

void	reset_fds(t_fd *fds)
{
	if (fds->fd_in > -1)
		close(fds->fd_in);
	if (fds->fd_out > -1)
		close(fds->fd_out);
	dup2(fds->stdin_mem, STDIN_FILENO);
	dup2(fds->stdout_mem, STDOUT_FILENO);
	dup2(fds->stderr_mem, STDERR_FILENO);
	unlink(".tmp");
}

void	redirections(t_p **parsed)
{
	t_fd	fds;
	int		i;

	if (check_r_syntax(parsed) == STOP)
		return ;
	if (check_if_r(parsed) == STOP)
	{
		find_builtin(creation_argv(*parsed));
		return ;
	}
	fds = mem_fds();
	redirections_setup(parsed);
	change_t_p(parsed, 1);
	i = heredoc_handler(parsed, &fds);
	input_handler(parsed, &fds, i);
	if (fds.fd_in > -1)
		dup2(fds.fd_in, STDIN_FILENO);
	output_handler(parsed, &fds);
	if (fds.fd_out > -1)
		dup2(fds.fd_out, STDOUT_FILENO);
	*parsed = new_parsed(parsed);
	if (*parsed)
		find_builtin(creation_argv(*parsed));
	reset_fds(&fds);
}
