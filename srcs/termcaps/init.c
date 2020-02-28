/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 01:58:24 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/28 20:37:23 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_term(void)
{
	char	*name;

	if (!(name = get_env(g_minishell, "TERM")))
		name = "xterm";
	tgetent(NULL, name);
	setupterm(NULL, STDOUT_FILENO, NULL);
	tcgetattr(0, &g_tc->term);
	tcgetattr(0, &g_tc->term_backup);
	g_tc->term.c_lflag = g_tc->term.c_lflag & ~ICANON;
	g_tc->term.c_lflag = g_tc->term.c_lflag & ~ECHO;
	g_tc->term.c_cc[VMIN] = 1;
	g_tc->term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &g_tc->term);
	init_tc();
}

void	cursor_win(void)
{
	struct winsize w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	g_tc->col = w.ws_col;
	g_tc->row = w.ws_row;
}

void	init_tc(void)
{
	g_tc->cm = tgetstr("cm", NULL);
	g_tc->ce = tgetstr("ce", NULL);
}
