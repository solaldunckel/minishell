/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 19:38:50 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/11 14:44:28 by haguerni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_cmd(t_minishell *minishell, t_cmd *cmd)
{
	t_token		*args;

	args = cmd->args;
	if (!args)
	{
		if (chdir(get_env(minishell, "HOME")))
			ft_putstr(strerror(errno));
	}
	else
	{
		if (chdir(args->word))
			ft_printf("%s: cd: %s: %s\n", minishell->name, args->word,
				strerror(errno));
	}
	ft_strdel(&minishell->curdir);
	minishell->curdir = getcwd(NULL, 0);
}
