/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 10:02:10 by juliencauch       #+#    #+#             */
/*   Updated: 2022/08/26 16:29:57 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_elmt_p(t_p **parsed, char *str)
{
	t_p	*head;
	t_p	*new;

	if (!(*parsed)->str)
	{
		(*parsed)->str = ft_strdup(str);
		return ;
	}
	new = malloc(sizeof(t_p));
	new->str = ft_strdup(str);
	if ((*parsed)->next == *parsed && (*parsed)->prev == *parsed)
	{
		new->next = *parsed;
		new->prev = *parsed;
		(*parsed)->next = new;
		(*parsed)->prev = new;
		return ;
	}
	head = *parsed;
	new->prev = head->prev;
	head->prev->next = new;
	head->prev = new;
	new->next = head;
}

void	add_elmt_type(t_p **parsed, char *str, int type)
{
	add_elmt_p(parsed, str);
	(*parsed)->prev->type = type;
}

void	check_valid_quote(int nav_type, int *d_quote, int *quote)
{
	if (nav_type == D_QUOTE && !(*quote % 2))
		(*d_quote)++;
	else if (nav_type == QUOTE && !(*d_quote % 2))
		(*quote)++;
}

int	check_missing_quote(t_l **elmt, t_p **parsed)
{
	int	quote;
	int	d_quote;
	t_l	*nav;

	quote = 0;
	d_quote = 0;
	nav = *elmt;
	while (nav->next != *elmt)
	{
		check_valid_quote(nav->type, &d_quote, &quote);
		nav = nav->next;
	}
	check_valid_quote(nav->type, &d_quote, &quote);
	if (d_quote % 2 || quote % 2)
	{
		g_glob->code = 258;
		printf("minishell: quote syntax error\n");
		free_lexed(elmt);
		free(*parsed);
		return (1);
	}
	else
		return (0);
}

int	quote_handling(t_l *elmt, t_p **parsed)
{
	t_l		*nav;

	nav = elmt;
	if (check_missing_quote(&elmt, parsed))
		return (FREE);
	while (nav->next != elmt)
	{
		if (nav->type == D_QUOTE || nav->type == QUOTE)
			find_next_quote(&nav, elmt, parsed);
		else if (nav->type != D_QUOTE && nav->type != USELESS)
			add_elmt_type(parsed, nav->str, nav->type);
		if (nav->next != elmt)
			nav = nav->next;
	}
	if (nav->type == D_QUOTE || nav->type == QUOTE)
		find_next_quote(&nav, elmt, parsed);
	else if (nav->type != D_QUOTE && nav->type != USELESS)
		add_elmt_type(parsed, nav->str, nav->type);
	return (CONTINUE);
}
