/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 10:57:51 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/23 17:41:17 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>

# include "ft_printf.h"
# include "get_next_line.h"

# define TRUE 1
# define FALSE 0

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/*
** String Functions
*/

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
size_t				ft_strlen(const char *s);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
char				*ft_strdup(const char *s1);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strcat(char *dst, const char *src);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				**ft_ssplit(char const *s, char *set);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_atoi(const char *nptr);
float				ft_atof(char *str);
char				*ft_itoa(intmax_t n);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
char				*ft_strncpy(char *dst, const char *src, size_t len);
int					ft_str_c_count(char *str, char c);
int					ft_str_isdigit(char *str);
int					ft_str_end(char *str, char *end);

/*
** Memory Functions
*/

void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memalloc(size_t size);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_memdel(void **ap);
void				*ft_calloc(size_t count, size_t size);

/*
** Print Functions
*/

void				ft_putchar(char c);
void				ft_putnbr(int n);
void				ft_putstr(char *s);
void				ft_putendl(char *s);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

/*
** List Functions
*/

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **alst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void*),
						void (*del)(void *));

/*
** Other Functions
*/

size_t				ft_is_space(char c);
int					ft_is_in_stri(char c, char *str);
size_t				ft_intlen(intmax_t n);
size_t				ft_intlen_base(uintmax_t n, char *base);
int					ft_check_base(char *base);
intmax_t			ft_atoi_base(char *str, char *base);
char				*ft_convert_base(char *nbr, char *base_from, char *base_to);
char				*ft_itoa_base(uintmax_t n, char *base);
char				*ft_c_to_str(char c);
char				*ft_uitoa(uintmax_t n);
size_t				ft_uintlen(uintmax_t n);
size_t				ft_strlen_c(char *s, char c);
int					ft_strequ(char *s1, char *s2);

#endif
