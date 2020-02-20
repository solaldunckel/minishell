/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haguerni <haguerni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 18:49:44 by haguerni          #+#    #+#             */
/*   Updated: 2020/02/20 18:59:35 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_errno(t_minishell *minishell, char *cmd, int type)
{
	if (type == 14)
		ft_dprintf(2, "%s: %s: %s\n", minishell->name, cmd,
			"command not found");
	else
		ft_dprintf(2, "%s: %s: %s\n", minishell->name, cmd, strerror(errno));
	minishell->exit = 127;
}

void	handle_errors(t_minishell *minishell, char *cmd, int type)
{
	if (type == 1)
		ft_dprintf(2, "%s: %s: %s\n", minishell->name, cmd, strerror(errno));
	else if (type == 2)
		ft_dprintf(2, "%s: %s: %s\n", minishell->name, cmd,
			"no such file or directory");
	else if (type == 3)
		ft_dprintf(2, "%s: %s: %s\n", minishell->name, cmd,
			"command not found");
	else if (type == 4)
		ft_dprintf(2, "%s: %s: %s\n", minishell->name, cmd,
			"too many arguments");
	exit_cmd(minishell);
}
