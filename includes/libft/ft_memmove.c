/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 17:12:26 by jcauchet          #+#    #+#             */
/*   Updated: 2022/06/10 18:29:06 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*source;
	char	*destination;
	int		i;

	source = (char *)src;
	destination = (char *)dst;
	if (!destination)
		return (NULL);
	i = -1;
	if (destination > source)
	{
		len--;
		while (len >= 0 && (int)len < ft_strlen(destination)
			&& (int)len < ft_strlen(source))
		{
			destination[len] = source[len];
			len--;
		}
	}
	else
		while (i++ < (int)len - 1)
			destination[i] = source[i];
	return (dst);
}
