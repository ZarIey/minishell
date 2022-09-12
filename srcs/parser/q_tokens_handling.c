/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   q_tokens_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 14:07:16 by jcauchet          #+#    #+#             */
/*   Updated: 2022/08/10 14:57:06 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	q_tokens_handler(t_p **parsed)
{
	t_p	*nav;

	nav = *parsed;
	while (nav->next != *parsed)
	{
		if (nav->type == IN_QUOTES || nav->type == IN_D_QUOTES)
		{
			if (is_builtin(nav->str) && nav->str[0])
				nav->type = BUILTIN;
			else if (is_exec(nav->str) && nav->str[0])
				nav->type = EXEC;
		}
		nav = nav->next;
	}
	if (nav->type == IN_QUOTES || nav->type == IN_D_QUOTES)
	{
		if (is_builtin(nav->str) && nav->str[0])
			nav->type = BUILTIN;
		else if (is_exec(nav->str) && nav->str[0])
			nav->type = EXEC;
	}
}
