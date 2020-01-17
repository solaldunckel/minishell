/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 11:18:12 by sdunckel          #+#    #+#             */
/*   Updated: 2020/01/17 11:27:54 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_prompt(t_minishell *minishell)
{
	if (minishell->exit == 0)
		ft_printf("" BOLDGREEN "➜ " RESET BOLDCYAN " %s " RESET, minishell->curdir);
	else
		ft_printf("" BOLDRED "➜ " RESET BOLDCYAN " %s " RESET, minishell->curdir);
}

void	process_split(t_minishell *minishell)
{
	int		i;

	i = 0;
	while (minishell->split[i])
	{
		if (minishell->split[i][0] == '$' && minishell->split[i][1])
			replace_env(minishell, &minishell->split[i]);
		minishell->split[i] = ft_strtrim(minishell->split[i], "'\"");
		i++;
	}
}

int		exec_builtin(t_minishell *minishell)
{
	if (ft_strequ(minishell->split[0], ECHO_CMD))
		echo_cmd(minishell);
	else if (ft_strequ(minishell->split[0], CD_CMD))
		cd_cmd(minishell);
	else if (ft_strequ(minishell->split[0], PWD_CMD))
		pwd_cmd(minishell);
	else if (ft_strequ(minishell->split[0], ENV_CMD))
		env_cmd(minishell);
	else if (ft_strequ(minishell->split[0], EXPORT_CMD))
		export_cmd(minishell);
	else if (ft_strequ(minishell->split[0], UNSET_CMD))
		unset_cmd(minishell);
	else if (ft_strequ(minishell->split[0], EXIT_CMD))
		exit_cmd(minishell);
	else
		return (0);
	return (1);
}

void	exec_commands(t_minishell *minishell, char *cmd)
{
	minishell->split = ft_split_brackets(cmd, " ");
	if (!minishell->split[0])
		return ;
	process_split(minishell);
	if (!exec_builtin(minishell))
		exec_prog(minishell);
	free_split(minishell->split);
}

void	sighandler(int sig_num)
{
	write(1, "\n", 1);
	if (sig_num == SIGQUIT)
		;
	else if (sig_num == SIGINT)
	{
		write(1, "\n", 1);
		print_prompt(g_minishell);
	}
}

void	wait_for_command(t_minishell *minishell)
{
	char 	**cmds;
	int		i;

	while (1)
	{
		signal(SIGQUIT, sighandler);
		signal(SIGINT, sighandler);
		print_prompt(minishell);
		if (get_next_line(0, &minishell->line))
		{
			i = 0;
			cmds = ft_split_brackets(minishell->line, ";");
			while (cmds[i])
			{
				exec_commands(minishell, cmds[i]);
				i++;
			}
			free_split(cmds);
			ft_strdel(&minishell->line);
		}
	}
}

int		main(int argc, char **argv, char **env)
{
	t_minishell 	minishell;

	(void)argv;
	ft_bzero(&minishell, sizeof(t_minishell));
	ft_printf("\nMINISHELL 42 by sdunckel & haguerni\n\n");
	minishell.name = ft_strtrim(argv[0], "./");
	minishell.curdir = getcwd(NULL, 0);
	env_init(&minishell, env);
	g_minishell = &minishell;
	wait_for_command(&minishell);
	return (0);
}
