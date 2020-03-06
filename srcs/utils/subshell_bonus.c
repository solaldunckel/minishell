/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 20:23:01 by sdunckel          #+#    #+#             */
/*   Updated: 2020/03/06 16:03:23 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	and_or_subshell(t_minishell *minishell, t_cmd **tmp)
{
	int		prev_scope;

	prev_scope = 0;
	if (!(*tmp)->prev)
		return ;
	if ((*tmp)->prev->scope != (*tmp)->scope)
	{
		prev_scope = (*tmp)->prev->scope;
		if ((*tmp)->prev->type == T_OR && !minishell->exit)
		{
			while ((*tmp) && (*tmp)->scope > prev_scope)
				*tmp = (*tmp)->next;
		}
		else if ((*tmp)->prev->type == T_AND && minishell->exit)
		{
			while ((*tmp) && (*tmp)->scope > prev_scope)
				*tmp = (*tmp)->next;
		}
		if (!*tmp)
			return ;
	}
	while (*tmp && (*tmp)->prev->type == T_AND && minishell->exit)
		*tmp = (*tmp)->next;
	while (*tmp && (*tmp)->prev->type == T_OR && !minishell->exit)
		*tmp = (*tmp)->next;
}
