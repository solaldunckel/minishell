/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 00:13:06 by sdunckel          #+#    #+#             */
/*   Updated: 2020/03/04 20:00:01 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_slash(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '/' && i != 0)
			count++;
		i++;
	}
	return (count);
}

char	*create_wildpath(char *s)
{
	int		i;
	char	*dest;

	i = 0;
	if (!(dest = (char *)malloc(ft_strlen_c(s, '*') + 2)))
		return (NULL);
	while (s[i] && (s[i] == '/' || s[i] == '.'))
	{
		dest[i] = s[i];
		i++;
	}
	if (i == 0 || s[i - 1] == '/')
	{
		dest[i] = '.';
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int		ft_strmatch(char *s1, char *s2, int i, int j)
{
	int	k;

	if ((!s1[i] || (!s1[i + 1] && s1[i] == '*')) && !s2[j])
		return (1);
	if (!s2[j])
		return (0);
	if (s1[i] == s2[j])
		return (ft_strmatch(s1, s2, i + 1, j + 1));
	k = j;
	if (s1[i] == '*')
		while (s2[k])
			if (ft_strmatch(s1, s2, i + 1, k++))
				return (1);
	if (s1[i] == '*' && s1[i + 1] == s2[j + 1])
		return (ft_strmatch(s1, s2, i + 1, j + 1));
	if (s1[i] == '*')
		return (ft_strmatch(s1, s2, i, j + 1));
	return (0);
}

void	add_arg(t_token *arg, char *tmp)
{
	t_token	*new;
	char	*word;

	tmp += 2;
	word = ft_strdup(tmp);
	new = create_arg_token(word, T_WORD);
	free(word);
	new->prev = arg;
	new->next = arg->next;
	new->next ? new->next->prev = new : 0;
	arg->next = new;
	arg->type = 11;
}

void	process_wildcard(t_token *arg, char *path, int i, char **split)
{
	DIR				*dir;
	struct dirent	*dent;
	char			*tmp;
	int				slash;

	slash = count_slash(path);
	!i ? i += ft_strlen(path) - 1 : 0;
	dir = opendir(path);
	while (arg->word[i] && arg->word[i] != '/')
		i++;
	while (split[slash] && dir && (dent = readdir(dir)))
	{
		tmp = ft_strjoin("/", dent->d_name);
		tmp = ft_strfree_join(path, tmp);
		if ((!arg->word[i] || !arg->word[i + 1]) && ft_strmatch(split[slash],
			dent->d_name, 0, 0) && (ft_strequ(dent->d_name, split[slash]) ||
			dent->d_name[0] != '.' || split[slash][0] == '.'))
			add_arg(arg, tmp);
		else if (ft_strmatch(split[slash], dent->d_name, 0, 0) &&
			(ft_strequ(dent->d_name, split[slash]) || dent->d_name[0] != '.' ||
			split[slash][0] == '.'))
			process_wildcard(arg, tmp, i + 1, split);
		free(tmp);
	}
	dir ? closedir(dir) : 0;
}
