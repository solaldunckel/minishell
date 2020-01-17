/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_remove_if.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 03:35:22 by sdunckel          #+#    #+#             */
/*   Updated: 2020/01/17 03:35:51 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_remove_if(t_list **begin_list, void *data, int (*cmp)(),
			void (*del)())
{
	t_list	*current;
	t_list	*next;

	if (!*begin_list)
		return ;
	while (*begin_list && cmp((*begin_list)->content, data) == 0)
	{
		next = (*begin_list)->next;
		del(*begin_list);
		*begin_list = next;
	}
	if (!*begin_list)
		return ;
	current = *begin_list;
	while (current && current->next)
	{
		if (cmp(current->next->content, data) == 0)
		{
			next = current->next->next;
			del(current->next);
			current->next = next;
		}
		else
			current = current->next;
	}
}
