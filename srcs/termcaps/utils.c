/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 14:02:30 by sdunckel          #+#    #+#             */
/*   Updated: 2020/03/04 14:51:35 by haguerni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	empty_space(int len)
{
	int		i;
	int		j;
	char	space[1028];

	g_tc->start_row + g_tc->rowoffset >= g_tc->row ?
		g_tc->start_row = g_tc->currow - g_tc->rowoffset : 0;
	tputs(tgoto(g_tc->cm, g_tc->start_col, g_tc->start_row), 1, putchar_tc);
	tputs(g_tc->ce, 1, putchar_tc);
	i = 0;
	j = 0;
	while (j < len)
	{
		space[i] = ' ';
		i++;
		j++;
		if (i == g_tc->col)
		{
			write(1, space, i);
			i = 0;
		}
	}
	write(1, space, i);
}

int		putchar_tc(int tc)
{
	write(1, &tc, 1);
	return (0);
}

void	print_char(long c)
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

void	delete_char(void)
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
	ft_strdel(&g_minishell->line);
	g_minishell->line = str;
	g_tc->cur_pos--;
}

char	*ft_sdpfr(const char *s1, char *s2)
{
	char	*str;
	int		i;

	i = 0;
	if (!(str = (char*)malloc(sizeof(char) * ft_strlen(s1) + 1)))
		return (NULL);
	while (s1[i])
	{
		str[i] = (char)s1[i];
		i++;
	}
	str[i] = '\0';
	free(s2);
	s2 = NULL;
	return (str);
}
