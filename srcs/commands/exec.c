/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsize <tomsize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 01:17:25 by tomsize           #+#    #+#             */
/*   Updated: 2020/02/11 00:50:20 by tomsize          ###   ########.fr       */
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

char	*replace_env(t_minishell *minishell, char *str)
{
	int		i;
	int		count;
	char 	buf[4096];
	char 	*new;

	new = ft_strdup("");
	i = 0;
	count = 0;
	ft_bzero(buf, sizeof(buf));
	while (str[i])
	{
		while (str[i] && str[i] == '$' && !is_escaped(str, i - 1))
		{
			new = ft_strjoin_free(new, buf);
			ft_bzero(buf, count);
			count = 0;
			i++;
			while (str[i] && !is_char_str(str[i], "$ \'\""))
			{
				buf[count] = str[i];
				i++;
				count++;
			}
			new = ft_strjoin_free(new, get_env(minishell, buf));
			ft_bzero(buf, count);
			count = 0;
		}
		buf[count] = str[i];
		count++;
		i++;
	}
	new = ft_strjoin_free(new, buf);
	return (new);
}

void	process_args(t_minishell *minishell, t_cmd *cmd)
{
	t_token	*tmp;
	char 	*to_free;

	if (ft_is_in_stri('$', cmd->cmd) >= 0)
		cmd->cmd = replace_env(minishell, cmd->cmd);
	tmp = cmd->args;
	while (tmp)
	{
	//	printf("%s\n", tmp->word);
		if (ft_is_in_stri('$', tmp->word) >= 0)
			tmp->word = replace_env(minishell, tmp->word);
		// if (tmp->word[0] == '\'' && tmp->word[ft_strlen(tmp->word) - 1] == '\'')
		// to_free = tmp->word;
		// tmp->word = ft_strtrim(tmp->word, "\"");
		// free(to_free);
		tmp = tmp->next;
	}
}

void	exec_commands(t_minishell *minishell)
{
	t_cmd	*tmp;
	pid_t	pid;
	int		status;

	tmp = minishell->cmd_list;
	while (tmp)
	{
		process_args(minishell, tmp);
		if (tmp->type == T_PIPE || (tmp->prev && tmp->prev->type == T_PIPE))
			if (pipe(tmp->pipe))
				return (exit(0));
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
