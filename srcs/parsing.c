/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 09:33:49 by sdunckel          #+#    #+#             */
/*   Updated: 2020/01/19 17:36:56 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_pipe(t_minishell *minishell)
{
	int		i;
	char 	**cmds;
	t_cmd	*cmd;

	i = 0;
	cmds = ft_split_brackets(minishell->line, "|");
	while (cmds[i])
	{
		if (!(cmd = malloc(sizeof(t_cmd))))
			return ;
		cmd->line = ft_strdup(cmds[i]);
		ft_lstadd_back(&minishell->cmd_list2, ft_lstnew(cmd));
		i++;
	}
	free_split(cmds);
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
		if (!(cmd = malloc(sizeof(t_cmd))))
			return ;
		cmd->line = ft_strdup(cmds[i]);
		ft_lstadd_back(&minishell->cmd_list, ft_lstnew(cmd));
		i++;
	}
	free_split(cmds);
}

// echo on test "tout;  "; ls -la | grep Makefile
