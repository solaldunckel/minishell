/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_process2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 04:18:02 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/22 04:18:28 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token_front(t_token **begin, t_token *new)
{
	if (*begin)
	{
		new->next = *begin;
		(*begin)->prev = new;
		*begin = new;
	}
	else
		*begin = new;

}

void	add_more_args(t_cmd *cmd, char **split)
{
	int		i;
	char	*tmp;

	i = ft_count_split(split) - 1;
	tmp = cmd->cmd;
	cmd->cmd = ft_strdup(split[0]);
	free(tmp);
	while (i > 0)
	{
		add_token_front(&cmd->args, create_arg_token(ft_strdup(split[i]),
			T_WORD));
		i--;
	}
}

void	process_args(t_minishell *minishell, t_cmd *cmd)
{
	t_token	*tmp;
	char	**split;

	(void)minishell;
	tmp = cmd->args;
	while (tmp)
	{
		tmp->word = handle_quotes(tmp->word);
		tmp = tmp->next;
	}
	if (cmd->cmd)
		cmd->cmd = handle_quotes(cmd->cmd);
	split = ft_split(cmd->cmd, ' ');
	if (ft_count_split(split) > 1)
		add_more_args(cmd, split);
	ft_free_split(&split);
}
