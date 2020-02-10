/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 16:36:48 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/10 01:25:28 by tomsize          ###   ########.fr       */
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
		prev = tmp;
		while (tmp->next)
		{
			tmp->next->prev = prev;
			prev = tmp->next;
			tmp = tmp->next;
		}
		tmp->next = new;
		tmp->next->prev = prev;
	}
	else
		*begin = new;
}

int		token_list_size(t_token **begin)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = *begin;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
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
	new->word = ft_substr(minishell->line, i - minishell->count,
		minishell->count);
	minishell->count = 0;
	return (new);
}

t_token		*create_arg_token(char *word)
{
	t_token	*new;

	if (!(new = ft_calloc(1, sizeof(t_token))))
		return (NULL);
	new->word = word;
	return (new);
}
