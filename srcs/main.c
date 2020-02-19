/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 11:18:12 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/19 14:29:28 by sdunckel         ###   ########.fr       */
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
		ft_printf("\n");
		if (!g_minishell->forked)
			g_minishell->exit = 1;
		else
			g_minishell->exit = 130;
		print_prompt(g_minishell);
		g_minishell->quit = 1;
	}
}

void	remove_redirect(t_token *args, t_token **begin)
{
	t_token	*tmp;
	t_token	*next;

	tmp = *begin;
	if (*begin == args)
	{
		next = (*begin)->next->next;
		free(*begin);
		*begin = next;
		return;
	}
	while (tmp && tmp->next)
	{
		if (tmp == args && tmp->prev)
		{
			next = tmp->next->next;
			if (tmp->next->next)
				tmp->next->next->prev = tmp->prev;
			tmp->prev->next = next;
			free(tmp->next);
			return;
		}
		tmp = tmp->next;
	}
}

void	create_redirect2(t_minishell *minishell, t_cmd *cmd)
{
	t_token	*args;

	(void)minishell;
	args = cmd->args;
	while (args)
	{
		printf("%p\n", args->next);
		if (ft_strequ(args->word, ">"))
		{
			if ((cmd->out = open(args->next->word, O_TRUNC | O_RDWR | O_CREAT,
				0644)) < 0)
			{
				ft_dprintf(2, "%s: %s: %s\n", g_minishell->name,
					args->next->word, strerror(errno));
				minishell->no_exit = 1;
			}
			remove_redirect(args, &cmd->args);

		}
		else if (ft_strequ(args->word, ">>"))
		{
			if ((cmd->out = open(args->next->word, O_RDWR | O_CREAT | O_APPEND,
				0644)) < 0)
			{
				ft_dprintf(2, "%s: %s: %s\n", g_minishell->name,
					args->next->word, strerror(errno));
					minishell->no_exit = 1;
			}
			remove_redirect(args, &cmd->args);
		}
		else if (ft_strequ(args->word, "<"))
		{
			if ((cmd->in = open(args->next->word, O_RDONLY)) < 0)
			{
				ft_dprintf(2, "%s: %s: %s\n", g_minishell->name,
					args->next->word, strerror(errno));
				minishell->no_exit = 1;
			}
			remove_redirect(args, &cmd->args);
		}
		args = args->next;
	}
}

void	exec_commands(t_minishell *minishell)
{
	t_cmd	*tmp;
	int		fpipe[2];

	tmp = minishell->cmd_list;
	while (tmp)
	{
		create_redirect2(minishell, tmp);
		process_args(minishell, tmp);
		if (tmp->cmd)
		{
			pipe(fpipe);
			if (ft_strequ(tmp->cmd, EXIT_CMD) && !minishell->no_exit
				&& tmp->type != T_PIPE
				&& (!tmp->prev || tmp->prev->type != T_PIPE))
				exit_cmd2(minishell, tmp);
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
		minishell->forked = 0;
		if (get_next_line_no_eof(0, &minishell->line, 0))
		{
			while (bracket_odd(minishell->line, 1))
				next_bracket(minishell);
			start_parse(minishell, minishell->line);
			ft_strdel(&minishell->line);
			if (g_minishell->quit == 0)
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
