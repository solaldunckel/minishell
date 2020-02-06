/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 18:10:04 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/06 01:36:56 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		in_bracket(char *s, int pos)
{
	int		bracket1;
	int		bracket2;

	bracket1 = 0;
	bracket2 = 0;
	while (pos >= 0)
	{
		if (s[pos] == 34 && s[pos - 1] != 92)
			bracket1++;
		if (s[pos] == 39)
			bracket2++;
		pos--;
	}
	if (bracket1 % 2 != 0 || bracket2 % 2 != 0)
		return (1);
	return (0);
}

int		is_char_str(char c, char *str)
{
	if (ft_is_in_stri(c, str) >= 0)
		return (1);
	return (0);
}

void	token_env(char *str, int *i, t_minishell *minishell)
{
	while (str[*i])
	{
		minishell->count++;
		(*i)++;
		if (is_char_str(str[*i], "><$|;\"\' "))
		{
			add_token_list(&minishell->token_list, create_token(minishell, *i));
			return ;
		}
	}
}

t_token		*create_token_newline(void)
{
	t_token	*new;

	if (!(new = ft_calloc(1, sizeof(t_token))))
		return (NULL);
	new->word = ft_strdup("newline");
	return (new);
}

void	split_tokens(t_minishell *minishell, char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (is_char_str(str[i], "\'\"") && !in_bracket(str, i))
		{
			minishell->count++;
			add_token_list(&minishell->token_list, create_token(minishell, i + 1));
			i++;
			continue;
		}
		if (str[i] == ' ' && !in_bracket(str, i))
		{
			add_token_list(&minishell->token_list, create_token(minishell, i));
			i++;
			continue;
		}
		if ((is_char_str(str[i], "><|;") && !is_char_str(str[i - 1], "><"))
			&& !in_bracket(str, i))
			add_token_list(&minishell->token_list, create_token(minishell, i));
		if (is_char_str(str[i], "$") && !in_bracket(str, i))
		{
			token_env(str, &i, minishell);
			continue;
		}
		minishell->count++;
		if ((is_char_str(str[i], "><|;") && !is_char_str(str[i + 1], "><"))
			&& !in_bracket(str, i))
			add_token_list(&minishell->token_list, create_token(minishell, i + 1));
		if ((is_char_str(str[i], "><") && is_char_str(str[i - 1], "><"))
			&& !in_bracket(str, i))
			add_token_list(&minishell->token_list, create_token(minishell, i + 1));
		i++;
	}
	if (i > 0)
	{
		add_token_list(&minishell->token_list, create_token(minishell, i));
		add_token_list(&minishell->token_list, create_token_newline());
	}
}

int		check_error(t_token *token)
{
	if ((token->type == T_PIPE || token->type == T_SEP) && !token->prev)
		return (0);
	if (token->type == T_REDIRECT && (token->prev
		&& token->prev->type == T_REDIRECT))
		return (0);
	if (token->type == T_NEWLINE && token->prev && token->prev->type == T_REDIRECT)
		return (0);
	if (token->type == T_PIPE && token->prev && token->prev->type == T_PIPE)
		return (0);
	if (token->type == T_SEP && token->prev && token->prev->type == T_SEP)
		return (0);
	return (1);
}

char	*iter_tokens(t_minishell *minishell)
{
	t_token *tmp;

	tmp = minishell->token_list;
	while (tmp)
	{
		if (ft_strequ(tmp->word, ">") || ft_strequ(tmp->word, ">>")
			|| ft_strequ(tmp->word, "<<") || ft_strequ(tmp->word, "<"))
			tmp->type = T_REDIRECT;
		else if (ft_strequ(tmp->word, "|"))
			tmp->type = T_PIPE;
		else if (ft_strequ(tmp->word, ";"))
			tmp->type = T_SEP;
		else if (ft_strequ(tmp->word, "newline") && !tmp->next)
			tmp->type = T_NEWLINE;
		else
			tmp->type = T_WORD;
		if (!check_error(tmp))
			return (tmp->word);
		tmp = tmp->next;
	}
	return (NULL);
}

void	create_redirect(t_token **token, t_cmd *cmd)
{
	if (ft_strequ((*token)->word, ">"))
		cmd->out = open((*token)->next->word, O_TRUNC | O_RDWR | O_CREAT, 0644);
	else if (ft_strequ((*token)->word, ">>"))
		cmd->out = open((*token)->next->word, O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (ft_strequ((*token)->word, "<"))
		cmd->in = open((*token)->next->word, O_RDONLY);
	*token = (*token)->next;
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
			break;
		}
		if ((*tmp)->type == T_SEP)
		{
			cmd->type = T_SEP;
			*tmp = (*tmp)->next;
			break;
		}
		*tmp = (*tmp)->next;
	}
	add_cmd_list(&minishell->cmd_list, cmd);
}

void	start_parse(t_minishell *minishell, char *str)
{
	char 	*token;
	t_token *tmp;
	t_cmd	*tmp2;

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
