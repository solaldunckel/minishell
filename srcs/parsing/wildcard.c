/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haguerni <haguerni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:53:37 by haguerni          #+#    #+#             */
/*   Updated: 2020/02/24 21:38:43 by haguerni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_strmatch(char *s1, char *s2, int i, int j)
{
	int k;

	if(!s1[i] && !s2[j])
		return (1);
	if(!s2[j])
		return (0);
	if (s1[i] == s2[j])
		return (ft_strmatch(s1, s2, i + 1, j + 1));
	k = j;
	if (s1[i] == '*')
		while(s2[k])
			if (ft_strmatch(s1, s2, i + 1, k++))
				return (1);
	if (s1[i] == '*' && s1[i + 1] == s2[j + 1])
		return (ft_strmatch(s1, s2, i + 1, j + 1));
	if (s1[i] == '*')
		return (ft_strmatch(s1, s2, i, j + 1));
	return (0);
}

void	add_processed_list(t_token *arg, DIR *dir, char *path, char **splat)
{
	struct dirent	*dent;
	char			*tmp;
	char			**splot;
	int				i;

	(void)arg;
	while ((dent = readdir(dir)))
	{
		tmp = ft_strjoin("/", dent->d_name);
		tmp = ft_strjoin(path, tmp);
		splot = ft_split(tmp, '/');
		i = 1;
		while (ft_strmatch(splat[i - 1], splot[i], 0, 0))
		{
			i++;
			if (!splot[i])
			{
				printf("%s\n", tmp);
				//add_next_arg(arg, tmp);
				break ;
			}
		}
		free(tmp);
		ft_free_split(&splot);
	}
	ft_free_split(&splat);
}

void	process_wildcard(t_token *arg, char *path, int i, int slash)
{
	DIR				*dir;
	struct dirent	*dent;
	char			*tmp;

	i += slash;
	while (arg->word[i] && arg->word[i] != '/')
	{
		if (arg->word[i] == '*')
			dir = opendir(path);
		i++;
	}
	if ((!arg->word[i] || !arg->word[i + 1]) && dir)
		add_processed_list(arg, dir, path, ft_split(arg->word, '/'));
	else if (dir)
	{
		while ((dent = readdir(dir)))
		{
			tmp = ft_strjoin("/", dent->d_name);
			tmp = ft_strjoin(path, tmp);
			if (!ft_strequ("..", dent->d_name) && !ft_strequ(".", dent->d_name))
				process_wildcard(arg, tmp, i, 1);
			free(tmp);
		}
	}
	if (dir)
		closedir(dir);
}
