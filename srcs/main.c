/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 11:18:12 by sdunckel          #+#    #+#             */
/*   Updated: 2020/01/22 15:54:58 by haguerni         ###   ########.fr       */
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

void	redirect(t_minishell *minishell, char **split, int i)
{
	if (ft_strequ(split[i], ">"))
	{
		minishell->out = 1;
		minishell->fd_out = open(split[i + 1], O_TRUNC | O_RDWR | O_CREAT, 0644);
	}
	else if (ft_strequ(split[i], ">>"))
	{
		minishell->out = 1;
		minishell->fd_out = open(split[i + 1], O_RDWR | O_CREAT | O_APPEND, 0644);
	}
	else if (ft_strequ(split[i], "<"))
	{
		minishell->in = 1;
		minishell->fd_in = open(split[i + 1], O_RDONLY);
	}
	split[i] = ft_strdup("");
	split[i + 1] = ft_strdup("");
}

char	**process_split(t_minishell *minishell, char **split)
{
	int		i;
	char	*to_free;
	char	*final;

	final = ft_strdup("");
	i = 0;
	minishell->out = 0;
	minishell->in = 0;
	while (split[i])
	{
		to_free = split[i];
		split[i] = ft_strtrim(split[i], "'\"");
		free(to_free);
		to_free = split[i];
		split[i] = replace_env(minishell, split[i]);
		free(to_free);
		if (split[i][0] == '>' || ft_strequ(split[i], ">>")
			|| split[i][0] == '<')
		{
			redirect(minishell, split, i);
			i++;
		}
		final = ft_strjoin_free(final, split[i]);
		final = ft_strjoin_free(final, " ");
		i++;
	}
	split = ft_split_brackets(final, " ");
	return (split);
}

int		exec_builtin(t_minishell *minishell, char **split)
{
	if (ft_strequ(split[0], ECHO_CMD))
		echo_cmd(minishell);
	else if (ft_strequ(split[0], CD_CMD))
		cd_cmd(minishell);
	else if (ft_strequ(split[0], PWD_CMD))
		pwd_cmd(minishell);
	else if (ft_strequ(split[0], ENV_CMD))
		env_cmd(minishell);
	else if (ft_strequ(split[0], EXPORT_CMD))
		export_cmd(minishell);
	else if (ft_strequ(split[0], UNSET_CMD))
		unset_cmd(minishell);
	else if (ft_strequ(split[0], EXIT_CMD))
		exit_cmd(minishell);
	else
		return (0);
	return (1);
}

void	handle_pipe(t_minishell *minishell, char **cmds)
{
	int		i;
	pid_t	pid;
	int		fd[2];
	char 	**split;

	i = 0;
	while (cmds[i])
	{
		split = ft_split_brackets(cmds[i], " ");
		if (!split[0])
			return ;
		process_split(minishell, split);
		if (!exec_builtin(minishell, split))
			exec_prog(minishell, split);
		i++;
	}
}

void	exec_commands(t_minishell *minishell, char *cmd)
{
	int		i;
	char 	**cmds;

	i = 0;
	cmds = ft_split_brackets(cmd, "|");
	if (count_split(cmds) > 1)
	{
		handle_pipe(minishell, cmds);
		return;
	}
	minishell->split = ft_split_brackets(cmd, " ");
	minishell->split = process_split(minishell, minishell->split);
	if (!exec_builtin(minishell, minishell->split))
		exec_prog(minishell, minishell->split);
	free_split(minishell->split);
}

void	sighandler(int sig_num)
{
	ft_printf("\b\b  \b\b");
	if (sig_num == 2)
	{
		ft_printf("\n" BOLDGREEN "➜ " RESET BOLDCYAN " %s " RESET,
		g_minishell->curdir);
	}
}

void	wait_for_command(t_minishell *minishell)
{
	char 	**cmds;
	t_list	*tmp;

	while (1)
	{
		signal(SIGQUIT, sighandler);
		signal(SIGINT, sighandler);
		print_prompt(minishell);
		if (get_next_line_no_eof(0, &minishell->line))
		{
			parse_cmds(minishell);
			tmp = minishell->cmd_list;
			while (tmp)
			{
				exec_commands(minishell, ((t_cmd*)(tmp->content))->line);
				tmp = tmp->next;
			}
			ft_lstclear(&minishell->cmd_list, free_cmd);
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
