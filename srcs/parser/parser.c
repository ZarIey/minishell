/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:15:56 by jcauchet          #+#    #+#             */
/*   Updated: 2022/08/25 13:39:31 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_lexed(t_l **lexed)
{
	t_l	*nav;
	t_l	*tmp;

	if (!*lexed)
		return ;
	if (!(*lexed)->str)
	{
		free(lexed);
		return ;
	}
	nav = (*lexed)->next;
	while (nav != *lexed)
	{
		tmp = nav->next;
		free(nav->str);
		free(nav);
		nav = tmp;
	}
	free(nav->str);
	free(nav);
}

void	free_parsed(t_p **parsed)
{
	t_p	*nav;
	t_p	*tmp;

	if (!*parsed)
		return ;
	if (!(*parsed)->str)
	{
		free(parsed);
		return ;
	}
	nav = (*parsed)->next;
	while (nav != *parsed)
	{
		tmp = nav->next;
		free(nav->str);
		free(nav);
		nav = tmp;
	}
	free(nav->str);
	free(nav);
}

t_p	*parsed_init(void)
{
	t_p	*parsed;

	parsed = malloc(sizeof(t_p));
	if (!parsed)
		return (NULL);
	parsed->str = NULL;
	parsed->next = parsed;
	parsed->prev = parsed;
	return (parsed);
}

/***************************************************************************
Main function to parse arguments and make the right behaviour.
***************************************************************************/
void	parser(t_l *elmt)
{
	t_p		*parsed;

	g_glob->q_type = 0;
	parsed = parsed_init();
	if (quote_handling(elmt, &parsed) == FREE)
		return ;
	if (pipe_handling(&parsed) == FREE)
	{
		free_lexed(&elmt);
		return ;
	}
	q_tokens_handler(&parsed);
	unlink(".tmp");
	redirections(&parsed);
	free_parsed(&parsed);
	free_lexed(&elmt);
}
