/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 13:25:08 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/16 15:59:27 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env(t_minishell *minishell, char *env, char *value)
{
	t_list	*tmp;
	char	*to_free;
	t_env	*tmp2;

	tmp = minishell->env_list;
	while (tmp)
	{
		tmp2 = tmp->content;
		if (ft_strequ(env, tmp2->name))
		{
			to_free = tmp2->value;
			tmp2->value = ft_strdup(value);
			free(to_free);
			return ;
		}
		tmp = tmp->next;
	}
}

t_env	*create_env(char **split, int ex)
{
	t_env	*env;

	if (!(env = ft_calloc(1, sizeof(t_env))))
		return (NULL);
	env->name = ft_strdup(split[0]);
	if (split[1])
		env->value = ft_strdup(split[1]);
	else if (ex)
		env->value = NULL;
	else
		env->value = ft_strdup("");
	env->ex = ex;
	return (env);
}

void	env_init(t_minishell *minishell, char **env)
{
	int		i;
	char	**tmp_split;
	t_env	*tmp;

	i = 0;
	while (env[i])
	{
		tmp_split = ft_split(env[i], '=');
		if (!(tmp = create_env(tmp_split, 0)))
			return ;
		ft_lstadd_back(&minishell->env_list, ft_lstnew(tmp));
		ft_free_split(&tmp_split);
		i++;
	}
	minishell->env_array = env_to_array(minishell);
	if (get_env(minishell, "PATH"))
		parse_bin(minishell);
}

char	**env_to_array(t_minishell *minishell)
{
	int		i;
	t_list	*tmp;
	char	**array;

	if (!(array = malloc(sizeof(char*) * ft_lstsize(minishell->env_list) + 1)))
		return (NULL);
	i = 0;
	tmp = minishell->env_list;
	while (tmp)
	{
		array[i] = ft_strjoin(((t_env*)(tmp->content))->name, "=");
		array[i] = ft_strjoin_free(array[i], ((t_env*)(tmp->content))->value);
		i++;
		tmp = tmp->next;
	}
	array[i] = NULL;
	if (minishell->env_array)
		ft_free_split(&minishell->env_array);
	return (array);
}

char	*get_env(t_minishell *minishell, char *env)
{
	t_list	*tmp;

	tmp = minishell->env_list;
	while (tmp)
	{
		if (ft_strequ(env, ((t_env*)(tmp->content))->name))
			return (((t_env*)(tmp->content))->value);
		tmp = tmp->next;
	}
	if (ft_strequ(env, "?"))
		return (ft_itoa(minishell->exit));
	return (NULL);
}
