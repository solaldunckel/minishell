/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 12:56:11 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/08 19:11:40 by haguerni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		add_cmd_list(t_cmd **begin, t_cmd *new)
{
	t_cmd	*tmp;
	t_cmd	*prev;

	prev = NULL;
	if (!new || !begin)
		return ;
	new->cmd = supp_newline(new->cmd);
	if (*begin)
	{
		tmp = *begin;
		tmp->prev = prev;
		while (tmp->next)
		{
			tmp->prev = prev;
			prev = tmp;
			tmp = tmp->next;
		}
		tmp->next = new;
		new->prev = tmp;
		new->next = NULL;
	}
	else
		*begin = new;
}

void		clear_cmd_list(t_cmd **begin, void (*del)(void *))
{
	t_cmd	*tmp;
	t_token *args;

	if (!begin || !del)
		return ;
	tmp = *begin;
	while (tmp)
	{
		args = tmp->args;
		while (args)
		{
			del(args);
			args = args->next;
		}
		free(tmp);
		tmp = tmp->next;
	}
	*begin = NULL;
}
