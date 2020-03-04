/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haguerni <haguerni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 17:48:54 by haguerni          #+#    #+#             */
/*   Updated: 2020/03/04 16:10:30 by haguerni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(int fpip[2], int spip[2])
{
	close(fpip[1]);
	close(spip[1]);
	close(spip[0]);
}

void	exec_prog2(t_minishell *minishell, t_cmd *tmp, pid_t pid, int fpip[2])
{
	int		status;
	int		spip[2];

	if (pipe(spip) < 0)
		return ;
	if (tmp->type == T_PIPE)
	{
		process_args(tmp->next);
		create_redirect(minishell, tmp->next);
		while (tmp->next && !tmp->next->cmd)
		{
			process_args(tmp->next);
			create_redirect(minishell, tmp->next);
			tmp = tmp->next;
		}
		if (tmp->next)
			exec_prog(minishell, tmp->next, fpip, spip);
	}
	close_fds(fpip, spip);
	//(void)pid;
	//printf("YES %s\n", tmp->cmd);
	tmp->type != T_PIPE ? waitpid(pid, &status, WUNTRACED) : 0;
	while (!WIFEXITED(status))
		if (!WIFSIGNALED(status) || g_minishell->quit != 0 || tmp->type == T_PIPE)
			break ;
	if (WIFEXITED(status) && tmp->type != T_PIPE)
		minishell->exit = WEXITSTATUS(status);
}

void	handle_fd(t_cmd *tmp, int fpip[2], int spip[2])
{
	if (tmp->prev && tmp->prev->type == T_PIPE)
	{
		dup2(fpip[0], 0);
		close(fpip[1]);
		if (tmp->type == T_PIPE)
		{
			dup2(spip[1], 1);
			close(spip[0]);
		}
	}
	else if (tmp->type == T_PIPE)
	{
		dup2(fpip[1], 1);
		close(fpip[0]);
	}
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
}

void	exec(t_minishell *minishell, t_cmd *tmp)
{
	if (ft_strequ(tmp->cmd, ECHO_CMD))
		echo_cmd(minishell, tmp);
	else if (ft_strequ(tmp->cmd, CD_CMD))
		cd_cmd(minishell, tmp);
	else if (ft_strequ(tmp->cmd, EXIT_CMD))
		exit_cmd2(minishell, tmp);
	else if (ft_strequ(tmp->cmd, ENV_CMD))
		env_cmd(&minishell->env_list);
	else if (ft_strequ(tmp->cmd, PWD_CMD))
		pwd_cmd(minishell);
	else if (ft_strequ(tmp->cmd, EXPORT_CMD))
		export_cmd(minishell, tmp, 1);
	else if (ft_strequ(tmp->cmd, UNSET_CMD))
		exit(0);
	else if (tmp->cmd && minishell->env_array != NULL
		&& tmp->args_array != NULL)
	{
		execve(tmp->bin, tmp->args_array, minishell->env_array);
		handle_errno(minishell, tmp->cmd, errno);
		exit(minishell->exit);
	}
	exit(0);
}

void	exec_prog(t_minishell *minishell, t_cmd *cmd, int fpip[2], int spip[2])
{
	pid_t	pid;

	minishell->forked = 1;
	cmd->bin = get_bin(minishell, cmd->cmd);
	cmd->args_array = join_args(cmd);
	pid = fork();
	if (pid == 0)
	{
		cmd->out == -1 || cmd->in == -1 ? exit(1) : 0;
		handle_fd(cmd, fpip, spip);
		exec(minishell, cmd);
	}
	else if (pid < 0)
		strerror(errno);
	else
	{
		signal(SIGINT, degage_frr);
		cmd->cmd && !ft_strequ(cmd->cmd + 2, minishell->name)
			? signal(SIGQUIT, degage_frr) : signal(SIGQUIT, SIG_IGN);
		if (cmd->type == T_PIPE && cmd->prev && cmd->prev->type == T_PIPE
			&& !close(fpip[1]) && !close(fpip[0]))
			exec_prog2(minishell, cmd, pid, spip);
		else
			exec_prog2(minishell, cmd, pid, fpip);
	}
}
