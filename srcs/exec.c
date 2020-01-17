/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 10:52:32 by sdunckel          #+#    #+#             */
/*   Updated: 2020/01/17 04:48:08 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_prog(t_minishell *minishell)
{
	pid_t	pid;
	int		status;
	char 	*bin;

	pid = fork();
	if (pid == 0)
	{
		bin = get_bin(minishell, minishell->split[0]);
		if (execve(bin, minishell->split, minishell->env_array) == -1)
		{
			ft_printf("%s: %s: %s\n", minishell->name, minishell->split[0],
				strerror(errno));
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		strerror(errno);
	else
	{
		waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status));
		if (WIFEXITED(status))
			minishell->exit = WEXITSTATUS(status);
	}
	return ;
}
