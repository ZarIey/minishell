/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctardy <ctardy@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 04:25:19 by jcauchet          #+#    #+#             */
/*   Updated: 2022/08/26 08:38:01 by ctardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*export_d_quote(char **argv)
{
	char	*c_path;

	c_path = NULL;
	c_path = ft_strjoin(c_path, argv[2]);
	c_path = ft_strjoin(c_path, argv[3]);
	return (c_path);
}

t_list	*check_name(t_list *new_lst)
{
	if (new_lst->name[0] < 65)
		new_lst->print = 0;
	return (new_lst);
}

int	check_equal(char *c_path)
{
	int	i;

	i = 0;
	if (!c_path)
		return (1);
	while (c_path[i])
	{
		if (c_path[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

char	*export_setup(char **argv)
{
	char	*c_path;

	c_path = NULL;
	if (!argv[1])
		return (NULL);
	if (!argv[4] && argv[3])
		return (export_d_quote(argv));
	if (!argv[4] && argv[2])
	{
		c_path = argv[2];
		return (c_path);
	}
	c_path = add_c_path(argv, c_path);
	return (c_path);
}

void	init_index(t_list *list)
{
	t_list	*sorted;
	t_list	*delete;

	sorted = list;
	delete = sorted;
	while (sorted)
	{
		delete = sorted;
		sorted->index = -1;
		sorted = sorted->next_sort;
		delete->next_sort = NULL;
	}
}
