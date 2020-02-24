/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haguerni <haguerni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 18:49:44 by haguerni          #+#    #+#             */
/*   Updated: 2020/02/22 01:55:29 by sdunckel         ###   ########.fr       */
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
