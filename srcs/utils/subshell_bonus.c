/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 20:23:01 by sdunckel          #+#    #+#             */
/*   Updated: 2020/03/09 18:26:24 by haguerni         ###   ########.fr       */
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

void	handle_wild(t_token *tmp)
{
	char	**split;
	char	*tmp2;

	split = ft_split(tmp->word, '/');
	tmp2 = create_wildpath(tmp->word);
	process_wildcard(tmp, tmp2, 0, split);
	free(tmp2);
	ft_free_split(&split);
}

void	lol_mdr(char *tmp, char *line, int notenv, int pip[2])
{
	ft_strdel(&tmp);
	if (ft_is_in_stri('$', line) > -1 && !notenv)
		line = replace_env(line, 0);
	g_minishell->quit != 2 ? ft_putstr_fd(line, pip[1]) : 0;
	ft_strdel(&line);
	close(pip[1]);
}
