/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:47:59 by ctardy            #+#    #+#             */
/*   Updated: 2022/08/26 17:40:10 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/***************************************************************************
Gestion des non numeric, too many arg
***************************************************************************/

void	verif_arg(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc > 3)
		printf("exit: too many arguments\n");
	while (argv[2][i])
	{
		if (argv[2][0 == '-' && argv[2][0] == 1 && !argv[2][3]])
			break ;
		if (argv[2][i] < 48 || argv[2][i] > 57)
			printf("exit: %s: numeric argument required\n", argv[1]);
		i++;
	}
}

int	exit_(int argc, char **argv)
{
	int	n;

	verif_arg(argc, argv);
	n = ft_atoi(argv[2]);
	if (n <= 255 && n > 0)
	{
		printf("exit\n");
		g_glob->code = n;
		exit(n);
	}
	else if (!n)
	{
		printf("exit\n");
		g_glob->code = 0;
		exit(0);
	}
	else
	{
		printf("exit\n");
		g_glob->code = 0;
		n %= 256;
		exit(n);
	}
}
