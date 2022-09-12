/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_errors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 10:11:41 by jcauchet          #+#    #+#             */
/*   Updated: 2022/08/20 14:21:34 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redirection(t_p *nav)
{
	if (!nav)
		return (0);
	if (nav->type == L_CHEV || nav->type == R_CHEV
		|| nav->type == L_DCHEV || nav->type == R_DCHEV
		|| nav->type == L_CHEV_L || nav->type == R_CHEV_L
		|| nav->type == L_DCHEV_L || nav->type == R_DCHEV_L)
		return (1);
	else
		return (0);
}

int	check_r_alone(t_p **parsed)
{
	t_p	*nav;
	int	i;

	nav = *parsed;
	i = 0;
	while (nav->next != *parsed)
	{
		if (nav->type != WHITE_SPACE && !is_redirection(nav))
			i = 1;
		nav = nav->next;
	}
	if (nav->type != WHITE_SPACE && !is_redirection(nav))
		i = 1;
	if (!i)
	{
		printf("minishell: redirection syntax error\n");
		return (STOP);
	}
	else
		return (CONTINUE);
}

int	check_r_end(t_p **parsed)
{
	t_p	*nav;

	nav = *parsed;
	if (is_redirection(nav->prev))
	{
		printf("minishell: redirection syntax error\n");
		return (STOP);
	}
	else if (nav->prev->type == WHITE_SPACE && is_redirection(nav->prev->prev))
	{
		printf("minishell: redirection syntax error\n");
		return (STOP);
	}
	return (CONTINUE);
}

int	check_r_double(t_p **parsed)
{
	t_p	*nav;

	nav = *parsed;
	while (nav->next != *parsed)
	{
		if ((is_redirection(nav) && is_redirection(nav->next))
			|| (is_redirection(nav) && ((is_redirection(nav->next->next))
					&& nav->next->type == WHITE_SPACE)))
		{
			printf("minishell: redirection syntax error\n");
			return (STOP);
		}
		nav = nav->next;
	}
	if ((is_redirection(nav) && is_redirection(nav->next))
		|| (is_redirection(nav) && ((is_redirection(nav->next->next))
				&& nav->next->type == WHITE_SPACE)))
	{
		printf("minishell: redirection syntax error\n");
		return (STOP);
	}
	return (CONTINUE);
}

int	check_r_syntax(t_p **parsed)
{
	t_p	*nav;

	nav = *parsed;
	if (check_r_alone(parsed) == STOP)
		return (STOP);
	if (check_r_end(parsed) == STOP)
		return (STOP);
	if (check_r_double(parsed) == STOP)
		return (STOP);
	return (CONTINUE);
}
