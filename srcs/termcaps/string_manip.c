/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_manip.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haguerni <haguerni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 21:01:10 by haguerni          #+#    #+#             */
/*   Updated: 2020/02/27 20:50:18 by sdunckel         ###   ########.fr       */
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

void	cut_line(void)
{
	if (!g_minishell->line)
		return ;
	g_tc->copy_cmd = ft_strdup(g_minishell->line);
	g_tc->cur_pos = 0;
	g_minishell->line = NULL;
}

void	copy_line(void)
{
	if (!g_minishell->line)
		return ;
	g_tc->copy_cmd = ft_strdup(g_minishell->line);
}

void	paste_line(void)
{
	if (!g_tc->copy_cmd)
		return ;
	if (g_minishell->line)
		g_minishell->line = ft_strjoin_free(g_minishell->line, g_tc->copy_cmd);
	else
		g_minishell->line = ft_strdup(g_tc->copy_cmd);
	g_tc->cur_pos += ft_strlen(g_tc->copy_cmd);
}
