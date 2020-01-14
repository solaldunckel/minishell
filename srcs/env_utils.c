/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 13:25:08 by sdunckel          #+#    #+#             */
/*   Updated: 2020/01/14 17:38:21 by sdunckel         ###   ########.fr       */
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

void	env_init(t_minishell *minishell, char **env)
{
	int		i;
	char	**tmp_split;

	i = 0;
	while (env[i])
	{
		tmp_split = ft_split(env[i], '=');
		ft_lstadd_back(&minishell->env_list, ft_lstnew(tmp_split));
		i++;
	}
}

char 	**env_array(t_minishell *minishell)
{
	int		i;
	t_list	*tmp;
	char 	**lenv;
	char 	**array;
	char 	*to_free;

	if (!(array = malloc(sizeof(char*) * 100)))
		return (NULL);
	i = 0;
	tmp = minishell->env_list;
	while (tmp)
	{
		lenv = tmp->content;
		array[i] = ft_strjoin(lenv[0], "=");
		to_free = array[i];
		array[i] = ft_strjoin(array[i], lenv[1]);
		free(to_free);
		i++;
		tmp = tmp->next;
	}
	array[i] = NULL;
	return (array);
}

char	*get_env(t_minishell *minishell, char *env)
{
	t_list	*tmp;
	char 	**lenv;

	tmp = minishell->env_list;
	while (tmp)
	{
		lenv = tmp->content;
		if (ft_strequ(env, lenv[0]))
			return (lenv[1]);
		tmp = tmp->next;
	}
	return (NULL);
}
