/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:00:09 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/22 11:41:18 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_check_flag(char *str, va_list ap, t_printf *tab)
{
	if (str[tab->i] == '*')
	{
		if (tab->precision_parsing)
			tab->precision_width = va_arg(ap, int);
		else
			tab->width = va_arg(ap, int);
	}
	if (str[tab->i] == '0' && !tab->minus && !tab->precision_parsing)
		tab->zero = 1;
	if (str[tab->i] > '0' && str[tab->i] <= '9' && !tab->precision_parsing)
		tab->width = ft_atoi_printf(str, &tab->i);
	if (str[tab->i] >= '0' && str[tab->i] <= '9' && tab->precision_parsing)
		tab->precision_width = ft_atoi_printf(str, &tab->i);
	tab->precision_parsing = 0;
	if (str[tab->i] == '-')
	{
		tab->zero = 0;
		tab->minus = 1;
	}
	str[tab->i] == '.' ? ft_set_precision(tab) : 0;
	str[tab->i] == ' ' ? tab->space = 1 : 0;
	str[tab->i] == '+' ? tab->plus = 1 : 0;
	str[tab->i] == '#' ? tab->sharp = 1 : 0;
	str[tab->i] == 'l' ? tab->l_count += 1 : 0;
	str[tab->i] == 'h' ? tab->h_count += 1 : 0;
}

int		ft_parse2(char *str, va_list ap, t_printf *tab)
{
	char	*sp;
	char	*c;

	while (!ft_is_flag(str[tab->i]))
	{
		ft_check_flag(str, ap, tab);
		if (str[tab->i + 1] == '\0')
			return (0);
		if (!ft_is_from_pf(str[tab->i + 1]))
		{
			c = ft_c_to_str(str[tab->i + 1]);
			tab->len = 1;
			tab->minus ? ft_add_to_buff(tab, c, 1) : 0;
			sp = ft_print_sp(tab);
			ft_add_to_buff(tab, sp, tab->sp_len);
			!tab->minus ? ft_add_to_buff(tab, c, 1) : 0;
			free(c);
			free(sp);
			tab->i++;
			return (0);
		}
		tab->i++;
	}
	return (1);
}

void	ft_parse(char *str, va_list ap, t_printf *tab)
{
	tab->i++;
	ft_reset_flags(tab);
	if (!ft_parse2(str, ap, tab))
		return ;
	if (tab->width < 0)
	{
		tab->minus = 1;
		tab->zero = 0;
		tab->width = -tab->width;
	}
	if (tab->precision_width < 0)
		tab->precision = 0;
	tab->precision && tab->precision_width >= 0 ? tab->zero = 0 : 0;
	tab->converter = str[tab->i];
	str[tab->i] == 'c' ? ft_convert_c(ap, tab) : 0;
	str[tab->i] == 's' ? ft_convert_str(ap, tab) : 0;
	str[tab->i] == 'p' ? ft_convert_p(ap, tab) : 0;
	str[tab->i] == 'd' || str[tab->i] == 'i' ? ft_convert_int(ap, tab) : 0;
	str[tab->i] == 'u' ? ft_convert_uint(ap, tab) : 0;
	str[tab->i] == 'x' ? ft_convert_x(ap, tab) : 0;
	str[tab->i] == 'X' ? ft_convert_x(ap, tab) : 0;
	str[tab->i] == '%' ? ft_convert_c(ap, tab) : 0;
	str[tab->i] == 'n' ? ft_convert_n(ap, tab) : 0;
}

size_t	ft_is_flag(char c)
{
	return (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i'
	|| c == 'u' || c == 'x' || c == 'n' || c == 'X' || c == '%');
}

size_t	ft_is_from_pf(char c)
{
	return (ft_is_flag(c) || (c >= '0' && c <= '9')
	|| c == '-' || c == ' ' || c == '.' || c == '+' || c == '#' || c == '*'
	|| c == 'l' || c == 'h');
}
