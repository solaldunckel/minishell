/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 11:18:12 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/10 01:17:41 by tomsize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_prompt(t_minishell *minishell)
{
	if (minishell->exit == 0)
		ft_printf("" BOLDGREEN "➜ " RESET BOLDCYAN " %s " RESET,
			minishell->curdir);
	else
		ft_printf("" BOLDRED "➜ " RESET BOLDCYAN " %s " RESET,
			minishell->curdir);
}

void	sighandler(int sig_num)
{
	ft_printf("\b\b  \b\b");
	if (sig_num == SIGINT)
	{
		ft_printf("\n" BOLDGREEN "➜ " RESET BOLDCYAN " %s " RESET,
		g_minishell->curdir);
		g_minishell->quit = 1;
	}
}

void	wait_for_command(t_minishell *minishell)
{
	while (1)
	{
		signal(SIGQUIT, sighandler);
		signal(SIGINT, sighandler);
		g_minishell->quit == 0 ? print_prompt(minishell) : 0;
		g_minishell->quit = 0;
		if (get_next_line_no_eof(0, &minishell->line, 0))
		{
			while (bracket_odd(minishell->line))
				next_bracket(minishell);
			start_parse(minishell, minishell->line);
			ft_strdel(&minishell->line);
			exec_commands(minishell);
			clear_token_list(&minishell->token_list, free);
			clear_cmd_list(&minishell->cmd_list, free);
		}
	}
}

int		main(int argc, char **argv, char **env)
{
	t_minishell		minishell;

	(void)argc;
	(void)argv;
	ft_bzero(&minishell, sizeof(t_minishell));
	ft_printf("\nMINISHELL 42 by sdunckel & haguerni\n\n");
	minishell.name = ft_strtrim(argv[0], "./");
	minishell.curdir = getcwd(NULL, 0);
	env_init(&minishell, env);
	g_minishell = &minishell;
	g_minishell->quit = 0;
	wait_for_command(&minishell);
	return (0);
}
