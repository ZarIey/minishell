/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 01:50:15 by jcauchet          #+#    #+#             */
/*   Updated: 2022/08/26 16:51:33 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pwd_(char **tab)
{
	char	cwd[1024];

	if (tab[2])
	{
		if (tab[2][0] == '-')
		{
			printf("minishell: pwd: options are not handled\n");
			g_glob->code = 1;
			return (1);
		}
	}
	printf("%s\n", getcwd(cwd, sizeof(cwd)));
	g_glob->code = 0;
	return (0);
}

char	*check_current(void)
{
	char	here[1024];
	char	*current;

	getcwd(here, 1024);
	current = ft_strdup(here);
	return (current);
}
