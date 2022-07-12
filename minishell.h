/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:40:01 by jcauchet          #+#    #+#             */
/*   Updated: 2022/06/15 18:29:25 jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "../includes/libft/libft.h"
# include "../includes/gnl/get_next_line.h"

# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <signal.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

# define CONTINUE	2
# define STOP		3

extern struct global *g_global;

typedef struct global
{
	t_list	*env;
	char	*prompt;
}	t_global;

// Zarley's part
void	print_list(t_list *list);

char	*make_path(char *s2);
t_list *sort_list(t_list **pstack_a);
t_list	*list_env(char **env, int size_env);
void	return_list(char **env);
char	*add_on_path(char *complet_path, char *path_export, char *saved_path);
char	*return_name(char *complet_path);
char	*return_path(char *complet_path);
char	*clean_path(char *path);

// Prompt functions

char	*create_prompt(void);

// Signal functions

void	ctrl_c(int sig);
void	ctrl_bs(int sig);
void	signal_init(void);

// Parsing functions

void	parsing(char *args);

// Builtin functions

void	ft_pwd(void);

// Command functions (execve)

void	execute_commands(char *args);

#endif
