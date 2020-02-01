/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 18:10:04 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/01 18:41:06 by sdunckel         ###   ########.fr       */
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

void	add_to_list(t_minishell *minishell)
{
	t_cmd_list	*tmp;
	t_cmd_list	*new;

	if (!ft_strlen(minishell->buf))
		return;
	if (!(new = malloc(sizeof(t_cmd_list))))
		return ;
	new->token = ft_strndup(minishell->buf, minishell->buf_count);
	minishell->buf_count = 0;
	tmp = minishell->token_list;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		minishell->token_list = new;

}

void	start_parse(t_minishell *minishell, char *str)
{
	int		i;

	minishell->buf_count = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == ' ' && !in_bracket(str, i))
		{
			add_to_list(minishell);
			continue;
		}
		minishell->buf[minishell->buf_count] = str[i];
		minishell->buf_count++;
		if (str[i] == '>' || str[i] == '<' || str[i] == '|' || str[i] == ';')
			add_to_list(minishell);
		if (str[i + 1] == '\0')
			add_to_list(minishell);
	}
}

//echo test> allo > allo test | echo " test > allo" > test ; ls -la
