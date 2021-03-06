/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 20:31:25 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/23 23:29:56 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_cmd(t_list **begin)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = *begin;
	if (!*begin)
		return ;
	while (tmp)
	{
		if (((t_env*)(tmp->content))->value && !((t_env*)(tmp->content))->tmp)
			ft_printf("%s=%s\n", ((t_env*)(tmp->content))->name,
				((t_env*)(tmp->content))->value);
		tmp = tmp->next;
	}
}
