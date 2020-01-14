/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 13:30:51 by sdunckel          #+#    #+#             */
/*   Updated: 2020/01/14 15:51:37 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_cmd(t_minishell *minishell)
{
	int		i;
	t_list	*tmp;
	char 	**lenv;
	char 	**tmp_split;

	i = 0;
	tmp = minishell->env_list;
	tmp_split = ft_split(minishell->split[1], '=');
	while (tmp)
	{
		lenv = tmp->content;
		if (ft_strequ(lenv[0], tmp_split[0]))
		{
			free(lenv[1]);
			if (tmp_split[1])
				lenv[1] = ft_strdup(tmp_split[1]);
			else
				lenv[1] = ft_strdup("");
			free_split(tmp_split);
			return;
		}
		tmp = tmp->next;
	}
	ft_lstadd_back(&minishell->env_list, ft_lstnew(tmp_split));
}
