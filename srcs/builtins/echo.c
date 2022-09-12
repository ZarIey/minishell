/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 14:58:20 by ctardy            #+#    #+#             */
/*   Updated: 2022/08/26 17:38:23 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/***************************************************************************
Gestion des flags -n -nnnnnnn gestion du nombre, gestion des erreurs type
-nnn8nn
***************************************************************************/



int	nbr_flag(char **argv)
{
	int	i;
	int	j;

	i = 2;
	j = 0;
	if (!argv[1])
		return (j);
	while ((!ft_strncmp(argv[i], "-n\0", 3) || !is_valid(argv[i])))
	{
		i++;
		j++;
		if (argv[i][0] >= 33 && argv[i][0] <= 126)
			return (j - 1);
		while (check_space(argv[i]))
		{
			i++;
			j++;
		}
	}
	return (j);
}

void	echo_output(int *i, int *tab, char **argv, char *space)
{
	while (*i < tab[1] && argv[*i])
	{
		if (*i == tab[1] - 1)
		{
			if (tab[0] == 1)
			{
				space = argv[(*i)++];
				printf("%s", space);
				return ;
			}
			space = argv[(*i)++];
			printf("%s\n", space);
			return ;
		}
		space = argv[(*i)++];
		printf("%s", space);
	}
	if (tab[1] == 1)
		printf("\n");
}

int	echo_(int argc, char **argv)
{
	int		i;
	int		end;
	char	*space;

	space = NULL;
	end = 0;
	g_glob->code = 0;
	if (only_flag(argv))
		return (0);
	i = (nbr_flag(argv) + 1);
	if (i > 1)
		end = 1;
	i++;
	echo_output(&i, (int [2]){end, argc}, argv, space);
	return (0);
}
