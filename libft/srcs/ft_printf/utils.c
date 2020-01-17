/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:45:21 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/22 11:42:46 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_add_sign(t_printf *tab)
{
	if (tab->n < 0)
	{
		tab->len--;
		ft_add_to_buff(tab, "-", 1);
	}
	else if (tab->plus && (tab->n >= 0))
	{
		tab->len--;
		ft_add_to_buff(tab, "+", 1);
	}
	else if (tab->space && !tab->plus && (tab->n >= 0))
	{
		tab->len--;
		ft_add_to_buff(tab, " ", 1);
	}
}

void	ft_add_prefix(t_printf *tab)
{
	if (tab->converter == 'x')
	{
		ft_add_to_buff(tab, "0x", 2);
		tab->len -= 2;
	}
	if (tab->converter == 'X')
	{
		ft_add_to_buff(tab, "0X", 2);
		tab->len -= 2;
	}
}

void	ft_join_all(char *str, char *sp, t_printf *tab)
{
	(tab->is_int && tab->zero) ? ft_add_sign(tab) : 0;
	if (tab->zero && tab->converter == 'p')
	{
		ft_add_to_buff(tab, "0x", 2);
		tab->len -= 2;
	}
	if (tab->sharp && tab->u && tab->zero && tab->precision_width < tab->len)
		ft_add_prefix(tab);
	if (sp && !tab->minus)
		ft_add_to_buff(tab, sp, tab->sp_len);
	if (!tab->zero && tab->converter == 'p')
	{
		ft_add_to_buff(tab, "0x", 2);
		tab->len -= 2;
	}
	if (tab->sharp && tab->u && !tab->zero && tab->precision_width < tab->len)
		ft_add_prefix(tab);
	if (tab->is_int && !tab->zero)
		ft_add_sign(tab);
	ft_add_to_buff(tab, str, tab->len);
	if (sp && tab->minus)
		ft_add_to_buff(tab, sp, tab->sp_len);
	free(str);
	free(sp);
}

char	*ft_print_sp(t_printf *tab)
{
	char	*str;
	int		i;

	i = 0;
	if (tab->width < tab->len)
		return (NULL);
	if (!(str = ft_calloc((tab->width - tab->len + 1), sizeof(char))))
		return (NULL);
	if (tab->precision && tab->precision_width > tab->len)
		tab->zero = 0;
	while (i < tab->width - tab->len)
	{
		if (tab->zero)
			str[i] = '0';
		else
			str[i] = ' ';
		i++;
	}
	tab->sp_len = i;
	str[i] = '\0';
	return (str);
}

char	*ft_num_precision(char *str, t_printf *tab)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!tab->precision)
		return (str);
	if (tab->precision_width < tab->len)
		return (str);
	if (!(tmp = ft_calloc(tab->precision_width + tab->len + 1, sizeof(char))))
		return (NULL);
	while (i < tab->precision_width - tab->len)
	{
		tmp[i] = '0';
		i++;
	}
	while (str[j])
	{
		tmp[i + j] = str[j];
		j++;
	}
	tmp[i + j] = '\0';
	free(str);
	return (tmp);
}
