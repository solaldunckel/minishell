/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 09:33:49 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/01 18:05:43 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_pipe(t_minishell *minishell, char *str)
{
	int		i;
	char 	**cmds;
	t_cmd	*cmd;

	i = 0;
	cmds = ft_split_brackets(str, "|");
	while (cmds[i])
	{
		if (!(cmd = malloc(sizeof(t_cmd))))
			return ;
		cmd->line = ft_strdup(cmds[i]);
		if (i == 0)
			cmd->type = NORMAL;
		else
			cmd->type = PIPE;
		ft_lstadd_back(&minishell->cmd_list, ft_lstnew(cmd));
		i++;
	}
	free_split(cmds);
}

void	parse_redirect(t_minishell *minishell, char **split)
{
	int		i;

	i = 0;
	while (split[i])
	{
		if (ft_is_in_stri('>', split[i]) >= 0
			|| ft_is_in_stri('<', split[i]) >= 0)
		{

		}
		i++;
	}
}
// echo test> allo > allo test | echo " test > allo" > test; ls -la
void	parse_space(t_minishell *minishell)
{
	t_list	*tmp;
	t_cmd	*cmd;

	tmp = minishell->cmd_list;
	while (tmp)
	{
		cmd = tmp->content;
		cmd->split = ft_split_brackets(cmd->line, " ");
		parse_redirect(minishell, cmd->split);
		tmp = tmp->next;
	}
}

void	parse_cmds(t_minishell *minishell)
{
	int		i;
	char 	**cmds;
	t_cmd	*cmd;

	i = 0;
	cmds = ft_split_brackets(minishell->line, ";");
	while (cmds[i])
	{
		parse_pipe(minishell, cmds[i]);
		i++;
	}
	free_split(cmds);
	//parse_space(minishell);
	//parse_redirect(minishell);
}

// echo on test "tout;  "; ls -la | grep Makefile
