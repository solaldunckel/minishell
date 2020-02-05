/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 11:18:12 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/05 21:25:26 by sdunckel         ###   ########.fr       */
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

void	exec_commands(t_minishell *minishell)
{
	t_cmd	*tmp;

	tmp = minishell->cmd_list;
	while (tmp)
	{
		if (ft_strequ(tmp->cmd, ECHO_CMD))
			echo_cmd(minishell, tmp);
		else if (ft_strequ(tmp->cmd, CD_CMD))
			cd_cmd(minishell, tmp);
		else if (ft_strequ(tmp->cmd, EXIT_CMD))
			exit_cmd();
		else if (ft_strequ(tmp->cmd, ENV_CMD))
			env_cmd(&minishell->env_list);
		else if (ft_strequ(tmp->cmd, PWD_CMD))
			pwd_cmd(minishell);
		else if (ft_strequ(tmp->cmd, EXPORT_CMD))
			export_cmd(minishell, tmp);
		else if (ft_strequ(tmp->cmd, UNSET_CMD))
			unset_cmd(minishell, tmp);
		tmp = tmp->next;
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
			exec_commands(minishell);
			clear_token_list(&minishell->token_list, free);
			clear_cmd_list(&minishell->cmd_list, free);
			ft_strdel(&minishell->line);
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
