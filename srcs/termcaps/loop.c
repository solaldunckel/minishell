/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 01:58:56 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/28 20:42:02 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		print_line(long c)
{
	tputs(tgoto(g_tc->cm, g_tc->start_col,
		g_tc->currow - g_tc->rowoffset + g_tc->mod_offset), 1, putchar_tc);
	tputs(g_tc->ce, 1, putchar_tc);
	print_prompt(g_minishell);
	if (g_minishell->line)
		ft_dprintf(0, "%s", g_minishell->line);
	get_cursor_position(&g_tc->curcol, &g_tc->currow);
	get_cursor_position(&g_tc->endcol, &g_tc->endrow);
	tputs(g_tc->ce, 1, putchar_tc);
	if ((g_tc->lenlen + g_tc->plen) % g_tc->col == 0)
	{
		g_tc->start_row -= 1;
		g_tc->currow += 1;
		c == BACKSPACE ? g_tc->rowoffset -= 1 : 0;
		c != BACKSPACE ? g_tc->rowoffset += 1 : 0;
		g_tc->mod_offset += (g_tc->lenlen + g_tc->plen) / g_tc->col;
	}
	if ((g_tc->cur_pos + g_tc->plen) % g_tc->col == 0)
	{
		g_tc->mod_offset -= (g_tc->lenlen + g_tc->plen) / g_tc->col;
		if (g_tc->currow >= g_tc->row)
			write(1, "\n", 1);
	}
	tputs(tgoto(g_tc->cm, (g_tc->cur_pos + g_tc->plen)
		% g_tc->col, g_tc->currow - g_tc->mod_offset), 1, putchar_tc);
}

void		handle_move_keys(long c)
{
	if (c == LEFT_ARROW)
		return (move_cursor_left());
	else if (c == RIGHT_ARROW)
		return (move_cursor_right());
	else if (c == CTRL_LEFT)
		return (move_prev_word());
	else if (c == CTRL_RIGHT)
		return (move_next_word());
	else if (c == CTRL_UP)
		return (move_prev_line());
	else if (c == CTRL_DOWN)
		return (move_next_line());
	else if (c == HOME)
		return (move_cursor_begin());
	else if (c == END)
		return (move_cursor_end());
}

void		handle_keys(long c)
{
	cursor_win();
	get_cursor_position(&g_tc->curcol, &g_tc->currow);
	if (ft_isprint(c))
		print_char(c);
	else if (c == BACKSPACE && g_tc->cur_pos > 0)
		delete_char();
	else if (c == UP_ARROW)
		up_history();
	else if (c == DOWN_ARROW)
		down_history();
	else if (c == ALT_C)
		return (copy_line());
	else if (c == ALT_X)
		cut_line();
	else if (c == ALT_V)
		paste_line();
	else if (c == LEFT_ARROW || c == RIGHT_ARROW || c == CTRL_LEFT
		|| c == CTRL_RIGHT || c == CTRL_UP || c == CTRL_DOWN || c == HOME
		|| c == END)
		return (handle_move_keys(c));
	g_minishell->line ? g_tc->lenlen = ft_strlen(g_minishell->line) : 0;
	print_line(c);
}

int			termcaps_loop(void)
{
	int		ret;
	long	c;

	c = 0;
	while ((ret = read(0, &c, sizeof(c))) > 0)
	{
		if (c == '\n')
		{
			get_cursor_position(&g_tc->endcol, &g_tc->endrow);
			break ;
		}
		if ((c == EOF_KEY && !g_minishell->line && (ret = -1) == -1))
			exit_cmd4(g_minishell);
		handle_keys(c);
		c = 0;
	}
	tputs(tgoto(g_tc->cm, g_tc->endcol, g_tc->endrow), 1, putchar_tc);
	printf("\n");
	return (1);
}
