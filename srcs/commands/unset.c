/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 20:50:10 by sdunckel          #+#    #+#             */
/*   Updated: 2020/03/04 16:50:24 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_env(t_env *env, char *data)
{
	if (ft_strequ(env->name, data))
		return (0);
	return (1);
}

int		is_valid_env2(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (i == 0 && (ft_isdigit(str[i])))
			return (0);
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	unset_cmd(t_minishell *minishell, t_cmd *cmd)
{
	t_token *args;
	char	*env;

	args = cmd->args;
	minishell->exit = 0;
	while (args)
	{
		if (is_valid_env2(args->word))
		{
			env = get_env(minishell, args->word);
			if (env)
				ft_lst_remove_if(&minishell->env_list, args->word, is_env,
					free_env);
			if (ft_strequ(args->word, "PATH"))
				parse_bin(minishell);
		}
		else
		{
			ft_dprintf(2, "%s: %s: `%s': %s\n", minishell->name, cmd->cmd,
				args->word, "not a valid identifier");
			minishell->exit = 1;
		}
		args = args->next;
	}
}
