/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 01:17:18 by jcauchet          #+#    #+#             */
/*   Updated: 2022/08/26 17:39:17 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid(char *str)
{
	int	i;

	i = 1;
	if (!str[i])
		return (1);
	while (str[i])
	{
		if (str[i] == 'n')
			i++;
		else
			return (1);
	}
	return (0);
}

int	check_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] == 32)
		i++;
	return (i);
}

int	check_arg(int argc, int nbr_flag)
{
	if (argc == nbr_flag)
		return (0);
	return (1);
}

int	only_flag(char **argv)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (argv[i])
	{
		if ((!ft_strncmp(argv[i], "-n\0", 3) || !is_valid(argv[i])))
			count++;
		i++;
	}
	count *= 2;
	count++;
	if (i == count)
		return (1);
	return (0);
}
