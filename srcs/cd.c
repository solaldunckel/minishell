/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 10:51:46 by sdunckel          #+#    #+#             */
/*   Updated: 2020/01/17 04:08:45 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_cmd(t_minishell *minishell)
{
	int		count;

	count = count_split(minishell->split);
	if (count == 1)
	{
		if (chdir(get_env(minishell, "HOME")))
			ft_putstr(strerror(errno));
	}
	else
	{
		if (chdir(minishell->split[1]))
			ft_printf("%s: cd: %s: %s\n", minishell->name, minishell->split[1],
				strerror(errno));
	}
	ft_strdel(&minishell->curdir);
	minishell->curdir = getcwd(NULL, 0);
}
