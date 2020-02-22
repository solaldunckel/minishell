/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 22:08:23 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/22 22:10:15 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		add_token_front(t_token **begin, t_token *new)
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

t_token		*token_split_to_list(char **split)
{
	t_token *new;
	int		i;
	int		count;

	i = 0;
	count = ft_count_split(split);
	new = NULL;
	while (i < count)
	{
		add_token_list(&new, create_arg_token(ft_strdup(split[i]), T_WORD));
		i++;
	}
	return (new);
}
