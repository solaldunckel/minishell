/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 20:29:29 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/17 19:42:16 by sdunckel         ###   ########.fr       */
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

void	exit_cmd(t_minishell *minishell)
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
	exit(0);
}
