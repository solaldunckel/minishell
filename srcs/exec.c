/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 10:52:32 by sdunckel          #+#    #+#             */
/*   Updated: 2020/01/27 22:19:12 by haguerni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_prog2(t_minishell *minishell, char **split, pid_t pid)
{
	int		status;
	char	bin;

	if (pid < 0)
		strerror(errno);
	else
	{
		waitpid(pid, &status, WUNTRACED);
		if (minishell->fd_out)
			close(minishell->fd_out);
		if (minishell->fd_in)
			close(minishell->fd_in);
		while (!WIFEXITED(status))
			if (!WIFSIGNALED(status))
				break ;
		if (WIFEXITED(status))
			minishell->exit = WEXITSTATUS(status);
	}
}

void	exec_prog(t_minishell *minishell, char **split)
{
	pid_t	pid;
	int		status;
	char	*bin;

	pid = fork();
	if (pid == 0)
	{
		if (minishell->out)
		{
			dup2(minishell->fd_out, STDOUT_FILENO);
			close(minishell->fd_out);
		}
		else if (minishell->in)
		{
			dup2(minishell->fd_in, STDIN_FILENO);
			close(minishell->fd_in);
		}
		bin = get_bin(minishell, split[0]);
		execve(bin, split, minishell->env_array);
		handle_errno(minishell, minishell->split[0], errno);
		exit(EXIT_FAILURE);
	}
	else if (pid != 0)
		exec_prog2(minishell, split, pid);
}
