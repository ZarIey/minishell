/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 17:57:27 by juliencauch       #+#    #+#             */
/*   Updated: 2022/08/23 14:33:12 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		len;
	int		i;
	int		j;
	char	*string;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	i = 0;
	j = 0;
	string = malloc(len * sizeof(char));
	if (!string)
		return (NULL);
	if (s1)
		while (s1[j])
			string[i++] = s1[j++];
	j = 0;
	while (s2[j])
		string[i++] = s2[j++];
	string[i] = '\0';
	free(s1);
	return (string);
}

char	*strjoin_without_free(char *s1, char *s2)
{
	int		len;
	int		i;
	int		j;
	char	*string;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	i = 0;
	j = 0;
	string = malloc(len * sizeof(char));
	if (!string)
		return (NULL);
	if (s1)
		while (s1[j])
			string[i++] = s1[j++];
	j = 0;
	while (s2[j])
		string[i++] = s2[j++];
	string[i] = '\0';
	return (string);
}

char	*ft_strjoin_char(char *str, char c)
{
	char	*new;
	int		i;

	if (!str)
	{
		new = malloc((sizeof(char)) * 2);
		new[0] = c;
		new[1] = '\0';
		return (new);
	}
	new = malloc(ft_strlen(str) + 2);
	i = 0;
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i++] = c;
	new[i] = '\0';
	free(str);
	return (new);
}

char	*ft_strjoin_df(char *s1, char *s2)
{
	int		len;
	int		i;
	int		j;
	char	*string;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	i = 0;
	j = 0;
	string = malloc(len * sizeof(char));
	if (!string)
		return (NULL);
	if (s1)
		while (s1[j])
			string[i++] = s1[j++];
	j = 0;
	while (s2[j])
		string[i++] = s2[j++];
	string[i] = '\0';
	free(s1);
	free(s2);
	s2 = NULL;
	return (string);
}

char	*join_christophe(char *str, char c)
{
	char	*new;
	int		i;

	if (!str)
	{
		new = malloc((sizeof(char)) * 2);
		new[0] = c;
		new[1] = '\0';
		return (new);
	}
	new = malloc(ft_strlen(str) + 2);
	i = 0;
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i++] = c;
	new[i] = '\0';
	return (new);
}
