/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utlis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctardy <ctardy@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 19:10:26 by ctardy            #+#    #+#             */
/*   Updated: 2022/06/27 19:14:22 by ctardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_list(t_list *list)
{
	t_list	*fake;

	fake = list;
	while (fake)
	{
		//printf("%d ", fake->index);
		printf("%s", fake->head);
		printf("%s", fake->name);
		printf("%c", fake->linker);
		printf("%s\n", fake->path);
		fake = fake->next_sort;
	}
}

char	*return_name(char *complet_path)
{
	char	*name;
	int		i;

	i = 0;
	while (complet_path[i] != '=')
		i++;
	i--;
	if (complet_path[i] != '+')
	{
		name = ft_substr(complet_path, 0, i);
		return (name);
	}
	name = ft_substr(complet_path, 0, i - 1);
	return (name);
}

char	*return_path(char *complet_path)
{
	char	*path;
	int		i;

	i = 0;
	while (complet_path[i] != '=')
		i++;
	path = ft_substr(complet_path, i + 1, ft_strlen(complet_path));
	return (path);
}

char	*clean_path(char *path)
{
	char	*clean_path;

	clean_path = ft_substr(path, 1, (ft_strlen(path) - 2));
	return (clean_path);
}
