/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 13:29:33 by sdunckel          #+#    #+#             */
/*   Updated: 2020/01/27 21:59:19 by haguerni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_cmd(t_minishell *minishell)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = minishell->env_list;
	while (tmp)
	{
		ft_printf("%s=%s\n", ((t_env*)(tmp->content))->name,
			((t_env*)(tmp->content))->value);
		tmp = tmp->next;
	}
}
