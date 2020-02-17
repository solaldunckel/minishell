/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:13:55 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/17 18:00:21 by sdunckel         ###   ########.fr       */
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
	if (ft_strequ((*token)->word, ">"))
	{
		if ((cmd->out = open((*token)->next->word, O_TRUNC | O_RDWR | O_CREAT,
			0644)) < 0)
			ft_dprintf(2, "%s: %s: %s\n", g_minishell->name,
				(*token)->next->word, strerror(errno));
	}
	else if (ft_strequ((*token)->word, ">>"))
	{
		if ((cmd->out = open((*token)->next->word, O_RDWR | O_CREAT | O_APPEND,
			0644)) < 0)
			ft_dprintf(2, "%s: %s: %s\n", g_minishell->name,
				(*token)->next->word, strerror(errno));
	}
	else if (ft_strequ((*token)->word, "<"))
	{
		if ((cmd->in = open((*token)->next->word, O_RDONLY)) < 0)
			ft_dprintf(2, "%s: %s: %s\n", g_minishell->name,
				(*token)->next->word, strerror(errno));
	}
	else if (ft_strequ((*token)->word, "<<"))
		ft_heredoc(minishell, token, cmd);
	*token = (*token)->next;
}

int		parse_tokens2(t_minishell *minishell, t_token **tmp, t_cmd *cmd)
{
	if ((*tmp)->type == T_WORD && cmd->cmd)
		add_token_list(&cmd->args, create_arg_token((*tmp)->word));
	if ((*tmp)->type == T_WORD && !cmd->cmd)
		cmd->cmd = (*tmp)->word;
	if ((*tmp)->type == T_REDIRECT)
		create_redirect(minishell, tmp, cmd);
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
