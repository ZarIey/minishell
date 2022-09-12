/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 19:01:37 by jcauchet          #+#    #+#             */
/*   Updated: 2022/06/10 18:31:12 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t		i;
	size_t		j;
	size_t		len;

	i = 0;
	j = 0;
	while (i < dstsize && dst[i])
		i++;
	if (i == dstsize)
		return (i + ft_strlen(src));
	len = ft_strlen(src)+ ft_strlen(dst);
	while (src[j] && i < dstsize - 1)
		dst[i++] = (char)src[j++];
	dst[i] = 0;
	return (len);
}
