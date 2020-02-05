/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 12:56:11 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/05 18:14:13 by sdunckel         ###   ########.fr       */
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
	if (*begin)
	{
		tmp = *begin;
		while (tmp->next)
		{
			tmp->prev = prev;
			prev = tmp;
			tmp = tmp->next;
		}
		tmp->prev = tmp;
		tmp->next = new;
	}
	else
		*begin = new;
}

void		clear_cmd_list(t_cmd **begin, void (*del)(void *))
{
	t_cmd	*tmp;

	if (!begin || !del)
		return ;
	tmp = *begin;
	while (tmp)
	{
		//del(tmp->cmd);
		free(tmp);
		tmp = tmp->next;
	}
	*begin = NULL;
}
