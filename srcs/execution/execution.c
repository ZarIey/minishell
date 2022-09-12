/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 13:54:42 by ctardy            #+#    #+#             */
/*   Updated: 2022/08/26 17:57:34 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error(void)
{
	perror("Error");
}

char	*find_list_path(char **env_pers)
{
	char	*path;
	int		i;
	
	i = 0;
	while (env_pers[i])
	{
		if (!ft_strncmp(env_pers[i], "PATH", 4))
			path = ft_strdup(env_pers[i]);	
		i++;
	}
	return(path);
}

char	*find_access_path(char **all_path, char *exec)
{
	char	*select_path;
	char	*final_path;
	int		i;

	i = 0;
	i = 0;
	while (all_path[i])
	{
		select_path = strjoin_without_free(all_path[i], "/");
		final_path = ft_strjoin(select_path, exec);
		if (access(final_path, F_OK) == 0)
			return (final_path);
		free(final_path);
		i++;
	}
	return (final_path);
}

char	*path_helper(char *path)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = ft_strlen(path);
	str = malloc(sizeof(char) * j);
	j -= 1;
	while (i < j)
	{
		str[i] = path[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*cmd_path(char *exec, char **env_pers)
{
	char	**all_path;
	char	*path;
	char	*final_path;
	int		i;

	i = 0;
	path = find_list_path(env_pers);
	all_path = ft_split(path + 5, ':');
	while (all_path[i])
		i++;
	if (i == 1)
		all_path[0] = path_helper(all_path[0]);
	final_path = find_access_path(all_path, exec);
	i = 0;
	while (all_path[++i])
		free(all_path[i]);
	free(all_path);
	return (final_path);
}

int	cmd_exec(char **cmd, char **env_pers)
{
	char	*path;
	int		i;
		
	i = 0;
	i = size_tab(cmd);
	path = cmd_path(cmd[0], env_pers);
	if (!path)
	{
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		error();
	}
	if (execve(path, cmd, env_pers) == -1)
		error();
	return (0);
}

void	child_fork(char **cmd, char **env_pers)
{
	cmd_exec(cmd, env_pers);
	exit(0);
}

void	set_escape_handling(void)
{
	char	**tab;
	int		id;
	
	if (!g_glob->env)
		return ;
	tab = ft_split("/bin/stty echoctl", ' ');
	g_glob->stty = -42;
	id = fork();
	if (!id)
	{
		execve(tab[0], &tab[0], NULL);
		exit(0);
	}
	waitpid(0, NULL, 0);
	free_tab(tab);
}

void	unset_escape_handling(void)
{
	char	**tab;
	int		id;
		
	if (!g_glob->env)
		return ;
	tab = ft_split("/bin/stty -echoctl", ' ');
	g_glob->stty = 0;
	id = fork();
	if (!id)
	{
		execve(tab[0], &tab[0], NULL);
		exit(0);
	}
	waitpid(0, NULL, 0);
	free_tab(tab);
}

int cmd_main(char **cmd, char **env_pers)
{
	int	id;
	int status;
	
	id = fork();
	if (id == -1)
		error();
	if (id)
		g_glob->code = 137 + SIGKILL;
	if (id == 0)
		child_fork(cmd, env_pers);
	waitpid(0, &status, 0);
	g_glob->code = exit_code(status);
	return (0);
}
