/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 19:38:50 by sdunckel          #+#    #+#             */
/*   Updated: 2020/03/11 18:38:30 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	edit_pwd(t_minishell *minishell)
{
	char	*backup;

	backup = ft_strdup(minishell->curdir);
	ft_strdel(&minishell->curdir);
	if (get_env(minishell, "PWD") && get_env(minishell, "OLDPWD"))
		set_env(minishell, "OLDPWD", get_env(minishell, "PWD"));
	minishell->curdir = getcwd(NULL, 0);
	if (!minishell->curdir)
	{
		ft_dprintf(2, "cd: error retrieving current directory: getcwd: "
			"cannot access parent directories: No such file or directory\n");
		minishell->curdir = ft_strjoin_free(backup, "/.");
		return ;
	}
	if (get_env(minishell, "PWD"))
		set_env(minishell, "PWD", minishell->curdir);
	free(backup);
}

void	cd_cmd(t_minishell *minishell, t_cmd *cmd)
{
	t_token		*args;

	args = cmd->args;
	if (!args)
	{
		if (chdir(get_env(minishell, "HOME")))
		{
			ft_dprintf(2, "%s: cd: HOME not set\n", minishell->name);
			minishell->exit = 1;
			return ;
		}
	}
	else
	{
		if (chdir(args->word))
		{
			ft_dprintf(2, "%s: cd: %s: %s\n", minishell->name, args->word,
				strerror(errno));
			minishell->exit = 1;
			return ;
		}
	}
	minishell->exit = 0;
	edit_pwd(minishell);
}
