/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 16:01:01 by ctardy            #+#    #+#             */
/*   Updated: 2022/08/26 16:54:57 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_(t_list *env, char **tab)
{
	if (tab[2])
	{
		printf("minishell: env: options and arguments are not handled\n");
		g_glob->code = 1;
		return (1);
	}
	print_list_env(env);
	g_glob->code = 0;
	return (0);
}
