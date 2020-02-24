/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:34:19 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/24 02:12:54 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*tmp2;

	if (!lst || !del)
		return ;
	tmp = *lst;
	while (tmp)
	{
		del(tmp->content);
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
	*lst = NULL;
}
