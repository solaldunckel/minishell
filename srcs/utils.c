/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 13:25:43 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/01 18:39:50 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(void *cmd)
{
	t_cmd 	*tmp;

	tmp = cmd;
	free(tmp->line);
	free_split(tmp->split);
	free(cmd);
}

char	*ft_strndup(const char *s1, int n)
{
	char	*str;
	int		i;
	int		to_malloc;
	int		len;

	i = 0;
	to_malloc = n;
	len = ft_strlen(s1);
	if (len < n)
		to_malloc = len;
	if (!(str = (char*)malloc(sizeof(char) * to_malloc + 1)))
		return (NULL);
	while (s1[i] && i < n)
	{
		str[i] = (char)s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**free_split(char **split)
{
	int		i;

	i = 0;
	while (split[i])
	{
		ft_strdel(&split[i]);
		i++;
	}
	free(split);
	split = NULL;
	return (split);
}

char	*ft_strjoin_free(char const *s1, char const *s2)
{
	char	*str;

	if (!(str = (char*)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)
		+ 1))))
		return (NULL);
	ft_strcpy(str, s1);
	free((void*)s1);
	ft_strcat(str, s2);
	return (str);
}

int		count_split(char **split)
{
	int		i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}
