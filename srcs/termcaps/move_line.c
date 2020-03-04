/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 15:42:16 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/28 16:49:59 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	move_cursor_begin(void)
{
	int		offset;

	offset = 0;
	if (!g_minishell->line)
		return ;
	if (g_tc->cur_pos == 0)
		return ;
	while (g_tc->cur_pos > 0)
		move_cursor_left();
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
	while (g_tc->cur_pos < len)
		move_cursor_right();
}

void	move_prev_line(void)
{
	int		start_col;
	int		start_row;
	int		cur_row;
	int		cur_col;

	start_col = 0;
	start_row = 0;
	cur_row = 0;
	cur_col = 0;
	get_cursor_position(&start_col, &start_row);
	while (g_tc->cur_pos > 0)
	{
		get_cursor_position(&cur_col, &cur_row);
		if (cur_row != start_row && start_col == cur_col)
			break ;
		move_cursor_left();
	}
}

void	move_next_line(void)
{
	int		start_col;
	int		start_row;
	int		cur_row;
	int		cur_col;
	int		len;

	start_col = 0;
	start_row = 0;
	cur_row = 0;
	cur_col = 0;
	if (!g_minishell->line)
		return ;
	len = ft_strlen(g_minishell->line);
	get_cursor_position(&start_col, &start_row);
	while (g_tc->cur_pos < len)
	{
		get_cursor_position(&cur_col, &cur_row);
		if (cur_row != start_row && start_col == cur_col)
			break ;
		move_cursor_right();
	}
}
