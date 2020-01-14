/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 13:29:33 by sdunckel          #+#    #+#             */
/*   Updated: 2020/01/14 13:29:38 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_cmd(t_minishell *minishell)
{
	int		i;
	t_list	*tmp;
	char 	**lenv;

	i = 0;
	tmp = minishell->env_list;
	while (tmp)
	{
		lenv = tmp->content;
		ft_printf("%s=%s\n", lenv[0], lenv[1]);
		tmp = tmp->next;
	}
}
