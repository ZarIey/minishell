/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 18:53:12 by jcauchet          #+#    #+#             */
/*   Updated: 2022/08/22 14:59:20 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	not_only_spaces(char *args)
{
	int	i;

	i = 0;
	if (!args)
		return (0);
	while (args[i])
	{
		if (args[i] != ' ' && (args[i] < 9 || args[i] > 13))
			return (1);
		i++;
	}
	return (0);
}

/***************************************************************************
This function checks input characters, one by one, and creates tokens to
separate in different part the input string. After that, the parser will
see if the newly created token string make sense or is bullshit.
***************************************************************************/
void	checker_type(char *args, t_l **elmt, int *i)
{
	if (args[*i] == '\0')
		end_handler(elmt);
	else if ((args[*i] == ' ') || (args[*i] >= 9 && args[*i] <= 13))
		general_handler(args, elmt, i, WHITE_SPACE);
	else if (args[*i] == '<' || args[*i] == '>')
		handle_chev(args, elmt, i);
	else if (args[*i] == '|')
		general_handler(args, elmt, i, PIPE);
	else if (args[*i] == '"' || args[*i] == '\'')
		handle_quotes(args, elmt, i);
	else
		g_glob->curr = append_char(g_glob->curr, args[*i]);
}

void	lexer(char *args)
{
	int		i;
	t_l		*elmt;
	char	*new_args;

	elmt = NULL;
	g_glob->curr = NULL;
	new_args = var_handling(args);
	if (!new_args)
		return ;
	i = -1;
	while (new_args[++i])
		checker_type(new_args, &elmt, &i);
	checker_type(new_args, &elmt, &i);
	if (!elmt)
	{
		free(new_args);
		return ;
	}
	parser(elmt);
	free(new_args);
}
