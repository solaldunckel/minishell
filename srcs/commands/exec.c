/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsize <tomsize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 01:17:25 by tomsize           #+#    #+#             */
/*   Updated: 2020/02/10 14:17:21 by tomsize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(t_minishell *minishell, t_cmd *tmp)
{
	char	*bin;
	char 	**split;

	if (ft_strequ(tmp->cmd, ECHO_CMD))
		echo_cmd(minishell, tmp);
	else if (ft_strequ(tmp->cmd, CD_CMD))
		cd_cmd(minishell, tmp);
	else if (ft_strequ(tmp->cmd, EXIT_CMD))
		exit_cmd();
	else if (ft_strequ(tmp->cmd, ENV_CMD))
		env_cmd(&minishell->env_list);
	else if (ft_strequ(tmp->cmd, PWD_CMD))
		pwd_cmd(minishell);
	else if (ft_strequ(tmp->cmd, EXPORT_CMD))
		export_cmd(minishell, tmp);
	else if (ft_strequ(tmp->cmd, UNSET_CMD))
		unset_cmd(minishell, tmp);
	else
	{
		split = args_to_array(minishell, tmp);
		bin = get_bin(minishell, tmp->cmd);
		execve(bin, split, minishell->env_array);
		handle_errno(minishell, tmp->cmd, errno);
		exit(EXIT_FAILURE);
	}
}

void	open_pipes(t_minishell *minishell, t_cmd *tmp)
{
	if (tmp->out)
	{
		if (tmp->out < 0)
			exit(0);
		dup2(tmp->out, STDOUT_FILENO);
		close(tmp->out);
	}
	if (tmp->in)
	{
		if (tmp->in < 0)
			exit(0);
		dup2(tmp->in, STDIN_FILENO);
		close(tmp->in);
	}
	if (tmp->type == T_PIPE)
		dup2(tmp->pipe[1], 1);
	if (tmp->prev && tmp->prev->type == T_PIPE)
		dup2(tmp->prev->pipe[0], 0);
}

void	close_pipes(t_minishell *minishell, t_cmd *tmp, int *status, int pid)
{
	waitpid(pid, status, WUNTRACED);
	if (tmp->type == T_PIPE || (tmp->prev && tmp->prev->type == T_PIPE))
	{
		close(tmp->pipe[1]);
		if (!tmp->next || tmp->type == T_SEP)
			close(tmp->pipe[0]);
	}
	if (tmp->prev && tmp->prev->type == T_PIPE)
		close(tmp->prev->pipe[0]);
	if (tmp->out)
		close(tmp->out);
	if (tmp->in)
		close(tmp->in);
	while (!WIFEXITED(*status))
		if (!WIFSIGNALED(*status))
			break ;
	if (WIFEXITED(*status))
		minishell->exit = WEXITSTATUS(*status);
}

void	exec_commands(t_minishell *minishell)
{
	t_cmd	*tmp;
	pid_t	pid;
	int		status;

	tmp = minishell->cmd_list;
	while (tmp)
	{
		if (tmp->type == T_PIPE || (tmp->prev && tmp->prev->type == T_PIPE))
		{
			if (pipe(tmp->pipe))
				return (exit(0));
		}
		pid = fork();
		if (pid < 0)
			exit(0);
		else if (pid == 0)
		{
			open_pipes(minishell, tmp);
			exec_builtin(minishell, tmp);
			exit(minishell->exit);
		}
		else
			close_pipes(minishell, tmp, &status, pid);
		tmp = tmp->next;
	}
}
