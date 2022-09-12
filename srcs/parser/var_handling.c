/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_in_q.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 21:21:00 by jcauchet          #+#    #+#             */
/*   Updated: 2022/08/08 12:52:59 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*var_expander(char *name)
{
	char	*expanded;
	t_list	*nav;

	nav = g_glob->env;
	expanded = NULL;
	while (nav)
	{
		if (ft_strlen(name) == ft_strlen(nav->name)
			&& !ft_strncmp(name, nav->name, ft_strlen(name)))
			expanded = ft_strdup(nav->path);
		nav = nav->next;
	}
	if (!expanded)
	{
		free(name);
		return (ft_strdup(""));
	}
	else
	{
		free(name);
		return (expanded);
	}
}

char	*retrieve_var(int *i, char *args, char *curr)
{
	char	*var;
	char	*new;

	var = NULL;
	new = NULL;
	(*i)++;
	while (ft_isalnum(args[*i]))
		var = ft_strjoin_char(var, args[(*i)++]);
	var = var_expander(var);
	new = ft_strjoin_df(new, var);
	(*i)--;
	return (ft_strjoin_df(curr, new));
}

char	*special_var_handling(int *i, char *new, char c)
{
	char	*tmp;
	char	*ret;

	if (c == '$')
	{
		(*i)++;
		return (ft_strjoin(new, "$$"));
	}
	(*i)++;
	tmp = ft_itoa(g_glob->code);
	ret = ft_strjoin(new, tmp);
	free(tmp);
	return (ret);
}

char	*var_handling(char *args)
{
	int		i;
	char	*new;
	int		in_q;

	in_q = 0;
	new = NULL;
	i = -1;
	while (args[++i])
	{
		if (args[i] == '\'')
			in_q++;
		if (args[i] == '$' && in_q % 2 == 0)
		{
			if (args[i + 1] == '$' || args[i + 1] == '?')
				new = special_var_handling(&i, new, args[i + 1]);
			else if (ft_isalnum(args[i + 1]))
				new = retrieve_var(&i, args, new);
			else
				new = ft_strjoin_char(new, args[i]);
		}
		else
			new = ft_strjoin_char(new, args[i]);
	}
	return (new);
}
