/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:17:35 by sdunckel          #+#    #+#             */
/*   Updated: 2020/01/17 03:38:11 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_env(t_env *env, char *data)
{
	if (ft_strequ(env->name, data))
		return (0);
	return (1);
}

void	free_env(t_list *lst)
{
	t_env	*env;

	env = lst->content;
	if (env->name)
		ft_strdel(&env->name);
	if (env->value)
		ft_strdel(&env->value);
	free(lst);
}

void	unset_cmd(t_minishell *minishell)
{
	int		i;
	char 	*env;

	i = 1;
	while (minishell->split[i])
	{
		env = get_env(minishell, minishell->split[i]);
		if (env)
			ft_lst_remove_if(&minishell->env_list, minishell->split[i],
				is_env, free_env);
		i++;
	}
}
