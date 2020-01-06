/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 10:51:46 by sdunckel          #+#    #+#             */
/*   Updated: 2019/12/31 02:19:10 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_cmd(t_minishell *minishell)
{
	char	*to_free;

	if (minishell->split[1] && chdir(minishell->split[1]))
		ft_putstr(strerror(errno));
	else if (!minishell->split[1])
	{
		if (chdir(get_env(minishell, "HOME")))
			ft_putstr(strerror(errno));
	}
	to_free = minishell->curdir;
	minishell->curdir = getcwd(NULL, 0);
	free(to_free);
}
