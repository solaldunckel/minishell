/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_process2_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 00:21:50 by sdunckel          #+#    #+#             */
/*   Updated: 2020/03/02 17:41:53 by haguerni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		add_more_args(t_cmd *cmd, char **split)
{
	int		i;
	char	*tmp;

	i = ft_count_split(split) - 1;
	tmp = cmd->cmd;
	cmd->cmd = ft_strdup(split[0]);
	free(tmp);
	while (i > 0)
	{
		add_token_front(&cmd->args, create_arg_token(split[i], T_WORD));
		i--;
	}
}

t_token		*add_more_args2(t_cmd *cmd, t_token **token, char **split)
{
	t_token *new;
	t_token *end_new;
	t_token *next;

	new = token_split_to_list(split);
	end_new = new;
	while (end_new->next)
		end_new = end_new->next;
	next = (*token)->next;
	end_new->next = next;
	if ((*token)->next)
		(*token)->next->prev = end_new;
	if ((*token)->prev)
		(*token)->prev->next = new;
	else
	{
		cmd->args = new;
		free((*token)->word);
		free(*token);
		return (end_new);
	}
	free((*token)->word);
	free(*token);
	ft_free_split(&split);
	return (end_new);
}

void		process_args2(t_cmd *cmd)
{
	int		env;
	char	**split;
	char	*tmp;

	env = 0;
	if (cmd->cmd && cmd->cmd[0] == '$')
		env = 1;
	if (cmd->cmd)
	{
		tmp = cmd->cmd;
		cmd->cmd = handle_quotes(cmd->cmd);
		ft_strdel(&tmp);
	}
	if (env)
	{
		split = ft_ssplit(cmd->cmd, " \n");
		if (ft_count_split(split) > 1)
			add_more_args(cmd, split);
		ft_free_split(&split);
	}
}

void		process_args_env(t_cmd *cmd)
{
	t_list	*tmp;
	char	*tmp2;

	tmp = cmd->env_list;
	while (tmp)
	{
		tmp2 = tmp->content;
		tmp->content = handle_quotes(tmp->content);
		ft_strdel(&tmp2);
		tmp = tmp->next;
	}
}

void		process_args(t_cmd *cmd)
{
	t_token	*tmp;
	char	**split;
	int		env;
	char	*tmp2;

	tmp = cmd->args;
	while (tmp && (env = 0) == 0)
	{
		if (ft_is_in_stri('*', tmp->word) > -1)
			process_wildcard(tmp, create_wildpath(tmp->word), 0,
				ft_split(tmp->word, '/'));
		tmp->type == 11 ? remove_redirect(tmp, &cmd->args) : 0;
		if (tmp->word && tmp->word[0] == '$')
			env = 1;
		tmp2 = tmp->word;
		tmp->word = handle_quotes(tmp->word);
		ft_strdel(&tmp2);
		if (env && (split = ft_ssplit(tmp->word, " \n")) != NULL)
			if (ft_count_split(split) > 1)
				tmp = add_more_args2(cmd, &tmp, split);
		tmp = tmp->next;
	}
	process_args2(cmd);
}
