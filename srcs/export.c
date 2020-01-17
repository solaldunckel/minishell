/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 13:30:51 by sdunckel          #+#    #+#             */
/*   Updated: 2020/01/17 04:03:11 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_cmd(t_minishell *minishell)
{
	t_list	*tmp;
	char 	**tmp_split;

	tmp = minishell->env_list;
	tmp_split = ft_split(minishell->split[1], '=');
	if (ft_strequ(tmp_split[1], "PATH"))
		parse_bin(minishell);
	while (tmp)
	{
		if (ft_strequ(((t_env*)(tmp->content))->name, tmp_split[0]))
		{
			free(((t_env*)(tmp->content))->value);
			if (tmp_split[1])
				((t_env*)(tmp->content))->value = ft_strdup(tmp_split[1]);
			else
				((t_env*)(tmp->content))->value = ft_strdup("");
			free_split(tmp_split);
			minishell->env_array = env_to_array(minishell);
			return;
		}
		tmp = tmp->next;
	}
	minishell->env_array = env_to_array(minishell);
	ft_lstadd_back(&minishell->env_list, ft_lstnew(create_env(minishell, tmp_split)));
	free_split(tmp_split);
}
