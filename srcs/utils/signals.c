/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 22:10:43 by sdunckel          #+#    #+#             */
/*   Updated: 2020/03/03 16:33:06 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighandler(int sig_num)
{
	ft_printf("\b\b  \b\b");
	if (sig_num == SIGINT)
	{
		ft_printf("\n");
		if (!g_minishell->forked)
			g_minishell->exit = 1;
		else
			g_minishell->exit = 130;
		print_prompt(g_minishell);
		g_minishell->quit = 1;
	}
	if (sig_num == SIGQUIT)
		g_minishell->quit = 4;
}

void	degage_frr(int sig_num)
{
	if (sig_num == 3)
		ft_dprintf(2, "Quit: %d\n", sig_num);
	g_minishell->quit = 4;
	g_minishell->quit2 = 1;
	if (sig_num == SIGQUIT)
		g_minishell->exit = 131;
	if (sig_num == SIGINT)
		g_minishell->exit = 130;
}
