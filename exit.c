/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctardy <ctardy@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:47:59 by ctardy            #+#    #+#             */
/*   Updated: 2022/07/12 13:53:12 by ctardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/***************************************************************************
Gestion des non numeric, too many arg
***************************************************************************/

void verif_arg(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc > 3)
		printf("exit: too many arguments\n");
	while (argv[1][i])
	{
		if (argv[1][i] < 48 || argv[1][i] > 57)
		{
			printf("exit: %s: numeric argument required\n", argv[1]);
			exit(0);
		}
		i++;		
	}
}

void	exit_(int argc, char **argv)
{
	int	n;

	verif_arg(argc, argv);
	n = ft_atoi(argv[1]);
	if (n && n < 255)
		exit(n);
	exit (0);
}

int	main(int argc, char **argv)
{
	exit_(argc, argv);
}
