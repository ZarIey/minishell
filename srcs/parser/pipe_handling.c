/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 09:11:06 by jcauchet          #+#    #+#             */
/*   Updated: 2022/08/26 16:30:19 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pipe_handling(t_p **parsed)
{
	t_p	*nav;

	nav = *parsed;
	while (nav->next != *parsed)
	{
		if (nav->type == PIPE)
		{
			free_parsed(parsed);
			g_glob->code = 258;
			printf("Error: Minishell Sardou doesn't handle pipes\n");
			return (FREE);
		}
		nav = nav->next;
	}	
	if (nav->type == PIPE)
	{
		free_parsed(parsed);
		printf("Error: Minishell Sardou doesn't handle pipes\n");
		return (FREE);
	}
	return (CONTINUE);
}
