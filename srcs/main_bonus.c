/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 11:18:12 by sdunckel          #+#    #+#             */
/*   Updated: 2020/03/04 20:41:22 by haguerni         ###   ########.fr       */
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
	g_tc->plen = 4 + ft_strlen(minishell->curdir);
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

void	exec_real_command(t_minishell *minishell, t_cmd **tmp)
{
	int		fpipe[2];

	and_or_subshell(minishell, tmp);
	if (!*tmp)
		return ;
	process_args(*tmp);
	create_redirect(minishell, *tmp);
	if ((*tmp)->cmd && (*tmp)->out != -1 && (*tmp)->in != -1)
	{
		if (pipe(fpipe))
			return ;
		exec_commands2(minishell, *tmp, fpipe);
		close(fpipe[0]);
		close(fpipe[1]);
	}
	if (!(*tmp)->cmd && (*tmp)->type != T_PIPE)
	{
		process_args_env(*tmp);
		add_tmp_env_variable(minishell, *tmp);
	}
	while ((*tmp)->type == T_PIPE)
		*tmp = (*tmp)->next;
}

void	exec_commands(t_minishell *minishell)
{
	t_cmd	*tmp;

	tmp = minishell->cmd_list;
	minishell->scope_p = 0;
	while (tmp)
	{
		if (!tmp)
			break ;
		exec_real_command(minishell, &tmp);
		if (!tmp)
			break ;
		tmp = tmp->next;
	}
}

int		main(int argc, char **argv, char **env)
{
	t_termcap		tc;
	t_minishell		minishell;
	int				fd;

	(void)argc;
	(void)argv;
	if ((fd = dup(0)) == -1)
		return (0);
	close(fd);
	ft_bzero(&minishell, sizeof(t_minishell));
	ft_bzero(&tc, sizeof(t_termcap));
	ft_printf("\nMINISHELL 42 by sdunckel & haguerni\n\n");
	minishell.name = ft_strtrim(argv[0], "./");
	minishell.curdir = getcwd(NULL, 0);
	env_init(&minishell, env);
	g_minishell = &minishell;
	g_tc = &tc;
	if (isatty(0))
	{
		init_term();
		wait_for_command(&minishell);
	}
	else
		wait_for_command_tty(&minishell);
	return (0);
}
