/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 18:10:04 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/02 16:37:03 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		in_bracket(char *s, int pos)
{
	int		bracket1;
	int		bracket2;

	bracket1 = 0;
	bracket2 = 0;
	while (pos > 0)
	{
		if (s[pos] == 34)
			bracket1++;
		if (s[pos] == 39)
			bracket2++;
		pos--;
	}
	if (bracket1 % 2 != 0 || bracket2 % 2 != 0)
		return (1);
	return (0);
}

void	start_parse(t_minishell *minishell, char *str)
{
	int		i;

	minishell->buf_count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' && !in_bracket(str, i))
		{
			add_token_list(&minishell->token_list, create_token(minishell));
			i++;
			continue;
		}
		if ((str[i] == '>' || str[i] == '<' || str[i] == '|' || str[i] == ';')
			&& !in_bracket(str, i))
			add_token_list(&minishell->token_list, create_token(minishell));
		minishell->buf[minishell->buf_count] = str[i];
		minishell->buf_count++;
		if ((str[i] == '>' || str[i] == '<' || str[i] == '|' || str[i] == ';')
			&& !in_bracket(str, i))
			add_token_list(&minishell->token_list, create_token(minishell));
		i++;
	}
	add_token_list(&minishell->token_list, create_token(minishell));
}

//echo test> allo > allo test | echo " test > allo" > test ; ls -la
