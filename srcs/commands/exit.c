/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 20:29:29 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/19 14:15:21 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env2(void *lst)
{
	t_env	*env;

	env = lst;
	ft_strdel(&env->name);
	ft_strdel(&env->value);
	free(env);
}

int		is_only_digit(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

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

void	exit_cmd2(t_minishell *minishell, t_cmd *cmd)
{
	int		exit_s;

	exit_s = 0;
	if (minishell->no_exit)
		return ;
	ft_dprintf(2, "exit\n");
	if (token_list_size(&cmd->args) > 1)
	{
		ft_dprintf(2, "%s: %s: %s\n", minishell->name, cmd->cmd,
			"too many arguments");
		minishell->exit = 1;
		return ;
	}
	if (cmd->args)
	{
		if (is_only_digit(((t_token*)cmd->args)->word))
		{
			exit_s = ft_atoi(((t_token*)cmd->args)->word);
			exit_s > 255 ? exit_s -= 256 : 0;
		}
		else
		{
			ft_dprintf(2, "\n%s: %s: %s: %s\n", minishell->name, cmd->cmd,
				((t_token*)cmd->args)->word, "numeric argument required");
			exit_s = 255;
		}
	}
	exit_cmd3(minishell, exit_s);
}

void	exit_cmd(t_minishell *minishell)
{
	exit_cmd3(minishell, 0);
}
