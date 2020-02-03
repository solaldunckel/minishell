/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:03:58 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/03 10:19:01 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_bin(t_minishell *minishell)
{
	int		i;
	char	**bin;

	i = 0;
	bin = ft_split(get_env(minishell, "PATH"), ':');
	while (bin[i])
	{
		bin[i] = ft_strjoin_free(bin[i], "/");
		i++;
	}
	if (minishell->bin)
		ft_free_split(&minishell->bin);
	minishell->bin = bin;
}

char	*try_opendir(t_minishell *minishell, char *path, char *cmd)
{
	DIR				*dir;
	struct dirent	*dent;

	dir = opendir(path);
	if (dir)
	{
		while ((dent = readdir(dir)))
		{
			if (ft_strequ(dent->d_name, cmd))
				return (ft_strjoin(path, cmd));
		}
	}
	if (dir)
		closedir(dir);
	return (NULL);
}

char	*get_bin(t_minishell *minishell, char *cmd)
{
	char	*try;
	int		i;

	i = 0;
	if (ft_is_in_stri('/', cmd) >= 0)
		return (cmd);
	while (minishell->bin[i])
	{
		try = try_opendir(minishell, minishell->bin[i], cmd);
		if (try)
			return (try);
		i++;
	}
	return (NULL);
}
