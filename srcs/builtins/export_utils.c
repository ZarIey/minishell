/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctardy <ctardy@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 19:10:26 by ctardy            #+#    #+#             */
/*   Updated: 2022/08/26 09:38:24 by ctardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*return_name(char *c_path)
{
	char	*name;
	int		i;
	int		equal;

	equal = 0;
	i = 0;
	while (c_path[i] && c_path[i] != '=' && c_path[i] != 32)
		i++;
	if (c_path[i] == '=')
		equal = 1;
	if (equal == 1)
	{
		if (!c_path[i + 1] || c_path[i + 1] == 32)
			return (name = ft_substr(c_path, 0, i + 1));
		name = ft_substr(c_path, 0, i);
		return (name);
	}
	name = ft_substr(c_path, 0, i);
	return (name);
}

char	*return_path(char *c_path)
{
	char	*path;
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (c_path[size] && c_path[size] != 32)
		size++;
	while (c_path[i] && c_path[i] != '=')
		i++;
	if (c_path[i] == '=')
	{
		path = ft_substr(c_path, i + 1, size - i);
		return (path);
	}
	return (ft_strdup(""));
}

char	*clean_path(char *path)
{
	char	*clean_path;

	clean_path = ft_substr(path, 1, (ft_strlen(path) - 2));
	return (clean_path);
}

int	comp(char *name_exp, t_list *list)
{
	int		i;
	char	*compare;

	if (!list)
		return (1);
	i = 0;
	compare = list->name;
	if (ft_strlen(name_exp) > ft_strlen(list->name))
		compare = name_exp;
	i = ft_strlen(compare);
	return (i);
}

char	*delete_equal(char	*name)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = ft_strlen(name);
	str = malloc(sizeof(char) * j);
	j -= 1;
	while (i < j)
	{
		str[i] = name[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
