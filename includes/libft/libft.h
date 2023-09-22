/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 17:15:15 by ljerinec          #+#    #+#             */
/*   Updated: 2022/11/01 17:15:17 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include "../ft_printf/ft_printf.h"
# include "../get_next_line/get_next_line.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

// string management
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_tolower(int caracter);
int			ft_toupper(int caracter);
int			ft_tolower(int c);
char		*ft_strrchr(char *s, int c);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(char *src);
char		*ft_strnstr(const char *str, const char *to_find, size_t n);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char *s1, char *s2);
char		**ft_split(char const *s, char c);
size_t		ft_strlcpy(char	*dest, const char	*src, size_t n);
size_t		ft_strlcat(char *dst, const char	*src, size_t dstsize);
size_t		ft_strlen(const char *str);

// checking string
int			ft_isalnum(int character);
int			ft_isalpha(int character);
int			ft_isdigit(int character);
int			ft_isprint(int caracter);
int			ft_isascii(int caracter);

// memory usage
int			ft_memcmp(void *s1, void *s2, size_t n);
void		ft_bzero(void	*s, size_t n);
void		*ft_memset(void	*b, int c, size_t len);
void		*ft_memcpy(void *dest, void const *src, size_t len);
void		*ft_memmove(void *dest, void *src, size_t len);
void		*ft_memchr(const void *str, int caracter, size_t len);
void		*ft_calloc(size_t count, size_t size);

// printing
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

// conversion
int			ft_atoi(const char *str);
char		*ft_itoa(int n);
long long	ft_atoi_2(const char *str);

// others
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));

// liste chainée
int			ft_lstsize(t_list *lst);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstadd_here(t_list **lst, t_list *new);
void		ft_lstdellast(t_list *lst);
void		ft_lstiter(t_list *lst, void (*f)(void *));
void		ft_lstdel_here(t_list **lst, t_list *node_to_delete);

// t_list		*ft_lstdel_here(t_list **lst, t_list *node_to_delete);
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstnew(void *content);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
