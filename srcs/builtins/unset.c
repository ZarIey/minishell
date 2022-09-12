/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 18:26:08 by ctardy            #+#    #+#             */
/*   Updated: 2022/08/26 17:11:42 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*add_c_path(char **argv, char *c_path)
{
	int	i;
	int	k;

	i = 2;
	k = i + 2;
	while (argv[i] && argv[k] && argv)
	{
		if (i == 2)
		{
			c_path = ft_strjoin(c_path, argv[i]);
			c_path = ft_strjoin(c_path, " ");
		}
		if (argv[k])
			c_path = ft_strjoin(c_path, argv[k]);
		c_path = ft_strjoin(c_path, " ");
		i += 2;
		k = i + 2;
	}
	return (c_path);
}

char	*unset_setup(char **argv)
{
	t_list	*list;
	char	*c_path;

	c_path = NULL;
	list = g_glob->env;
	if (!argv[1])
		return (NULL);
	if (!argv[4] && argv[2])
	{
		c_path = argv[2];
		return (c_path);
	}
	c_path = add_c_path(argv, c_path);
	return (c_path);
}

char	*return_name_unset(char *c_path)
{
	char	*name;
	int		i;
	int		equal;

	equal = 0;
	i = 0;
	while (c_path[i] && c_path[i] != 32)
		i++;
	if (c_path[i] == 32)
		equal = 1;
	if (equal == 1)
	{
		name = ft_substr(c_path, 0, i);
		return (name);
	}
	name = ft_substr(c_path, 0, i + 1);
	return (name);
}

void	unset_free_util(char **many_arg, char *c_path)
{
	free_tab(many_arg);
	free(c_path);
}

int	unset_error(char **tab)
{
	if (tab[2])
	{
		if (tab[2][0] == '-')
		{
			printf("minishell: unset: options are not handled\n");
			g_glob->code = 1;
			return (1);
		}
	}
	g_glob->code = 0;
	return (0);
}

void	unset_(char **argv, int size, char **tab)
{
	char	*name_export;
	char	*c_path;
	char	**many_arg;
	int		i;

	if (unset_error(tab))
		return ;
	c_path = unset_setup(argv);
	if (!c_path)
		return ;
	size = 0;
	i = 0;
	many_arg = ft_split(c_path, ' ');
	while (many_arg[i])
	{
		name_export = return_name_unset(&c_path[size]);
		check_existing_unset(name_export, "", 0);
		size += ft_strlen(name_export) + 1;
		free(name_export);
		i++;
	}
	if (!argv[4])
		free_tab(many_arg);
	else
		unset_free_util(many_arg, c_path);
}
