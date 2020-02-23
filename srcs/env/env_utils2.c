/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 22:52:55 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/23 23:27:40 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		env_valid_character(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (i == 0 && ft_isdigit(str[i]))
			return (0);
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int		is_valid_env(char *str)
{
	int		i;
	int		eq_count;

	i = 0;
	eq_count = 0;
	while (str[i])
	{
		if (i == 0 && (ft_isdigit(str[i]) || str[i] == '='))
			return (0);
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '=')
			return (0);
		if (str[i] == '=')
			eq_count++;
		i++;
	}
	if (eq_count)
		return (1);
	return (0);
}

t_env	*create_tmp_env(char **split)
{
	t_env	*env;

	if (!(env = ft_calloc(1, sizeof(t_env))))
		exit_cmd(g_minishell);
	env->name = ft_strdup(split[0]);
	if (split[1])
		env->value = ft_strndup(split[1], 4096);
	else
		env->value = ft_strdup("");
	env->tmp = 1;
	return (env);
}

void	add_tmp_env_variable(t_minishell *minishell, t_cmd *cmd)
{
	char	**split;
	t_list	*tmp;

	tmp = cmd->env_list;
	while (tmp)
	{
		split = ft_split_n(tmp->content, '=', 1);
		if (!(modify_env_list(minishell, split, 0)))
			ft_lstadd_back(&minishell->env_list,
				ft_lstnew(create_tmp_env(split)));
		ft_free_split(&split);
		tmp = tmp->next;
	}
}
