/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 13:25:08 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/03 19:34:56 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_env_2(t_minishell *minishell, char *str, char **final)
{
	char	*tmp;
	char	**split;
	int		j;

	j = 0;
	split = ft_split(str, '$');
	while (split[j])
	{
		tmp = get_env(minishell, split[j]);
		if (tmp)
			*final = ft_strjoin_free(*final, tmp);
		else
			*final = ft_strjoin_free(*final, "");
		j++;
	}
	ft_free_split(&split);
}

char	*replace_env(t_minishell *minishell, char *line)
{
	int		i;
	char	*tmp;
	char	*final;
	char	**split;

	i = 0;
	final = ft_strdup("");
	split = ft_ssplit(line, " ");
	while (split[i])
	{
		if (ft_is_in_stri('$', split[i]) >= 0)
			replace_env_2(minishell, split[i], &final);
		else
			final = ft_strjoin_free(final, split[i]);
		i++;
	}
	ft_free_split(&split);
	return (final);
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
