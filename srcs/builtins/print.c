/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctardy <ctardy@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 16:07:09 by ctardy            #+#    #+#             */
/*   Updated: 2022/08/26 10:21:48 by ctardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_path(t_list *list)
{
	t_list	*lst;

	lst = list;
	if (ft_strlen(lst->path) >= 1 || lst->name[1] == '=' || lst->print == 2)
		return (1);
	return (0);
}

void	print_list_export(t_list *env)
{
	t_list	*l;
	char	q;

	(void)env;
	q = '"';
	l = g_glob->env_sorted;
	while (l)
	{
		if (l->print == 2)
			printf("%s%s%c%c%s%c\n", l->head, l->name, l->linker, q, l->path, q);
		else if (l->print == 1 && ft_strlen(l->path) < 1)
			printf("%s%s\n", l->head, l->name);
		else if (l->print == 1 && ft_strlen(l->name) == 1 && ft_strlen(l->path))
			printf("%s%s%c%c%s%c\n", l->head, l->name, l->linker, q, l->path, q);
		else if ((l->print == 1 && ft_strlen(l->name) == 1))
			printf("%s%s\n", l->head, l->name);
		else if (l->print == 1)
		{
			printf("%s%s", l->head, l->name);
			if (l->name[1] != '=')
				printf("%c", l->linker);
			printf("%c%s%c\n", q, l->path, q);
		}
		l = l->next;
	}
}

void	print_list_env(t_list *list)
{
	t_list	*l;

	l = list;
	while (l)
	{
		if (check_path(l))
		{
			if (l->print == 2)
				printf("%s%c\n", l->name, l->linker);
			else if (l->print == 1 || l->name[1] == '=')
			{
				printf("%s", l->name);
				if (l->name[1] != '=')
					printf("%c", l->linker);
				printf("%s\n", l->path);
			}
			else if (l->print == 1)
			{
				printf("%s", l->name);
				printf("%c", l->linker);
				printf("%s\n", l->path);
			}
		}
		l = l->next;
	}
}
