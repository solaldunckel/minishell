/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 20:41:27 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/12 16:39:10 by haguerni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sort_list(t_list **begin_list, int (*cmp)())
{
	t_list	*ptr;
	t_list	*ptr2;
	t_list	*next;

	ptr = *begin_list;
	while (ptr)
	{
		ptr2 = *begin_list;
		while (ptr2->next)
		{
			if ((*cmp)(((t_env*)(ptr2->content))->name,
				((t_env*)(ptr2->next->content))->name) > 0)
			{
				next = ptr2->content;
				ptr2->content = ptr2->next->content;
				ptr2->next->content = next;
			}
			ptr2 = ptr2->next;
		}
		ptr = ptr->next;
	}
}

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
			ft_printf("declare -x %s=\"%s\"\n", ((t_env*)(tmp->content))->name,
				((t_env*)(tmp->content))->value);
		tmp = tmp->next;
	}
}

void	export_no_args(t_minishell *minishell)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = minishell->env_list;
	while (tmp)
	{
		ft_lstadd_back(&minishell->sort_env_list, ft_lstnew(tmp->content));
		tmp = tmp->next;
	}
	ft_sort_list(&minishell->sort_env_list, ft_strcmp);
	env_cmd_export(&minishell->sort_env_list);
	ft_lstclear(&minishell->sort_env_list, nothing);
}

int		modify_env_list(t_minishell *minishell, char **split)
{
	t_list	*tmp;

	tmp = minishell->env_list;
	while (tmp)
	{
		if (ft_strequ(((t_env*)(tmp->content))->name, split[0]))
		{
			free(((t_env*)(tmp->content))->value);
			if (split[1])
				((t_env*)(tmp->content))->value = ft_strdup(split[1]);
			else
				((t_env*)(tmp->content))->value = ft_strdup("");
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	export_cmd(t_minishell *minishell, t_cmd *cmd, int forked)
{
	t_token *args;
	char	**split;

	args = cmd->args;
	if (!args && forked)
	{
		export_no_args(minishell);
		return ;
	}
	while (args && !forked)
	{
		if (ft_is_in_stri('=', args->word) >= 0)
		{
			split = ft_split(args->word, '=');
			if (!(modify_env_list(minishell, split)))
				ft_lstadd_back(&minishell->env_list,
					ft_lstnew(create_env(split)));
			if (ft_strequ(split[0], "PATH"))
				parse_bin(minishell);
			minishell->env_array = env_to_array(minishell);
			ft_free_split(&split);
		}
		args = args->next;
	}
	minishell->exit = 0;
}
