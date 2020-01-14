/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 10:51:46 by sdunckel          #+#    #+#             */
/*   Updated: 2020/01/14 13:51:00 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_cmd(t_minishell *minishell)
{
	char	*to_free;
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
	to_free = minishell->curdir;
	minishell->curdir = getcwd(NULL, 0);
	free(to_free);
}
