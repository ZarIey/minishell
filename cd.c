/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctardy <ctardy@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:35:28 by ctardy            #+#    #+#             */
/*   Updated: 2022/07/05 16:41:47 by ctardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	check_argv(char **argv)
// {
// 	int	i;
// 	char *str;

// 	i = 0;
// 	str = argv[2];
// 	if (!str)
// 		return(1);
// 	while (str[i] == '.' || str[i] == '/')
// 		i++;	
// 	return (0);
// }

void	cd(char **argv)
{
	// char	*str;

	// str = check_argv(argv[2]);
	if (chdir(argv[2]) == 0)
		return ;
}

// int main(int argc, char **argv)
// {

// }