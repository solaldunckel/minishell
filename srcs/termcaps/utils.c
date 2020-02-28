/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 14:02:30 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/28 14:22:48 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			putchar_tc(int tc)
{
	write(1, &tc, 1);
	return (0);
}

void		print_char(long c)
{
	char	c2[2];

	c2[0] = c;
	c2[1] = '\0';
	if (g_minishell->line)
		g_minishell->line = ft_strjoin_middle(g_minishell->line, c2,
			g_tc->cur_pos + 1);
	else
		g_minishell->line = ft_strdup(c2);
	g_tc->cur_pos++;
}

void		delete_char(void)
{
	char	*str;
	int		len;

	if (!g_minishell->line)
		return ;
	len = ft_strlen(g_minishell->line);
	if (len == 1 && g_tc->cur_pos == 1)
	{
		ft_strdel(&g_minishell->line);
		g_tc->cur_pos--;
		return ;
	}
	if (!(str = (char*)ft_calloc(1, sizeof(char) * (len))))
		return ;
	ft_strlcpy(str, g_minishell->line, g_tc->cur_pos);
	ft_strncat(str, g_minishell->line + g_tc->cur_pos, len - g_tc->cur_pos);
	str[len - 1] = '\0';
	ft_strdel(&g_minishell->line);
	g_minishell->line = str;
	g_tc->cur_pos--;
}
