/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:43:38 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/22 15:23:16 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void *))
{
	t_list	**begin;
	t_list	*temp1;
	t_list	*temp3;

	if (!(begin = (t_list **)malloc(sizeof(t_list))))
		return (NULL);
	if (!(lst) || !(*begin = ft_lstnew(f(lst->content))) || f == NULL)
		return (NULL);
	lst = lst->next;
	temp1 = *begin;
	while (lst)
	{
		temp3 = temp1;
		if (!(temp1 = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(begin, del);
			return (NULL);
		}
		temp3->next = temp1;
		lst = lst->next;
	}
	temp1->next = NULL;
	return (*begin);
}
