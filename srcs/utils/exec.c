/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haguerni <haguerni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 17:48:54 by haguerni          #+#    #+#             */
/*   Updated: 2020/02/15 14:05:34 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_prog2(t_minishell *minishell, t_cmd *tmp, pid_t pid, int fpip[2])
{
	int		status;
	char	bin;
	int		spip[2];

	if (pid < 0)
		strerror(errno);
	else
	{
		pipe(spip);
		if (!tmp->out && tmp->type == T_PIPE)
			exec_prog(minishell, tmp->next, fpip, spip);
		close(fpip[1]);
		waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status))
			if (!WIFSIGNALED(status) || g_minishell->quit == 1)
				break ;
		if (WIFEXITED(status))
			minishell->exit = WEXITSTATUS(status);
	}
}

void	handle_fd(t_cmd *tmp, int fpip[2], int spip[2])
{
	if (tmp->out)
	{
		dup2(tmp->out, STDOUT_FILENO);
		close(tmp->out);
	}
	if (tmp->in)
	{
		dup2(tmp->in, STDIN_FILENO);
		close(tmp->in);
	}
	if (tmp->prev && tmp->prev->type == T_PIPE)
	{
		dup2(fpip[0], 0);
		close(fpip[1]);
		if (!tmp->out && tmp->type == T_PIPE)
		{
			dup2(spip[1], 1);
			close(spip[0]);
		}
	}
	else if (!tmp->out && tmp->type == T_PIPE)
	{
		dup2(fpip[1], 1);
		close(fpip[0]);
	}
}

void	exec(t_minishell *minishell, t_cmd *tmp, char *bin)
{
	if (ft_strequ(tmp->cmd, ECHO_CMD))
		echo_cmd(minishell, tmp);
	else if (ft_strequ(tmp->cmd, CD_CMD))
		exit(0);
	else if (ft_strequ(tmp->cmd, EXIT_CMD))
		exit_cmd();
	else if (ft_strequ(tmp->cmd, ENV_CMD))
		env_cmd(&minishell->env_list);
	else if (ft_strequ(tmp->cmd, PWD_CMD))
		pwd_cmd(minishell);
	else if (ft_strequ(tmp->cmd, EXPORT_CMD))
		export_cmd(minishell, tmp, 1);
	else if (ft_strequ(tmp->cmd, UNSET_CMD))
		exit(0);
	else
	{
		execve(bin, tmp->args_array, minishell->env_array);
		handle_errno(minishell, tmp->cmd, errno);
		exit(EXIT_FAILURE);
	}
	exit(0);
}

void	exec_prog(t_minishell *minishell, t_cmd *tmp, int fpip[2], int spip[2])
{
	pid_t	pid;
	int		status;
	char	*bin;

	pid = fork();
	if (pid == 0)
	{
		if (tmp->out == -1 || tmp->in == -1)
			exit(-1);
		handle_fd(tmp, fpip, spip);
		tmp->args_array = join_args(tmp);
		bin = get_bin(minishell, tmp->cmd);
		exec(minishell, tmp, bin);
	}
	else
	{
		if (tmp->type == T_PIPE && tmp->prev && tmp->prev->type == T_PIPE)
		{
			close(fpip[1]);
			exec_prog2(minishell, tmp, pid, spip);
		}
		else
			exec_prog2(minishell, tmp, pid, fpip);
	}
	free(tmp->args_array);
}
