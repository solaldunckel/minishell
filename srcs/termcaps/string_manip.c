/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_manip.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haguerni <haguerni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 21:01:10 by haguerni          #+#    #+#             */
/*   Updated: 2020/03/04 15:45:31 by haguerni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_middle(char *s1, const char *s2, int div)
{
	char	*str;
	int		l;

	l = ft_strlen(s1) + 1;
	if (!s2)
	{
		str = ft_strdup(s1);
		free((void*)s1);
		return (str);
	}
	if (!(str = (char*)malloc(sizeof(char) * (l + 2))))
		return (NULL);
	ft_strlcpy(str, s1, div);
	str[div] = '\0';
	ft_strcat(str, s2);
	while (div < l)
	{
		str[div] = s1[div - 1];
		div++;
	}
	ft_strdel(&s1);
	str[div] = '\0';
	return (str);
}

char	*ft_strjoin_middle2(char *s1, const char *s2, int div)
{
	char	*str;
	int		l;
	char	*tmp;

	if (!s2)
	{
		str = ft_strdup(s1);
		free((void*)s1);
		return (str);
	}
	l = ft_strlen(s1) + ft_strlen(s2);
	if (!(str = (char*)malloc(sizeof(char) * (l + 1))))
		return (NULL);
	ft_strlcpy(str, s1, div + 1);
	ft_strcat(str, s2);
	tmp = ft_substr(s1, div, ft_strlen(s1) - div);
	ft_strcat(str, tmp);
	free(tmp);
	return (str);
}

void	cut_line(void)
{
	char	*to_free;

	to_free = NULL;
	if (!g_minishell->line)
		return ;
	else
		empty_space(ft_strlen(g_minishell->line) + g_tc->plen);
	to_free = g_tc->copy_cmd;
	g_tc->copy_cmd = ft_substr(g_minishell->line, g_tc->cur_pos,
		ft_strlen(g_minishell->line) - g_tc->cur_pos);
	free(to_free);
	to_free = g_minishell->line;
	g_minishell->line = ft_substr(g_minishell->line, 0, g_tc->cur_pos);
	free(to_free);
	g_tc->rowoffset = g_tc->rowoffset - g_tc->mod_offset;
	g_tc->mod_offset = 0;
}

void	copy_line(void)
{
	char	*to_free;

	to_free = NULL;
	if (!g_minishell->line)
		return ;
	to_free = g_tc->copy_cmd;
	g_tc->copy_cmd = ft_substr(g_minishell->line, g_tc->cur_pos,
		ft_strlen(g_minishell->line) - g_tc->cur_pos);
	free(to_free);
}

void	paste_line(void)
{
	char	*to_free;

	to_free = NULL;
	if (!g_tc->copy_cmd)
		return ;
	if (g_minishell->line)
	{
		empty_space(ft_strlen(g_minishell->line) + g_tc->plen);
		to_free = g_minishell->line;
		g_minishell->line = ft_strjoin_middle2(g_minishell->line,
			g_tc->copy_cmd, g_tc->cur_pos);
		free(to_free);
	}
	else
		g_minishell->line = ft_strdup(g_tc->copy_cmd);
	g_tc->cur_pos += ft_strlen(g_tc->copy_cmd);
	g_tc->rowoffset = (ft_strlen(g_minishell->line) + g_tc->plen) / g_tc->col;
	g_tc->mod_offset = (ft_strlen(g_minishell->line) - g_tc->cur_pos +
		g_tc->plen) / g_tc->col;
	g_tc->currow = g_tc->start_row + g_tc->rowoffset;
}
