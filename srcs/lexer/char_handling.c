/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 13:12:45 by jcauchet          #+#    #+#             */
/*   Updated: 2022/08/21 17:38:35 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/***************************************************************************
All these functions check how many times there are successive tokens.
Then they concatenate them in a string and separate them from the rest
of the string.
***************************************************************************/
void	end_handler(t_l **elmt)
{
	if (g_glob->curr)
		add_elmt_l(elmt, g_glob->curr);
}

void	handle_quotes(char *args, t_l **elmt, int *i)
{
	if (g_glob->curr)
		add_elmt_l(elmt, g_glob->curr);
	g_glob->curr = append_char(g_glob->curr, args[*i]);
	add_elmt_l(elmt, g_glob->curr);
}

void	check_successive(char *args, int *i, int type)
{
	if (type == WHITE_SPACE)
		while ((args[*i] == ' ') || (args[*i] >= 9 && args[*i] <= 13))
			g_glob->curr = append_char(g_glob->curr, args[(*i)++]);
	else if (type == PIPE)
		while (args[*i] == '|')
			g_glob->curr = append_char(g_glob->curr, args[(*i)++]);
}

void	general_handler(char *args, t_l **elmt, int *i, int type)
{
	if (g_glob->curr)
		add_elmt_l(elmt, g_glob->curr);
	else
		g_glob->curr = append_char(g_glob->curr, args[(*i)++]);
	check_successive(args, i, type);
	add_elmt_l(elmt, g_glob->curr);
	(*i)--;
}

void	handle_chev(char *args, t_l **elmt, int *i)
{
	if (g_glob->curr)
		add_elmt_l(elmt, g_glob->curr);
	g_glob->curr = append_char(g_glob->curr, args[*i]);
	if (args[*i + 1] == args[*i])
	{
		g_glob->curr = append_char(g_glob->curr, args[*i + 1]);
		add_elmt_l(elmt, g_glob->curr);
		(*i)++;
	}
	else
		add_elmt_l(elmt, g_glob->curr);
}
