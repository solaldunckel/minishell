/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:13:55 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/06 15:28:40 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_redirect(t_token **token, t_cmd *cmd)
{
	if (ft_strequ((*token)->word, ">"))
		cmd->out = open((*token)->next->word, O_TRUNC | O_RDWR | O_CREAT, 0644);
	else if (ft_strequ((*token)->word, ">>"))
		cmd->out = open((*token)->next->word, O_RDWR | O_CREAT | O_APPEND,
			0644);
	else if (ft_strequ((*token)->word, "<"))
		cmd->in = open((*token)->next->word, O_RDONLY);
	*token = (*token)->next;
}

int		parse_tokens2(t_minishell *minishell, t_token **tmp, t_cmd *cmd)
{
	if ((*tmp)->type == T_WORD && cmd->cmd)
		add_token_list(&cmd->args, create_arg_token((*tmp)->word));
	if ((*tmp)->type == T_WORD && !cmd->cmd)
		cmd->cmd = (*tmp)->word;
	if ((*tmp)->type == T_REDIRECT)
		create_redirect(tmp, cmd);
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
		if (!parse_tokens2(minishell, tmp, cmd))
			break ;
		*tmp = (*tmp)->next;
	}
	add_cmd_list(&minishell->cmd_list, cmd);
}
