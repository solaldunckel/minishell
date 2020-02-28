/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 01:58:56 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/28 00:47:26 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			putchar_tc(int tc)
{
	write(1, &tc, 1);
	return (0);
}

void		print_line(long c)
{
	tputs(tgoto(g_tc->cm, 0, g_tc->currow - g_tc->rowoffset + g_tc->mod_offset), 1, putchar_tc);
	tputs(g_tc->ce, 1, putchar_tc);
	print_prompt(g_minishell);
	if (g_minishell->line)
		dprintf(0, "%s", g_minishell->line);
	get_cursor_position(&g_tc->curcol, &g_tc->currow);
	get_cursor_position(&g_tc->endcol, &g_tc->endrow);
	tputs(g_tc->ce, 1, putchar_tc);
	(g_tc->lenlen + g_tc->plen) % g_tc->col == 0 ? g_tc->start_row -= 1 : 0;
	(g_tc->lenlen + g_tc->plen) % g_tc->col == 0 && c != BACKSPACE ? g_tc->rowoffset += 1 : 0;
	(g_tc->lenlen + g_tc->plen) % g_tc->col == 0 && c == BACKSPACE ? g_tc->rowoffset -= 1 : 0;
	(g_tc->lenlen + g_tc->plen) % g_tc->col == 0 && c == BACKSPACE ? g_tc->currow += 1 : 0;
	(g_tc->lenlen + g_tc->plen) % g_tc->col == 0 && c != BACKSPACE ? g_tc->currow += 1 : 0;
	(g_tc->lenlen + g_tc->plen) % g_tc->col == 0  ? g_tc->mod_offset += (g_tc->lenlen + g_tc->plen) / g_tc->col : 0;
	(g_tc->cur_pos + g_tc->plen) % g_tc->col == 0  ? g_tc->mod_offset -= (g_tc->lenlen + g_tc->plen) / g_tc->col : 0;
	if ((g_tc->cur_pos + g_tc->plen) % (g_tc->col) == 0 && g_tc->currow >= g_tc->row)
		printf("\n");
	tputs(tgoto(g_tc->cm, (g_tc->cur_pos + g_tc->plen)
		% g_tc->col, g_tc->currow - g_tc->mod_offset), 1, putchar_tc);
}

void		print_char(long c)
{
	char	c2[2];

	c2[0] = c;
	c2[1] = '\0';
	if (g_minishell->line)
		g_minishell->line = ft_strjoin_middle(g_minishell->line, c2, g_tc->cur_pos + 1);
	else
		g_minishell->line = ft_strdup(c2);
	g_tc->cur_pos++;
}

void		delete_char(void)
{
	char	*str;
	int		len;

	if (!g_minishell->line)
		return;
	len = ft_strlen(g_minishell->line);
	if (len == 1 && g_tc->cur_pos == 1)
	{
		ft_strdel(&g_minishell->line);
		g_tc->cur_pos--;
		return ;
	}
	if (!(str = (char*)ft_calloc(1, sizeof(char) * (len + 1))))
		return ;
	ft_strlcpy(str, g_minishell->line, g_tc->cur_pos);
	ft_strncat(str, g_minishell->line + g_tc->cur_pos, len - g_tc->cur_pos);
	str[len - 1] = '\0';
	g_minishell->line = str;
	g_tc->cur_pos--;
}

void		handle_keys(long c)
{
	cursor_win();
	get_cursor_position(&g_tc->curcol, &g_tc->currow);
	if (ft_isprint(c))
		print_char(c);
	else if (c == BACKSPACE && g_tc->cur_pos > 0)
		delete_char();
	else if (c == LEFT_ARROW)
		return (move_cursor_left());
	else if (c == RIGHT_ARROW)
		return (move_cursor_right());
	else if (c == UP_ARROW)
		up_history();
	else if (c == DOWN_ARROW)
		down_history();
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
	else if (c == ALT_C)
		return (copy_line());
	else if (c == ALT_X)
		cut_line();
	else if (c == ALT_V)
		paste_line();
	g_minishell->line ? g_tc->lenlen = ft_strlen(g_minishell->line) : 0;
	print_line(c);
}

int        termcaps_loop(void)
{
	int                 ret;
	long                c;

	c = 0;
	while ((ret = read(0, &c, sizeof(c))) > 0)
	{
		if (c == '\n')
		{
			get_cursor_position(&g_tc->endcol, &g_tc->endrow);
			break;
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
