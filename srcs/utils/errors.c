/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsize <tomsize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 01:16:33 by tomsize           #+#    #+#             */
/*   Updated: 2020/02/10 01:16:45 by tomsize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_errno(t_minishell *minishell, char *cmd, int type)
{
	if (type == 14)
		ft_dprintf(2, "%s: %s: %s\n", minishell->name, cmd, "command not found");
	else
		ft_dprintf(2, "%s: %s: %s\n", minishell->name, cmd, strerror(errno));
}
