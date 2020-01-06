/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 09:29:00 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/06 15:26:39 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

# define RESET   "\033[0m"
# define BLACK   "\033[30m"
# define RED     "\033[31m"
# define GREEN   "\033[32m"
# define YELLOW  "\033[33m"
# define BLUE    "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN    "\033[36m"
# define WHITE   "\033[37m"
# define BOLDBLACK   "\033[1m\033[30m"
# define BOLDRED     "\033[1m\033[31m"
# define BOLDGREEN   "\033[1m\033[32m"
# define BOLDYELLOW  "\033[1m\033[33m"
# define BOLDBLUE    "\033[1m\033[34m"
# define BOLDMAGENTA "\033[1m\033[35m"
# define BOLDCYAN    "\033[1m\033[36m"
# define BOLDWHITE   "\033[1m\033[37m"

typedef struct	s_printf
{
	char			buf[BUFFER_SIZE + 1];
	int				buf_count;
	int				ret;
	int				width;
	int				precision;
	int				precision_width;
	int				precision_parsing;
	int				converter;
	int				minus;
	int				zero;
	int				plus;
	int				space;
	int				sharp;
	int				len;
	int				sp_len;
	int				is_int;
	int				h_count;
	int				l_count;
	intmax_t		n;
	uintmax_t		u;
	int				i;
}				t_printf;

int				ft_printf(const char *str, ...);
void			ft_init_struct(t_printf *tab);
void			ft_str_it(va_list ap, t_printf *tab, char *str);
void			ft_parse(char *str, va_list ap, t_printf *tab);
void			ft_check_flag(char *str, va_list ap, t_printf *tab);
void			ft_add_to_buff(t_printf *tab, char *str, int len);
void			ft_dump_buffer(t_printf *tab);
void			ft_convert_str(va_list ap, t_printf *tab);
void			ft_convert_int(va_list ap, t_printf *tab);
void			ft_convert_uint(va_list ap, t_printf *tab);
void			ft_convert_x(va_list ap, t_printf *tab);
void			ft_convert_p(va_list ap, t_printf *tab);
void			ft_convert_c(va_list ap, t_printf *tab);
void			ft_convert_n(va_list ap, t_printf *tab);
void			ft_convert_o(va_list ap, t_printf *tab);
void			ft_size_u(va_list ap, t_printf *tab);
char			*ft_strdup_l(char *s, t_printf *tab);
char			*ft_print_sp(t_printf *tab);
char			*ft_num_precision(char *str, t_printf *tab);
void			ft_join_all(char *str, char *sp, t_printf *tab);
char			*ft_c_to_str(char c);
void			ft_add_sign(t_printf *tab);
int				ft_atoi_printf(char *str, int *i);
char			*itoa_printf(intmax_t n);
char			*uitoa_printf(uintmax_t n);
char			*itoa_base_pf(uintmax_t num, char *base);
size_t			intlen_printf(intmax_t n);
size_t			uintlen_printf(uintmax_t n);
size_t			intlen_base_pf(uintmax_t n, char *base);
void			ft_set_precision(t_printf *tab);
void			ft_reset_flags(t_printf *tab);
size_t			ft_is_flag(char c);
size_t			ft_is_from_pf(char c);

#endif
