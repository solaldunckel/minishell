/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmds_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:13:55 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/28 20:38:53 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		iter_tokens2(t_token *tmp)
{
	if (ft_strequ(tmp->word, "|"))
		tmp->type = T_PIPE;
	else if (ft_strequ(tmp->word, ";"))
		tmp->type = T_SEP;
	else if (ft_strequ(tmp->word, "newline") && !tmp->next)
		tmp->type = T_NEWLINE;
	else if (is_valid_env(tmp->word))
		tmp->type = T_ENV;
	else if (ft_strequ(tmp->word, "&&"))
		tmp->type = T_AND;
	else if (ft_strequ(tmp->word, "||"))
		tmp->type = T_OR;
	else if (ft_strequ(tmp->word, "("))
		tmp->type = T_PAR_OPEN;
	else if (ft_strequ(tmp->word, ")"))
		tmp->type = T_PAR_CLOSE;
	else
		return (0);
	return (1);
}

void	start_parse(t_minishell *minishell, char *str)
{
	char	*token;
	t_token *tmp;

	minishell->scope_p = 0;
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
		ft_lstadd_back(&cmd->env_list, ft_lstnew(ft_strdup((*tmp)->word)));
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

int		parse_tokens3(t_token **tmp, t_cmd *cmd, int *dec)
{
	if ((*tmp)->type == T_PAR_OPEN)
		g_minishell->scope_p++;
	if ((*tmp)->type == T_PAR_CLOSE)
		*dec = 1;
	if ((*tmp)->type == T_AND)
	{
		cmd->type = T_AND;
		*tmp = (*tmp)->next;
		return (0);
	}
	if ((*tmp)->type == T_OR)
	{
		cmd->type = T_OR;
		*tmp = (*tmp)->next;
		return (0);
	}
	if ((*tmp)->type == T_ENV && cmd->cmd)
		add_token_list(&cmd->args,
			create_arg_token((*tmp)->word, (*tmp)->type));
	return (1);
}

void	parse_tokens(t_minishell *minishell, t_token **tmp)
{
	t_cmd	*cmd;
	int		dec;

	dec = 0;
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
		if (!parse_tokens3(tmp, cmd, &dec))
			break ;
		*tmp = (*tmp)->next;
	}
	cmd->scope = minishell->scope_p;
	add_cmd_list(&minishell->cmd_list, cmd);
	if (dec && (dec = 0) == 0)
		minishell->scope_p--;
}
