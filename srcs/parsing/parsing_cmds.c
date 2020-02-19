/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:13:55 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/19 14:38:15 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_heredoc(t_minishell *minishell, t_token **token, t_cmd *cmd)
{
	char	*line;
	char	*tmp;
	int		pip[2];

	pipe(pip);
	cmd->in = pip[0];
	line = ft_strdup("");
	tmp = NULL;
	while (!tmp || !ft_strequ((*token)->next->word, tmp))
	{
		ft_strdel(&tmp);
		write(1, "> ", 2);
		if (get_next_line_no_eof(0, &tmp, 1))
		{
			if (!ft_strequ((*token)->next->word, tmp))
			{
				line = ft_strjoin_free(line, tmp);
				line = ft_strjoin_free(line, "\n");
			}
		}
	}
	ft_strdel(&tmp);
	if (ft_is_in_stri('$', line) && (*token)->next->word[0] != '\"')
		line = replace_env(minishell, line);
	ft_putstr_fd(line, pip[1]);
	close(pip[1]);
}

void	create_redirect(t_minishell *minishell, t_token **token, t_cmd *cmd)
{
	if (ft_strequ((*token)->word, "<<") && BONUS)
		ft_heredoc(minishell, token, cmd);
	*token = (*token)->next;
}

int		parse_tokens2(t_minishell *minishell, t_token **tmp, t_cmd *cmd)
{
	(void)minishell;
	if ((*tmp)->type == T_WORD && (cmd->cmd || ((*tmp)->prev
		&& (*tmp)->prev->type == T_REDIRECT)))
		add_token_list(&cmd->args, create_arg_token((*tmp)->word));
	if ((*tmp)->type == T_WORD && !cmd->cmd && (((*tmp)->prev && (*tmp)->prev->type != T_REDIRECT) || !(*tmp)->prev))
		cmd->cmd = (*tmp)->word;
	if ((*tmp)->type == T_REDIRECT)
		add_token_list(&cmd->args, create_arg_token((*tmp)->word));
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
