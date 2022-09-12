/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 16:05:39 by jcauchet          #+#    #+#             */
/*   Updated: 2022/08/25 12:43:32 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>
# include <unistd.h>

extern struct global	*g_glob;

typedef struct global	t_global;

typedef struct s_list
{
	struct s_list	*next;
	struct s_list	*next_sort;
	void			*content;
	int				print;
	int				index;
	char			*head;
	char			linker;
	char			*name;
	int				q1;
	char			*path;
	int				q2;
	char			*base_path;
}	t_list;

int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
void	*ft_memset(void *b, int c, size_t len);
char	**ft_split(char *s, char c);
char	*ft_strdup(char *s1);
int		ft_strlen(char *s);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strchr(char *s, int c);
int		ft_tolower(int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
int		ft_toupper(int c);
char	*ft_substr(char *s, int start, int len);
char	*ft_itoa(int n);
int		ft_isalpha(int c);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
size_t	ft_strlcat(char *dst, char *src, size_t dstsize);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strtrim(char *s1, char *set);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	*ft_strmapi(char *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
t_list	*ft_lstnew(char *env_choosen, int size);
t_list	*ft_lstnew_void(void);
void	ft_lstadd_front(t_list **alst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
char	*strjoin_without_free(char *s1, char *s2);
char	*append_char(char *str, char c);
char	*strdup_one(char c);
char	*ft_strjoin_char(char *str, char c);
void	print_list(t_list *list);
char	*ft_strjoin_df(char *s1, char *s2);
char	*join_christophe(char *str, char c);

#endif
