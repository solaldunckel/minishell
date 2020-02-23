/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 20:41:27 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/23 23:34:15 by sdunckel         ###   ########.fr       */
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

void	export_no_args(t_minishell *minishell)
{
	t_list	*tmp;

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

int		modify_env_list(t_minishell *minishell, char **split, int ex)
{
	t_list	*tmp;

	tmp = minishell->env_list;
	while (tmp)
	{
		if (ft_strequ(((t_env*)(tmp->content))->name, split[0]))
		{
			if (ex)
			{
				if (((t_env*)(tmp->content))->tmp)
					((t_env*)(tmp->content))->tmp = 0;
				return (1);
			}
			((t_env*)(tmp->content))->tmp = 0;
			free(((t_env*)(tmp->content))->value);
			if (split[1])
				((t_env*)(tmp->content))->value = ft_strndup(split[1], 4096);
			else
				((t_env*)(tmp->content))->value = ft_strdup("");
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	export_cmd2(t_minishell *minishell, t_token *args, char **split)
{
	int		ex;
	int		i;

	i = -1;
	ex = 0;
	ft_is_in_stri('=', args->word) == -1 ? ex = 1 : 0;
	if (!(modify_env_list(minishell, split, ex)))
		ft_lstadd_back(&minishell->env_list,
			ft_lstnew(create_env(split, ex)));
	if (ft_strequ(split[0], "PATH"))
		parse_bin(minishell);
	minishell->env_array = env_to_array(minishell);
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
	while (args)
	{
		split = ft_split_n(args->word, '=', 1);
		if (ft_strlen(args->word) > 0 && env_valid_character(split[0]))
			export_cmd2(minishell, args, split);
		else
			ft_dprintf(2, "%s: %s: `%s': %s\n", minishell->name, cmd->cmd,
				args->word, "not a valid identifier");
		ft_free_split(&split);
		args = args->next;
	}
	minishell->exit = 0;
}
