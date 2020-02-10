/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 17:07:06 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/06 15:10:01 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_escaped(char *s, int pos)
{
	int n;

	n = 0;
	while (pos > 0 && s[pos] == '\\')
	{
		n++;
		pos--;
	}
	return (n % 2);
}

int		last_pipe(char *s, int pos)
{
	while (pos >= 0 && s[pos] == ' ')
		pos--;
	if (pos >= 0 && s[pos] == '|' && !is_escaped(s, pos - 1))
		return (1);
	return (0);
}

int		bracket_odd(char *s)
{
	int		bracket1;
	int		bracket2;
	int		i;

	bracket1 = 0;
	bracket2 = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == 34 && (i == 0 || !is_escaped(s, i - 1))
			&& bracket2 % 2 == 0)
			bracket1++;
		if (s[i] == 39 && (i == 0 || bracket2 % 2 != 0 || !is_escaped(s, i - 1))
			&& bracket1 % 2 == 0)
			bracket2++;
		i++;
	}
	if (bracket1 % 2 != 0 || bracket2 % 2 != 0)
		return (1);
	return (0);
}

void	next_bracket(t_minishell *minishell)
{
	char	*tmp;

	write(1, "> ", 2);
	if (get_next_line_no_eof(0, &tmp, 1))
	{
		minishell->line = ft_strjoin_free(minishell->line, "\n");
		minishell->line = ft_strjoin_free(minishell->line, tmp);
		ft_strdel(&tmp);
	}
	if (g_minishell->quit == 2)
	{
		ft_strdel(&minishell->line);
		minishell->line = ft_strjoin("", "");
		g_minishell->quit = 1;
	}
}