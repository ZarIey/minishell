/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:33:30 by jcauchet          #+#    #+#             */
/*   Updated: 2022/08/26 17:09:50 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "../includes/libft/libft.h"

# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdbool.h>
# include <termios.h>
# include <fcntl.h>

# define NO			0
# define YES		1
# define CONTINUE	2
# define STOP		3
# define FREE		4

extern struct global	*g_glob;

typedef struct global
{
	t_list	*env;
	t_list	*env_sorted;
	char	*prompt;
	char	*curr;
	char	*cur_path;
	int		q_type;
	int		code;
	int		stty;
}	t_global;

typedef enum enum_type
{
	BUILTIN = 48,
	EXEC,
	DOLLAR,
	PIPE,
	R_CHEV,
	L_CHEV,
	R_DCHEV,
	L_DCHEV,
	QUOTE,
	D_QUOTE,
	TEXT,
	WHITE_SPACE,
	IN_D_QUOTES,
	OUT_D_QUOTES,
	IN_QUOTES,
	USELESS,
	R_CHEV_L,
	L_CHEV_L,
	R_DCHEV_L,
	L_DCHEV_L
}	t_enum_type;

typedef struct l
{
	char		*str;
	t_enum_type	type;
	struct l	*next;
	struct l	*prev;
}	t_l;

typedef struct p
{
	char		*str;
	t_enum_type	type;
	struct p	*next;
	struct p	*prev;
}	t_p;

typedef struct fd
{
	int			stdin_mem;
	int			stdout_mem;
	int			stderr_mem;
	int			fd_in;
	int			fd_out;
	int			curr_fd;
	t_enum_type	type;
}	t_fd;

// Signal functions

void		ctrl_c(int sig);
void		ctrl_bs(int sig);
void		signal_init(void);
int			exit_code(int status);

// Lexer functions

void		lexer(char *args);
t_l			*create_new_elmt(char *str);
t_l			*add_elmt_l(t_l **elmt, char *str);
t_enum_type	find_type(char *str);
void		handle_chev(char *args, t_l **elmt, int *i);
void		handle_quotes(char *args, t_l **elmt, int *i);
void		general_handler(char *args, t_l **elmt, int *i, int type);
void		end_handler(t_l **elmt);
int			is_builtin(char *str);
int			is_exec(char *str);
char		*var_handling(char *args);
void		free_lexed(t_l **lexed);

// Checker functions

int			not_only_spaces(char *args);

// Parsing functions

void		parser(t_l *elmt);
int			single_one(t_l *elmt);
int			is_pipe(t_l *elmt);
void		add_elmt_p(t_p **parsed, char *str);
int			quote_handling(t_l *elmt, t_p **parsed);
void		find_next_quote(t_l **nav, t_l *elmt, t_p **parsed);
void		free_parsed(t_p **parsed);
int			pipe_handling(t_p **parsed);
void		add_elmt_type(t_p **parsed, char *str, int type);
void		q_tokens_handler(t_p **parsed);
t_p			*parsed_init(void);

// Redirections functions

void		redirections(t_p **parsed);
int			check_r_syntax(t_p **parsed);
int			is_redirection(t_p *nav);
void		redirections_setup(t_p **parsed);
t_fd		mem_fds(void);
void		change_t_p(t_p	**parsed, int i);
int			heredoc_handler(t_p **parsed, t_fd *fds);
void		input_handler(t_p **parsed, t_fd *fds, int i);
void		output_handler(t_p **parsed, t_fd *fds);
t_p			*recreate_and_exec(t_p **parsed, int i);
t_p			*new_parsed(t_p **parsed);

// Builtin functions

char		*get_user_ptr(void);
int			comp(char *name_exp, t_list *list);
void		free_list_end(t_list *l_env, t_list *l_sorted, int flag);
void		free_tab(char **tab);
int			find_builtin(char **tab);
char		**creation_argv(t_p *lexer);
void		return_value(int return_comm);
int			builtin_action(t_p *lexer);
int			size_list(t_p *parsed);
int			echo_(int argc, char **argv);
int			cd_(char *path, char *current);
int			cd_arg(int argc, char **argv);
char		*home_path(void);
void		change_env(char *old, char *current);
int			env_(t_list *env, char **tab);
int			exit_(int argc, char **argv);
int			pwd_(char **tab);
int			export_(char **argv, int size);
int			size_tab(char **tab);
void		print_list_export(t_list *env);
void		unset_(char **argv, int size, char **tab);
int			is_arg(int type);
int			check_existing(char *name_export, char *path_export, int i);
int			check_existing_unset(char *name_exp, char *path_exp, int i);
void		print_list_env(t_list *list);
void		init_rank(t_list *lst);
void		print_list(t_list *list);
char		*make_path(char *s2);
void		sort_list(t_list **pstack_a);
t_list		*list_env(char **env, int size_env);
void		return_list(char **env);
char		*add_on_path(char *c_path, char *path_export, char *saved_path);
char		*return_name(char *c_path);
char		*return_path(char *c_path);
char		*clean_path(char *path);
char		*check_current(void);
int			only_flag(char **argv);
int			check_arg(int argc, int nbr_flag);
int			check_space(char *str);
int			is_valid(char *str);
int			check_equal(char *c_path);
char		*delete_equal(char	*name);
char		*add_c_path(char **argv, char *c_path);
char		*export_setup(char **argv);
char		*free_and_dup(char *to_be_freed, char *new);
void		add_and_sort(t_list *new_lst, t_list *new_lst_sorted);
void		add_list(char *c_path, char *name_exp);
t_list		*check_name(t_list *new_lst);
int			comp(char *name_exp, t_list *list);

// Exec functions

char		**recmd(char **cmd, int size);
int			check_space(char *str);
int			cmd_main(char **cmd, char **env_pers);
char		*find_access_path(char **all_path, char *exec);
void		child_fork(char **cmd, char **env_pers);
void		error(void);
void		set_escape_handling(void);
void		unset_escape_handling(void);
char		*find_path(char *str);

#endif
