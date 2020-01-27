/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 13:30:51 by sdunckel          #+#    #+#             */
/*   Updated: 2020/01/27 22:22:09 by haguerni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_cmd(t_minishell *minishl)
{
	t_list	*tmp;
	char	**tmp_s;

	tmp = minishl->env_list;
	tmp_s = ft_split(minishl->split[1], '=');
	if (ft_strequ(tmp_s[1], "PATH"))
		parse_bin(minishl);
	while (tmp)
	{
		if (ft_strequ(((t_env*)(tmp->content))->name, tmp_s[0]))
		{
			free(((t_env*)(tmp->content))->value);
			if (tmp_s[1])
				((t_env*)(tmp->content))->value = ft_strdup(tmp_s[1]);
			else
				((t_env*)(tmp->content))->value = ft_strdup("");
			free_split(tmp_s);
			minishl->env_array = env_to_array(minishl);
			return ;
		}
		tmp = tmp->next;
	}
	minishl->env_array = env_to_array(minishl);
	ft_lstadd_back(&minishl->env_list, ft_lstnew(create_env(minishl, tmp_s)));
	free_split(tmp_s);
}
