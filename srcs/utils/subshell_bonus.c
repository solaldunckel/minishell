/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 20:23:01 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/28 20:23:30 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	launch_subshell(t_minishell *minishell, t_cmd **tmp)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		exec_real_command(minishell, tmp);
		exit(minishell->exit);
	}
	else if (pid < 0)
		strerror(errno);
	else
	{
		waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status))
			if (!WIFSIGNALED(status) || g_minishell->quit != 0)
				break ;
		if (WIFEXITED(status))
			minishell->exit = WEXITSTATUS(status);
	}
}

void	and_or_subshell(t_minishell *minishell, t_cmd **tmp)
{
	if ((*tmp)->prev && (*tmp)->prev->type == T_AND && minishell->exit)
		*tmp = (*tmp)->next;
	else if ((*tmp)->prev && (*tmp)->prev->type == T_OR && !minishell->exit)
		*tmp = (*tmp)->next;
}
