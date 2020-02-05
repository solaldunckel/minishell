/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 16:36:48 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/05 18:13:21 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		add_token_list(t_token **begin, t_token *new)
{
	t_token	*tmp;
	t_token *prev;

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

t_token		*create_arg_token(char *word)
{
	t_token	*new;

	if (!(new = ft_calloc(1, sizeof(t_token))))
		return (NULL);
	new->word = ft_strdup(word);
	return (new);
}
