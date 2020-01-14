/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 10:52:32 by sdunckel          #+#    #+#             */
/*   Updated: 2020/01/14 17:43:56 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_prog(t_minishell *minishell)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;
	char 	**env;

	pid = fork();
	if (pid == 0)
	{
		env = env_array(minishell);
		minishell->split[0] = ft_strjoin("/bin/", minishell->split[0]);
		if (execve(minishell->split[0], minishell->split, env) == -1)
			ft_printf("%s: %s: %s\n", minishell->name, minishell->split[0],
				"command not found");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		strerror(errno);
	else
	{
		wpid = waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return ;
}
