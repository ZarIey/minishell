/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctardy <ctardy@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 16:01:01 by ctardy            #+#    #+#             */
/*   Updated: 2022/06/27 18:16:16 by ctardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env(char **envi)
{
	int		i;

	i = 0;
	while (envi[i])
	{	
		printf("%s\n", envi[i]);
		i++;
	}
}

// int main(int argc, char **argv, char **envi)
// {
// 	(void) argc;
// 	(void) argv;
// 	env(envi);
// }
