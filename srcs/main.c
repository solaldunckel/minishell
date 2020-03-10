/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 11:18:12 by sdunckel          #+#    #+#             */
/*   Updated: 2020/03/10 03:54:03 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_prompt(t_minishell *minishell)
{
	if (minishell->exit == 0)
		ft_dprintf(2, "" BOLDGREEN "➜ " RESET BOLDCYAN " %s " RESET,
			minishell->curdir);
	else
		ft_dprintf(2, "" BOLDRED "➜ " RESET BOLDCYAN " %s " RESET,
			minishell->curdir);
}

void	exec_commands2(t_minishell *minishell, t_cmd *tmp, int fpipe[2])
{
	if (ft_strequ(tmp->cmd, EXIT_CMD) && tmp->type != T_PIPE
		&& (!tmp->prev || tmp->prev->type != T_PIPE))
		exit_cmd2(minishell, tmp, 0);
	else if (ft_strequ(tmp->cmd, EXPORT_CMD) && tmp->args)
		export_cmd(minishell, tmp, 0);
	else if (ft_strequ(tmp->cmd, CD_CMD) && tmp->type != T_PIPE &&
		(!tmp->prev || tmp->prev->type != T_PIPE))
		cd_cmd(minishell, tmp);
	else if (ft_strequ(tmp->cmd, UNSET_CMD))
		unset_cmd(minishell, tmp);
	else if (!tmp->prev || (tmp->prev && !(tmp->prev->type == T_PIPE)))
		exec_prog(minishell, tmp, fpipe, NULL);
}

void	exec_commands(t_minishell *minishell)
{
	t_cmd	*tmp;
	int		fpipe[2];

	tmp = minishell->cmd_list;
	while (tmp)
	{
		process_args(tmp);
		create_redirect(minishell, tmp);
		if (tmp->cmd && tmp->out != -1 && tmp->in != -1)
		{
			if (pipe(fpipe))
				return ;
			exec_commands2(minishell, tmp, fpipe);
			close(fpipe[0]);
			close(fpipe[1]);
		}
		if (!tmp->cmd && tmp->type != T_PIPE)
		{
			process_args_env(tmp);
			add_tmp_env_variable(minishell, tmp);
		}
		while (tmp->type == T_PIPE)
			tmp = tmp->next;
		tmp = tmp->next;
	}
}

void	wait_for_command(t_minishell *minishell)
{
	while (1)
	{
		signal(SIGQUIT, sighandler);
		signal(SIGINT, sighandler);
		if (minishell->quit == 0 || minishell->quit2)
			print_prompt(minishell);
		minishell->quit = 0;
		minishell->quit2 = 0;
		minishell->forked = 0;
		if (get_next_line_no_eof(0, &minishell->line, 0))
		{
			while (g_minishell->quit == 0 && bracket_odd(minishell->line, 1))
				next_bracket(minishell);
			start_parse(minishell, minishell->line);
			if (minishell->cmd_list && (g_minishell->quit == 0
				|| g_minishell->quit == 4))
				exec_commands(minishell);
			if (ft_strlen(minishell->line) && ft_strlen_s(minishell->line) == 0)
				minishell->exit = 0;
			clear_token_list(&minishell->token_list, free);
			clear_cmd_list(&minishell->cmd_list, free);
		}
		ft_strdel(&minishell->line);
	}
}

int		main(int argc, char **argv, char **env)
{
	t_minishell		minishell;
	int				fd;

	(void)argc;
	(void)argv;
	if (read(0, NULL, 0) == -1)
		return (0);
	if ((fd = dup(0)) == -1)
		return (0);
	close(fd);
	ft_bzero(&minishell, sizeof(t_minishell));
	ft_dprintf(2, "\nMINISHELL 42 by sdunckel & haguerni\n\n");
	minishell.name = ft_strtrim(argv[0], "./");
	minishell.curdir = getcwd(NULL, 0);
	env_init(&minishell, env);
	g_minishell = &minishell;
	minishell.quit = 0;
	wait_for_command(&minishell);
	return (0);
}
