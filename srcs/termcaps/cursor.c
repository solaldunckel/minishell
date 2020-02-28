/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 18:25:25 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/28 00:46:43 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	move_cursor_left(void)
{
	if (g_tc->cur_pos == 0)
		return ;
	g_tc->cur_pos--;
	(g_tc->cur_pos + g_tc->plen + 1) % g_tc->col == 0 ? g_tc->currow -= 1 : 0;
	(g_tc->cur_pos + g_tc->plen + 1) % g_tc->col == 0 ? g_tc->mod_offset += 1 : 0;
	tputs(tgoto(g_tc->cm, (g_tc->cur_pos + g_tc->plen) % g_tc->col, g_tc->currow), 1, putchar_tc);
}

void	move_cursor_right(void)
{
	if (!g_minishell->line)
		return ;
	if (g_tc->cur_pos == (int)ft_strlen(g_minishell->line))
		return ;
	g_tc->cur_pos++;
	(g_tc->cur_pos + g_tc->plen - 1) % g_tc->col == 0 ? g_tc->currow += 1 : 0;
	(g_tc->cur_pos + g_tc->plen - 1) % g_tc->col == 0 ? g_tc->mod_offset -= 1 : 0;
	tputs(tgoto(g_tc->cm, (g_tc->cur_pos + g_tc->plen) % g_tc->col, g_tc->currow), 1, putchar_tc);
}

void	move_prev_word(void)
{
	int		i;
	int		is_word;

	if (g_tc->cur_pos == 0)
		return ;
	i = g_tc->cur_pos - 1;
	is_word = 0;
	if (!g_minishell->line)
		return ;
	while (i > 0 && g_minishell->line[i])
	{
		if (g_minishell->line[i] == ' ')
		{
			is_word = 1;
			if (g_minishell->line[i - 1] != ' ')
				break;
		}
		else if (is_word && g_minishell->line[i - 1] != ' ')
			break;
		i--;
	}
	g_tc->cur_pos = i;
	tputs(tgoto(g_tc->cm, (g_tc->cur_pos + g_tc->plen) % g_tc->col, g_tc->currow), 1, putchar_tc);
}

void	move_next_word(void)
{
	int		len;
	int		i;
	int		is_word;

	i = g_tc->cur_pos;
	is_word = 0;
	if (!g_minishell->line)
		return ;
	len = ft_strlen(g_minishell->line);
	while (i < len && g_minishell->line[i])
	{
		if (g_minishell->line[i] == ' ')
			is_word = 1;
		else if (is_word && g_minishell->line[i] != ' ')
			break;
		i++;
	}
	g_tc->cur_pos = i;
	tputs(tgoto(g_tc->cm, (g_tc->cur_pos + g_tc->plen) % g_tc->col, g_tc->currow), 1, putchar_tc);
}

void	move_cursor_begin(void)
{
	int		offset;

	offset = 0;
	if (!g_minishell->line)
		return ;
	if (g_tc->cur_pos == 0)
		return ;
	g_tc->cur_pos = 0;
	offset = (g_tc->cur_pos + g_tc->plen) / g_tc->col;
	// g_tc->mod_offset = 0;
	tputs(tgoto(g_tc->cm, (g_tc->cur_pos + g_tc->plen) % g_tc->col, g_tc->currow - g_tc->rowoffset), 1, putchar_tc);
}

void	move_cursor_end(void)
{
	int		offset;
	int		len;

	offset = 0;
	if (!g_minishell->line)
		return ;
	len = ft_strlen(g_minishell->line);
	if (g_tc->cur_pos == len)
		return ;
	g_tc->cur_pos = len;
	// g_tc->mod_offset = 0;
	tputs(tgoto(g_tc->cm, (g_tc->cur_pos + g_tc->plen) % g_tc->col, g_tc->currow), 1, putchar_tc);
}

void	move_prev_line(void)
{
	int		offset;

	offset = 0;
	offset = (g_tc->cur_pos + g_tc->plen) / g_tc->col;
	if (!g_minishell->line || offset == 0)
		return ;
	g_tc->cur_pos -= g_tc->col;
	g_tc->mod_offset += 1;
	if ((g_tc->cur_pos + g_tc->plen) % g_tc->col < g_tc->plen && offset == 0)
	{
		g_tc->cur_pos = 0;
		tputs(tgoto(g_tc->cm, g_tc->plen, g_tc->currow - g_tc->mod_offset), 1, putchar_tc);
	}
	else
		tputs(tgoto(g_tc->cm, (g_tc->cur_pos + g_tc->plen) % g_tc->col,
			g_tc->currow - g_tc->mod_offset), 1, putchar_tc);
}

void	move_next_line(void)
{

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
				*rows = atoi(&buf[i]) - 1;
			else
				*col = atoi(&buf[i - 1]) - 1;
			a++;
		}
		i++;
	}
}
