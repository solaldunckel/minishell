/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 17:06:02 by sdunckel          #+#    #+#             */
/*   Updated: 2020/03/02 20:31:44 by haguerni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	up_history(void)
{
	if (!g_tc->history)
		return ;
	if (g_minishell->line && !g_tc->cur_history)
		g_tc->backup_cmd = ft_strdup(g_minishell->line);
	if (!g_tc->cur_history)
		g_tc->cur_history = g_tc->history;
	else if (g_tc->cur_history->next)
		g_tc->cur_history = g_tc->cur_history->next;
	g_minishell->line = ft_strdup(g_tc->cur_history->cmd);
	g_tc->cur_pos = ft_strlen(g_minishell->line);
	tputs(tgoto(g_tc->dl, 0, 5), 5, putchar_tc);;
	g_tc->mod_offset = 0;
	g_tc->rowoffset = (g_tc->cur_pos + g_tc->plen) / g_tc->col;
	g_tc->currow = g_tc->start_row + g_tc->rowoffset;
}

void	down_history(void)
{
	if (!g_tc->cur_history)
		return ;
	if (g_tc->cur_history->prev)
	{
		g_tc->cur_history = g_tc->cur_history->prev;
		g_minishell->line = ft_strdup(g_tc->cur_history->cmd);
		g_tc->cur_pos = ft_strlen(g_minishell->line);
	}
	else if (g_tc->backup_cmd)
	{
		g_minishell->line = ft_strdup(g_tc->backup_cmd);
		g_tc->cur_history = NULL;
		g_tc->cur_pos = ft_strlen(g_minishell->line);
	}
	else
	{
		g_tc->cur_pos = 0;
		g_tc->cur_history = NULL;
		g_minishell->line = NULL;
	}
	tputs(tgoto(g_tc->dl, 0, 5), 5, putchar_tc);
	g_tc->mod_offset = 0;
	g_tc->rowoffset = (g_tc->cur_pos + g_tc->plen) / g_tc->col;
	g_tc->currow = g_tc->start_row + g_tc->rowoffset;
}

void	add_cmd_to_history(char *cmd)
{
	t_hist	*new;

	if (!cmd)
		return ;
	if (!(new = ft_calloc(1, sizeof(t_hist))))
		return ;
	new->cmd = ft_strdup(cmd);
	add_history_list(&g_tc->history, new);
}

void	add_history_list(t_hist **begin, t_hist *new)
{
	if (*begin)
	{
		new->next = *begin;
		(*begin)->prev = new;
		*begin = new;
	}
	else
		*begin = new;
}

void	clear_history_list(t_hist **begin)
{
	t_hist	*tmp;
	t_hist	*tmp2;

	tmp = *begin;
	while (tmp)
	{
		ft_strdel(&tmp->cmd);
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
}
