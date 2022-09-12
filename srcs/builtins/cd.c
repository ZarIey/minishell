/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:35:28 by ctardy            #+#    #+#             */
/*   Updated: 2022/08/26 12:51:59 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_folder(char *current)
{
	int		i;
	int		slash;
	char	folder[1024];
	char	*clean_folder;

	i = 1;
	slash = 0;
	while (slash < 2)
	{
		while (current[i] != '/')
			i++;
		slash++;
		i++;
	}
	ft_strlcpy(folder, current, i + 1);
	clean_folder = ft_strdup(folder);
	return (clean_folder);
}

char	*prec_cd(char *current)
{
	int		i;
	char	prec[100];
	char	*clean_prec;

	i = ft_strlen(current);
	while (current[i] != 47)
		i--;
	ft_strlcpy(prec, current, i + 1);
	clean_prec = ft_strdup(prec);
	return (clean_prec);
}

char	*home_path(void)
{
	t_list	*inter;
	char	*home;

	inter = g_glob->env;
	while (inter)
	{
		if (!ft_strncmp(inter->name, "HOME", 4))
			home = inter->path;
		inter = inter->next;
	}
	return (home);
}

int	verif_crash(char *path)
{
	int		i;
	char	verif[11];

	i = 0;
	while (i < 10)
	{
		verif[i] = path[i];
		i++;
	}
	verif[i] = '\0';
	if (!ft_strncmp(path, "/.Trashes", 9))
		return (1);
	return (0);
}

int	cd_(char *path, char *current)
{
	g_glob->code = 0;
	if (path[0] == 126)
	{
		chdir(home_path());
		return (0);
	}
	if (verif_crash(current))
	{
		printf("unexpected error, redirected to $HOME path\n");
		chdir(home_path());
		return (0);
	}
	if (!path)
	{
		chdir(get_folder(current));
		return (0);
	}
	if (chdir(path) < 0)
	{
		printf("cd: no such file or directory: %s\n", path);
		g_glob->code = 1;
	}
	return (0);
}
