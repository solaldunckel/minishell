/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 22:52:55 by sdunckel          #+#    #+#             */
/*   Updated: 2020/03/04 00:28:55 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_cmd_export(t_list **begin)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = *begin;
	if (!*begin)
		return ;
	while (tmp)
	{
		if (!ft_strequ(((t_env*)(tmp->content))->name, "_"))
		{
			if (((t_env*)(tmp->content))->value
				&& !((t_env*)(tmp->content))->tmp)
				ft_printf("declare -x %s=\"%s\"\n",
					((t_env*)(tmp->content))->name,
					((t_env*)(tmp->content))->value);
			else if (!((t_env*)(tmp->content))->value
				&& !((t_env*)(tmp->content))->tmp)
				ft_printf("declare -x %s\n",
					((t_env*)(tmp->content))->name);
		}
		tmp = tmp->next;
	}
}

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
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '='
			&& str[i] != '+' && str[i] != '\'' && str[i] != '\"')
			return (0);
		if ((str[i] == '\'' || str[i] == '\"') && eq_count < 1)
			return (0);
		if (eq_count == 0 && str[i] == '+' && str[i + 1] != '=')
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
	char	*to_free;
	int		join;

	join = 0;
	tmp = cmd->env_list;
	while (tmp)
	{
		split = ft_split_n(tmp->content, '=', 1);
		if (ft_str_end(split[0], "+"))
		{
			to_free = split[0];
			split[0] = ft_strndup(split[0], ft_strlen(split[0]) - 1);
			free(to_free);
			join = 1;
		}
		if (!(modify_env_list(minishell, split, 2, join)))
			ft_lstadd_back(&minishell->env_list,
				ft_lstnew(create_tmp_env(split)));
		ft_free_split(&split);
		tmp = tmp->next;
	}
}
