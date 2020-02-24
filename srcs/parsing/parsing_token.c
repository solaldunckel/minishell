/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:13:33 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/24 14:56:20 by haguerni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		split_tokens2(t_minishell *minishell, char *str, int *i)
{
	if ((str[*i] == ' ' || str[*i] == '\t') && !in_bracket(str, *i)
		&& !is_escaped(str, *i - 1))
	{
		add_token_list(&minishell->token_list, create_token(minishell, *i));
		(*i)++;
		return (0);
	}
	if ((is_char_str(str[*i], "><|;") && !is_char_str(str[*i - 1], "><"))
		&& !in_bracket(str, *i) && !is_escaped(str, *i - 1))
		add_token_list(&minishell->token_list, create_token(minishell, *i));
	return (1);
}

void	split_tokens(t_minishell *minishell, char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!split_tokens2(minishell, str, &i))
			continue ;
		minishell->count++;
		if ((is_char_str(str[i], "><|;") && !is_char_str(str[i + 1], "><"))
			&& !in_bracket(str, i) && !is_escaped(str, i - 1))
			add_token_list(&minishell->token_list,
				create_token(minishell, i + 1));
		if ((is_char_str(str[i], "><") && is_char_str(str[i - 1], "><"))
			&& !in_bracket(str, i) && !is_escaped(str, i - 1))
			add_token_list(&minishell->token_list,
				create_token(minishell, i + 1));
		i++;
	}
	if (i > 0)
	{
		add_token_list(&minishell->token_list, create_token(minishell, i));
		add_token_list(&minishell->token_list,
			create_arg_token("newline", T_NEWLINE));
	}
}

int		check_error(t_token *token)
{
	if ((token->type == T_PIPE || token->type == T_SEP) && !token->prev)
		return (0);
	if (token->type == T_REDIRECT && (token->prev
		&& token->prev->type == T_REDIRECT))
		return (0);
	if (token->type == T_NEWLINE && token->prev
		&& (token->prev->type == T_REDIRECT || token->prev->type == T_PIPE))
		return (0);
	if (token->type == T_PIPE && (token->prev->type == T_PIPE
		|| token->prev->type == T_SEP || token->prev->type == T_REDIRECT))
		return (0);
	if (token->type == T_SEP && (token->prev->type == T_SEP
		|| token->prev->type == T_PIPE || token->prev->type == T_REDIRECT))
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
		else if (is_valid_env(tmp->word))
			tmp->type = T_ENV;
		else
			tmp->type = T_WORD;
		if (!check_error(tmp))
			return (tmp->word);
		tmp = tmp->next;
	}
	return (NULL);
}
