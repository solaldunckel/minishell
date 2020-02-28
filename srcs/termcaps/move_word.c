/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 15:41:13 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/28 15:41:30 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	move_prev_word(void)
{
	int		is_word;

	if (g_tc->cur_pos == 0)
		return ;
	is_word = 0;
	if (!g_minishell->line)
		return ;
	g_tc->cur_pos--;
	while (g_tc->cur_pos > 0)
	{
		if (!is_word && g_minishell->line[g_tc->cur_pos] != ' ')
			is_word = 1;
		if (is_word && g_minishell->line[g_tc->cur_pos - 1] == ' ')
			break ;
		move_cursor_left();
	}
}

void	move_next_word(void)
{
	int		len;
	int		is_word;

	is_word = 0;
	if (!g_minishell->line)
		return ;
	len = ft_strlen(g_minishell->line);
	while (g_tc->cur_pos < len)
	{
		if (!is_word && g_minishell->line[g_tc->cur_pos] != ' ')
			is_word = 1;
		if (is_word && g_minishell->line[g_tc->cur_pos] == ' ')
			break ;
		move_cursor_right();
	}
}
