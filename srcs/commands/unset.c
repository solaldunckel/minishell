/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 20:50:10 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/17 17:31:01 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_env(t_env *env, char *data)
{
	if (ft_strequ(env->name, data))
		return (0);
	return (1);
}

void	free_env(void *lst)
{
	t_env	*env;

	env = ((t_list*)lst)->content;
	if (env->name)
		ft_strdel(&env->name);
	if (env->value)
		ft_strdel(&env->value);
	free(env);
}

void	unset_cmd(t_minishell *minishell, t_cmd *cmd)
{
	t_token *args;
	char	*env;

	args = cmd->args;
	while (args)
	{
		env = get_env(minishell, args->word);
		if (env)
			ft_lst_remove_if(&minishell->env_list, args->word, is_env,
				free_env);
		if (ft_strequ(args->word, "PATH"))
			parse_bin(minishell);
		args = args->next;
	}
	minishell->exit = 0;
}
