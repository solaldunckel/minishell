/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:43:05 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/22 11:32:47 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_size_int(va_list ap, t_printf *tab)
{
	if (tab->l_count >= 2)
		tab->n = (intmax_t)va_arg(ap, long long);
	else if (tab->l_count == 1)
		tab->n = (intmax_t)va_arg(ap, long);
	else if (tab->h_count && ((tab->h_count % 2) == 0))
		tab->n = (intmax_t)((char)va_arg(ap, int));
	else if (tab->h_count && ((tab->h_count % 2) != 0))
		tab->n = (intmax_t)((short)va_arg(ap, int));
	else
		tab->n = (intmax_t)va_arg(ap, int);
}

void	ft_size_u(va_list ap, t_printf *tab)
{
	if (tab->l_count >= 2)
		tab->u = (uintmax_t)va_arg(ap, unsigned long long);
	else if (tab->l_count == 1)
		tab->u = (uintmax_t)va_arg(ap, unsigned long);
	else if (tab->h_count && ((tab->h_count % 2) == 0))
		tab->u = (uintmax_t)((unsigned char)va_arg(ap, int));
	else if (tab->h_count && ((tab->h_count % 2) != 0))
		tab->u = (uintmax_t)((unsigned short)va_arg(ap, int));
	else
		tab->u = (uintmax_t)va_arg(ap, unsigned int);
}

void	ft_convert_int(va_list ap, t_printf *tab)
{
	char	*str;
	char	*sp;

	tab->is_int = 1;
	ft_size_int(ap, tab);
	str = itoa_printf(tab->n);
	tab->len = ft_intlen(tab->n);
	str = ft_num_precision(str, tab);
	tab->len = ft_strlen(str);
	(tab->n < 0) ? tab->len++ : 0;
	(tab->n >= 0) && (tab->plus || tab->space) ? tab->len++ : 0;
	if (tab->n == 0 && tab->precision && tab->precision_width == 0
		&& !tab->width)
	{
		free(str);
		return ;
	}
	if (tab->n == 0 && tab->precision && tab->precision_width == 0)
	{
		free(str);
		str = ft_strdup(" ");
	}
	sp = ft_print_sp(tab);
	ft_join_all(str, sp, tab);
}

void	ft_convert_uint(va_list ap, t_printf *tab)
{
	char	*str;
	char	*sp;

	tab->is_int = 1;
	ft_size_u(ap, tab);
	str = ft_uitoa(tab->u);
	tab->len = ft_strlen(str);
	str = ft_num_precision(str, tab);
	tab->len = ft_strlen(str);
	if (tab->u == 0 && tab->precision && tab->precision_width == 0
		&& !tab->width)
	{
		free(str);
		return ;
	}
	if (tab->u == 0 && tab->precision && tab->precision_width == 0)
	{
		free(str);
		str = ft_strdup(" ");
	}
	sp = ft_print_sp(tab);
	ft_join_all(str, sp, tab);
}
