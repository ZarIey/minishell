/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctardy <ctardy@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 18:26:08 by ctardy            #+#    #+#             */
/*   Updated: 2022/06/27 19:51:10 by ctardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*get_last(t_list *lst_env)
{
	t_list	*inter;

	inter = lst_env;
	if (inter == NULL)
		return (NULL);
	while (inter->next)
		inter = inter->next;
	return (inter);
}

void free_list(t_list *lst)
{
		free(lst->head);
		free(lst->name);
		//free(lst->linker);			
		free(lst->path);
		free(lst->next);
		free(lst);
}

void	unset(char *str, t_list *lst_env)
{
	t_list	*precedent;
	t_list	*next;

	int i = 1;
	precedent = get_last(lst_env);
	while (lst_env)
	{
		printf("lst_env->name -------%s\n", lst_env->name);
		if (ft_strncmp(lst_env->name, str, ft_strlen(str)) == 0)
		{
			printf("Je rentre pour la %ieme fois", i);
			precedent->next = lst_env->next;
			// if (!lst_env->next)
			// 	precedent->next = NULL;
			free_list(lst_env);
		}
		i++;
		precedent = lst_env;
		lst_env = lst_env->next;
		next = lst_env->next;
	}
}

// gccw includes/minishell.h includes/libft/*.c list_env.c srcs/builtins/export_utlis.c srcs/builtins/unset.c


int main (int argc, char **argv, char **env)
{
	int	env_size(char **env);
	
	(void) argc;
	g_global = malloc(sizeof(t_global));
	g_global->env = list_env(env, env_size(env));
	print_list(g_global->env);
	unset(argv[1], g_global->env);
	print_list(g_global->env);
}
