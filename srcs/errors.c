/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 19:25:33 by sdunckel          #+#    #+#             */
/*   Updated: 2020/01/27 22:00:03 by haguerni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_errno(t_minishell *minishell, char *cmd, int type)
{
	//printf("%d\n", errno);
	if (type == 14)
		ft_printf("%s: %s: %s\n", minishell->name, cmd, "command not found");
	else
		ft_printf("%s: %s: %s\n", minishell->name, cmd, strerror(errno));
}

void	handle_errors(t_minishell *minishell, char *cmd, int type)
{
	if (type == 1)
		ft_printf("%s: %s: %s\n", minishell->name, cmd, strerror(errno));
	else if (type == 2)
		ft_printf("%s: %s: %s\n", minishell->name, cmd,
			"no such file or directory");
	else if (type == 3)
		ft_printf("%s: %s: %s\n", minishell->name, cmd, "command not found");
	exit(0);
}
