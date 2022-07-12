/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctardy <ctardy@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 14:58:20 by ctardy            #+#    #+#             */
/*   Updated: 2022/07/12 12:19:19 by ctardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/***************************************************************************
Gestion des flags -n -nnnnnnn gestion du nombre, gestion des erreurs type
-nnn8nn
***************************************************************************/

int	is_valid(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == 'n')
			i++;
		else 
			return (1);
	}
	return (0);
}

int nbr_flag(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (ft_strncmp(argv[i], "-n\0", 3) == 0 || is_valid(argv[i]) == 0)
	{
		i++;
		j++;
	}
	return (j);
}

void	echo(int argc, char **argv)
{
	char	*echo;
	int		i;
	int		end;

	end = 0;
	if ((i = (nbr_flag(argv) + 1)) > 1)
		end = 1;
	while (i < argc)
	{	
		if (i == argc - 1)
		{
			echo = ft_strdup(argv[i++]);
			if (end == 1)
			{
				printf("%s", echo);
				exit (0);
			}
			printf("%s\n", echo);
			exit (0);
		}
		echo = ft_strdup(argv[i++]);
		printf("%s ", echo);
	}
}

// int main(int argc, char **argv)
// {
// 	echo(argc, argv);
// 	//printf("nbr de n : %d\n", j);
// 	//echo(argc, argv);
// }
