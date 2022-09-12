/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_next_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 10:29:03 by jcauchet          #+#    #+#             */
/*   Updated: 2022/08/03 20:06:02 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_empty_d_quote(t_l **nav, t_p **parsed, t_l *elmt, int type)
{
	if ((int)(*nav)->type == type && (int)(*nav)->next->type == type)
	{
		*nav = (*nav)->next;
		add_elmt_p(parsed, "\0");
		if (type == D_QUOTE)
			(*parsed)->prev->type = IN_D_QUOTES;
		else
			(*parsed)->prev->type = IN_QUOTES;
		(*nav)->type = USELESS;
		(void)elmt;
		return (1);
	}
	return (0);
}

void	new_type(t_p **parsed, char *str, int type)
{
	add_elmt_p(parsed, str);
	free(str);
	if (type == D_QUOTE)
		(*parsed)->prev->type = IN_D_QUOTES;
	else
		(*parsed)->prev->type = IN_QUOTES;
}

void	find_next_quote(t_l **nav, t_l *elmt, t_p **parsed)
{
	char	*str;
	int		type;

	type = (*nav)->type;
	str = NULL;
	if (check_empty_d_quote(nav, parsed, elmt, type))
		return ;
	(*nav) = (*nav)->next;
	while ((int)(*nav)->next->type != type)
	{
		if (!str)
			str = ft_strdup((*nav)->str);
		else
			str = ft_strjoin(str, (*nav)->str);
		*nav = (*nav)->next;
	}
	if (!str)
		str = ft_strdup((*nav)->str);
	else
		str = ft_strjoin(str, (*nav)->str);
	*nav = (*nav)->next;
	(*nav)->type = USELESS;
	new_type(parsed, str, type);
}	
