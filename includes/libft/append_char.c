/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:24:38 by jcauchet          #+#    #+#             */
/*   Updated: 2022/08/21 17:37:52 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*append_char(char *str, char c)
{
	char	*new;
	int		len;
	int		i;

	len = ft_strlen(str);
	i = -1;
	if (!str)
	{
		new = malloc(sizeof(char) * 2);
		new[0] = c;
		new[1] = '\0';
		return (new);
	}
	new = malloc(len + 2);
	while (str[++i])
		new[i] = str[i];
	new[i++] = c;
	new[i] = 0;
	free(str);
	return (new);
}
