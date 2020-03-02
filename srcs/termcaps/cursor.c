/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 18:25:25 by sdunckel          #+#    #+#             */
/*   Updated: 2020/03/02 19:35:04 by haguerni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	move_cursor_left(void)
{
	if (g_tc->cur_pos == 0)
		return ;
	g_tc->cur_pos--;
	(g_tc->cur_pos + g_tc->plen + 1) % g_tc->col == 0 ? g_tc->currow -= 1 : 0;
	(g_tc->cur_pos + g_tc->plen + 1) % g_tc->col == 0 ? g_tc->mod_offset += 1
		: 0;
	tputs(tgoto(g_tc->cm, (g_tc->cur_pos + g_tc->plen) % g_tc->col,
		g_tc->currow), 1, putchar_tc);
}

void	move_cursor_right(void)
{
	if (!g_minishell->line)
		return ;
	if (g_tc->cur_pos == (int)ft_strlen(g_minishell->line))
		return ;
	g_tc->cur_pos++;
	(g_tc->cur_pos + g_tc->plen) % g_tc->col == 0 ? g_tc->currow += 1 : 0;
	(g_tc->cur_pos + g_tc->plen) % g_tc->col == 0 ? g_tc->mod_offset -= 1
		: 0;
	tputs(tgoto(g_tc->cm, (g_tc->cur_pos + g_tc->plen) % g_tc->col,
		g_tc->currow), 1, putchar_tc);
}

void	get_cursor_position(int *col, int *rows)
{
	int		a;
	int		i;
	char	buf[255];
	int		ret;

	a = 0;
	i = 1;
	write(0, "\033[6n", 4);
	ret = read(0, buf, 254);
	buf[ret] = '\0';
	while (buf[i])
	{
		if (buf[i] >= 48 && buf[i] <= 57)
		{
			if (a == 0)
				*rows = ft_atoi(&buf[i]) - 1;
			else
				*col = ft_atoi(&buf[i]) - 1;
			a++;
			i += ft_intlen(*col) - 1;
		}
		i++;
	}
}
