/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 19:47:25 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/22 04:15:09 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_heredoc(t_token **token, t_cmd *cmd, char *tmp)
{
	char	*line;
	int		pip[2];

	pipe(pip);
	cmd->in = pip[0];
	line = ft_strdup("");
	while ((!tmp || !ft_strequ((*token)->next->word, tmp)) &&
		g_minishell->quit == 0)
	{
		ft_strdel(&tmp);
		write(1, "> ", 2);
		if (get_next_line_no_eof(0, &tmp, 2) &&
			!ft_strequ((*token)->next->word, tmp))
		{
			line = ft_strjoin_free(line, tmp);
			g_minishell->quit != 3 ? line = ft_strjoin_free(line, "\n") : 0;
		}
	}
	ft_strdel(&tmp);
	if (ft_is_in_stri('$', line) > -1 && (*token)->next->word[0] != '\"')
		line = replace_env(line, 0);
	g_minishell->quit != 2 ? ft_putstr_fd(line, pip[1]) : 0;
	ft_strdel(&line);
	close(pip[1]);
}

t_token	*remove_redirect(t_token *args, t_token **begin)
{
	t_token	*tmp;
	t_token	*next;

	tmp = *begin;
	if (*begin == args)
	{
		next = (*begin)->next;
		free_redirect(*begin);
		*begin = next;
		next ? next->prev = NULL : 0;
		return (next);
	}
	while (tmp)
	{
		if (tmp == args && tmp->prev)
		{
			next = tmp->next;
			tmp->prev->next = next;
			tmp->next ? tmp->next->prev = tmp->prev : 0;
			free_redirect(args);
			return (next);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int		create_redirect2(t_minishell *minishell, t_cmd *cmd, t_token **args,
			int flags)
{
	int		fd;

	if ((fd = open((*args)->next->word, flags, 0644)) < 0)
	{
		ft_dprintf(2, "%s: %s: %s\n", g_minishell->name,
			(*args)->next->word, strerror(errno));
		minishell->exit = 1;
	}
	*args = remove_redirect(*args, &cmd->args);
	*args = remove_redirect(*args, &cmd->args);
	return (fd);
}

void	create_redirect(t_minishell *minishell, t_cmd *cmd)
{
	t_token	*args;

	args = cmd->args;
	while (args && args->next)
	{
		if (ft_strequ(args->word, ">") && args->type == T_REDIRECT)
			cmd->out = create_redirect2(minishell, cmd, &args,
				O_TRUNC | O_RDWR | O_CREAT);
		else if (ft_strequ(args->word, ">>") && args->type == T_REDIRECT)
			cmd->out = create_redirect2(minishell, cmd, &args,
				O_RDWR | O_CREAT | O_APPEND);
		else if (ft_strequ(args->word, "<") && args->type == T_REDIRECT)
			cmd->in = create_redirect2(minishell, cmd, &args, O_RDONLY);
		else if (ft_strequ(args->word, "<<") && args->type == T_REDIRECT
			&& BONUS)
		{
			ft_heredoc(&args, cmd, NULL);
			args = remove_redirect(args, &cmd->args);
			args = remove_redirect(args, &cmd->args);
		}
		else
			args = args->next;
	}
}
