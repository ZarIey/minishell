/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 22:02:56 by jcauchet          #+#    #+#             */
/*   Updated: 2022/08/24 11:07:43 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_letter(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while ((str[i] >= 65 && str[i] <= 90)
			|| (str[i] >= 97 && str[i] <= 122))
			i++;
		if ((str[i] < 65 || str[i] > 90) && (str[i] < 97 || str[i] > 122))
			return (1);
	}
	return (0);
}

int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while ((str[i] >= 48 && str[i] <= 57))
			i++;
		if (!(str[i] >= 48 && str[i] <= 57))
			return (1);
	}
	return (0);
}

char	*name_checker(char *str)
{
	int		i;
	char	*clean_name;

	i = 0;
	while ((is_letter(str) && is_number(str)) || str[i] == '_')
	{
		i++;
		if (str[i] == '+')
		{
			i++;
			if (str[i] == '=')
			{
				clean_name = ft_substr(str, 0, (i - 2));
				return (clean_name);
			}
			exit (0);
		}
		return (str);
	}
	exit (0);
}

t_list	*ft_lstnew_void(void)
{
	t_list	*lst;

	lst = malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	lst->head = ft_strdup("");
	lst->name = ft_strdup("");
	lst->linker = '\0';
	lst->path = ft_strdup("");
	lst->print = 0;
	lst->next = NULL;
	lst->next_sort = NULL;
	return (lst);
}

t_list	*ft_lstnew(char *env_choosen, int size)
{
	t_list	*lst;
	int		size_env;
	char	*raw_name;

	size_env = ft_strlen(env_choosen);
	lst = malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	lst->head = ft_strdup("declare -x ");
	raw_name = ft_substr(env_choosen, 0, size);
	lst->name = name_checker(raw_name);
	lst->linker = '=';
	lst->path = ft_substr(env_choosen, size + 1, size_env);
	lst->print = 1;
	lst->next = NULL;
	lst->next_sort = NULL;
	return (lst);
}
