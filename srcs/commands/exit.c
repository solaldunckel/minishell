/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 20:29:29 by sdunckel          #+#    #+#             */
/*   Updated: 2020/03/10 04:33:51 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_cmd3(t_minishell *minishell, int status)
{
	ft_strdel(&minishell->name);
	ft_strdel(&minishell->curdir);
	ft_strdel(&minishell->line);
	ft_strdel(&minishell->exit_str);
	clear_cmd_list(&minishell->cmd_list, free);
	ft_lstclear(&minishell->env_list, free_env2);
	clear_token_list(&minishell->token_list, free);
	ft_free_split(&minishell->env_array);
	ft_free_split(&minishell->bin);
	exit(status);
}

int		exit_status(t_minishell *minishell, t_cmd *cmd)
{
	uint8_t		exit_s;

	exit_s = minishell->exit;
	if (cmd->args)
	{
		if (is_only_digit(((t_token*)cmd->args)->word)
		|| (((t_token*)cmd->args)->word[0] == '-'
		&& ft_isdigit(((t_token*)cmd->args)->word[1])))
			exit_s = ft_atoi(((t_token*)cmd->args)->word);
		else
		{
			ft_dprintf(2, "%s: %s: %s: %s\n", minishell->name, cmd->cmd,
				((t_token*)cmd->args)->word, "numeric argument required");
			exit_s = 255;
		}
	}
	return ((int)exit_s);
}

void	exit_cmd2(t_minishell *minishell, t_cmd *cmd, int ex)
{
	int		exit_s;

	exit_s = 0;
	!ex ? ft_dprintf(2, "exit\n") : 0;
	if (token_list_size(&cmd->args) > 1)
	{
		ft_dprintf(2, "%s: %s: %s\n", minishell->name, cmd->cmd,
			"too many arguments");
		minishell->exit = 1;
		return ;
	}
	exit_s = exit_status(minishell, cmd);
	exit_cmd3(minishell, exit_s);
}

void	exit_cmd4(t_minishell *minishell)
{
	ft_dprintf(2, "exit\n");
	exit_cmd3(minishell, minishell->exit);
}

void	exit_cmd(t_minishell *minishell)
{
	exit_cmd3(minishell, 1);
}
