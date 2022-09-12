/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:20:54 by jcauchet          #+#    #+#             */
/*   Updated: 2022/08/24 12:21:08 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_path(char *str)
{
	t_list	*nav;

	nav = g_glob->env;
	while (nav)
	{
		if (!ft_strncmp(str, nav->name, 4) && ft_strlen(nav->name) == 4)
			return (ft_strdup(nav->path));
		nav = nav->next;
	}
	return (NULL);
}
