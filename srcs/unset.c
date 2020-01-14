/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:17:35 by sdunckel          #+#    #+#             */
/*   Updated: 2020/01/14 17:05:03 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_env(t_list **begin_list, char *env)
{
	t_list	*current;
	t_list	*next;
	char 	**lenv;

	if (!*begin_list)
		return ;
	while (*begin_list)
	{
		lenv = (*begin_list)->content;
		if (ft_strequ(lenv[0], env))
		{
			next = (*begin_list)->next;
			free_split(lenv);
			free(*begin_list);
			*begin_list = next;
		}
		else
			break;
	}
	if (!*begin_list)
		return ;
	current = *begin_list;
	while (current && current->next)
	{
		lenv = current->next->content;
		if (ft_strequ(lenv[0], env))
		{
			next = current->next->next;
			free_split(lenv);
			free(current->next);
			current->next = next;
		}
		else
			current = current->next;
	}
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
			remove_env(&minishell->env_list, minishell->split[i]);
		i++;
	}
}
