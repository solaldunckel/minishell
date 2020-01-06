/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 11:10:11 by sdunckel          #+#    #+#             */
/*   Updated: 2019/10/24 15:11:02 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_dump_buffer(t_printf *tab)
{
	write(1, tab->buf, tab->buf_count);
	tab->buf_count = 0;
}

void	ft_add_to_buff(t_printf *tab, char *str, int len)
{
	int		i;

	i = 0;
	tab->ret += len;
	while (i < len)
	{
		tab->buf[tab->buf_count] = str[i];
		tab->buf_count++;
		if (tab->buf_count == BUFFER_SIZE)
			ft_dump_buffer(tab);
		i++;
	}
}

void	ft_print_normal(t_printf *tab, char *str)
{
	int		len;

	len = 0;
	while (str[tab->i] && str[tab->i] != '%')
	{
		tab->buf[tab->buf_count] = str[tab->i];
		tab->buf_count++;
		len++;
		if (tab->buf_count == BUFFER_SIZE)
			ft_dump_buffer(tab);
		tab->i++;
	}
	tab->ret += len;
	tab->i--;
}

void	ft_init_struct(t_printf *tab)
{
	tab->buf_count = 0;
	tab->ret = 0;
	tab->width = 0;
	tab->precision = 0;
	tab->precision_width = 0;
	tab->precision_parsing = 0;
	tab->converter = 0;
	tab->minus = 0;
	tab->zero = 0;
	tab->plus = 0;
	tab->space = 0;
	tab->sharp = 0;
	tab->len = 0;
	tab->sp_len = 0;
	tab->is_int = 0;
	tab->h_count = 0;
	tab->l_count = 0;
	tab->n = 0;
	tab->u = 0;
	tab->i = 0;
}

int		ft_printf(const char *str, ...)
{
	t_printf	tab;
	va_list		ap;

	ft_init_struct(&tab);
	va_start(ap, str);
	while (str[tab.i])
	{
		if (str[tab.i] == '%')
		{
			if (str[tab.i + 1] == '\0')
				break ;
			if (ft_is_from_pf(str[tab.i + 1]))
				ft_parse((char*)str, ap, &tab);
		}
		else
			ft_print_normal(&tab, (char*)str);
		tab.i++;
	}
	va_end(ap);
	ft_dump_buffer(&tab);
	return (tab.ret);
}
