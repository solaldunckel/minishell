/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 16:36:48 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/04 17:03:39 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		add_token_list(t_token **begin, t_token *new)
{
	t_token	*tmp;

	if (!new || !begin)
		return ;
	if (*begin)
	{
		tmp = *begin;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*begin = new;
}

void		clear_token_list(t_token **begin, void (*del)(void *))
{
	t_token	*tmp;

	if (!begin || !del)
		return ;
	tmp = *begin;
	while (tmp)
	{
		del(tmp->word);
		free(tmp);
		tmp = tmp->next;
	}
	*begin = NULL;
}

t_token		*create_token(t_minishell *minishell, int i)
{
	t_token	*new;

	if (!minishell->count)
		return (NULL);
	if (!(new = ft_calloc(1, sizeof(t_token))))
		return (NULL);
	new->word = ft_substr(minishell->line, i - minishell->count, minishell->count);
	minishell->count = 0;
	return (new);
}
