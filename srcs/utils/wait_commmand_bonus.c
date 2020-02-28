/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_commmand_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 20:24:06 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/28 20:27:22 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_for_command_tty(t_minishell *minishell)
{
	while (1)
	{
		signal(SIGQUIT, sighandler);
		signal(SIGINT, sighandler);
		if (g_minishell->quit == 0 || g_minishell->quit2)
			print_prompt(minishell);
		g_minishell->quit = 0;
		g_minishell->quit2 = 0;
		minishell->forked = 0;
		if (get_next_line_no_eof(0, &minishell->line, 0))
		{
			while (g_minishell->quit == 0 && bracket_odd(minishell->line, 1))
				next_bracket(minishell);
			start_parse(minishell, minishell->line);
			if (g_minishell->quit == 0 || g_minishell->quit == 4)
				exec_commands(minishell);
			clear_token_list(&minishell->token_list, free);
			clear_cmd_list(&minishell->cmd_list, free);
		}
		ft_strdel(&minishell->line);
	}
}

void	wait_for_command(t_minishell *minishell)
{
	while (1)
	{
		signal(SIGQUIT, sighandler);
		signal(SIGINT, sighandler);
		get_cursor_position(&g_tc->start_col, &g_tc->start_row);
		print_prompt(minishell);
		get_cursor_position(&g_tc->col, &g_tc->start_row);
		g_tc->mod_offset = 0;
		if (termcaps_loop())
		{
			tcsetattr(0, TCSANOW, &g_tc->term_backup);
			add_cmd_to_history(minishell->line);
			if (minishell->line)
				start_parse(minishell, minishell->line);
			exec_commands(minishell);
			clear_token_list(&minishell->token_list, free);
			clear_cmd_list(&minishell->cmd_list, free);
			tcsetattr(0, TCSANOW, &g_tc->term);
		}
		ft_strdel(&g_tc->backup_cmd);
		g_tc->rowoffset = 0;
		g_tc->cur_history = NULL;
		g_tc->cur_pos = 0;
		ft_strdel(&minishell->line);
	}
}
