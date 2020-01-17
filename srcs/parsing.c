/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 09:33:49 by sdunckel          #+#    #+#             */
/*   Updated: 2020/01/17 11:03:52 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int		cmd_len(t_minishell *minishell)
// {
// 	int		i;
// 	int		simple_bracket;
// 	int		double_bracket;
//
// 	i = 0;
// 	simple_bracket = 0;
// 	double_bracket = 0;
// 	while (minishell->line[i])
// 	{
// 		if (minishell->line[i] == 34)
// 			simple_bracket++;
// 		if (minishell->line[i] == 34)
// 			double_bracket++;
// 		if (minishell->line[i] == ';' || minishell->line[i] == '|'
// 			|| minishell->line[i] == '<' || minishell->line[i] == '>'
// 			&& simple_bracket % 2 == 0 && double_bracket % 2 == 0)
// 			return (i);
// 		i++;
// 	}
// 	return (i);
// }
//
// void	parse_cmds(t_minishell *minishell)
// {
// 	char **cmds;
//
// 	cmds = ft_split_bracket(minishell->line, ";");
//
// }

// echo on test "tout;  ";
