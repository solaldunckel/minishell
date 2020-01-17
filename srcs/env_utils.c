/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 13:25:08 by sdunckel          #+#    #+#             */
/*   Updated: 2020/01/17 04:46:38 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_env(t_minishell *minishell, char **split)
{
	int		i;
	char 	*env;
	char	*new;
	char 	*to_free;
	char 	*tmp;

	env = ft_strtrim(*split, "$");
	tmp = get_env(minishell, env);
	if (tmp)
		new = ft_strdup(tmp);
	else
		new = ft_strdup("");
	to_free = *split;
	*split = new;
	free(to_free);
	free(env);
}

t_env	*create_env(t_minishell *minishell, char **split)
{
	t_env	*env;

	if (!(env = ft_calloc(1, sizeof(t_env))))
		return (NULL);
	env->name = ft_strdup(split[0]);
	if (split[1])
		env->value = ft_strdup(split[1]);
	else
		env->value = ft_strdup("");
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
		if (!(tmp = create_env(minishell, tmp_split)))
			return ;
		ft_lstadd_back(&minishell->env_list, ft_lstnew(tmp));
		free_split(tmp_split);
		i++;
	}
	minishell->env_array = env_to_array(minishell);
	if (get_env(minishell, "PATH"))
		parse_bin(minishell);
}

char 	**env_to_array(t_minishell *minishell)
{
	int		i;
	t_list	*tmp;
	char 	**array;

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
		free_split(minishell->env_array);
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
