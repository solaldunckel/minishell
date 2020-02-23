/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:13:55 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/23 23:16:37 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_parse(t_minishell *minishell, char *str)
{
	char	*token;
	t_token *tmp;

	split_tokens(minishell, str);
	token = iter_tokens(minishell);
	if (token)
	{
		ft_dprintf(2, "%s: syntax error near unexpected token `%s'\n",
			minishell->name, token);
		return ;
	}
	tmp = minishell->token_list;
	while (tmp)
		parse_tokens(minishell, &tmp);
}

int		parse_tokens2(t_token **tmp, t_cmd *cmd)
{
	if ((*tmp)->type == T_WORD && (cmd->cmd || ((*tmp)->prev
		&& (*tmp)->prev->type == T_REDIRECT)))
		add_token_list(&cmd->args,
			create_arg_token((*tmp)->word, (*tmp)->type));
	if ((*tmp)->type == T_WORD && !cmd->cmd && (((*tmp)->prev
		&& (*tmp)->prev->type != T_REDIRECT) || !(*tmp)->prev))
		cmd->cmd = ft_strdup((*tmp)->word);
	if ((*tmp)->type == T_REDIRECT)
		add_token_list(&cmd->args,
			create_arg_token((*tmp)->word, (*tmp)->type));
	if ((*tmp)->type == T_ENV && !cmd->cmd)
		ft_lstadd_back(&cmd->env_list, ft_lstnew((*tmp)->word));
	if ((*tmp)->type == T_PIPE)
	{
		cmd->type = T_PIPE;
		*tmp = (*tmp)->next;
		return (0);
	}
	if ((*tmp)->type == T_SEP)
	{
		cmd->type = T_SEP;
		*tmp = (*tmp)->next;
		return (0);
	}
	return (1);
}

void	parse_tokens(t_minishell *minishell, t_token **tmp)
{
	t_cmd	*cmd;

	if ((*tmp)->type == T_NEWLINE)
	{
		*tmp = (*tmp)->next;
		return ;
	}
	if (!(cmd = ft_calloc(1, sizeof(t_cmd))))
		return ;
	while (*tmp)
	{
		if (!parse_tokens2(tmp, cmd))
			break ;
		if ((*tmp)->type == T_ENV && cmd->cmd)
			add_token_list(&cmd->args,
				create_arg_token((*tmp)->word, (*tmp)->type));
		*tmp = (*tmp)->next;
	}
	add_cmd_list(&minishell->cmd_list, cmd);
}
