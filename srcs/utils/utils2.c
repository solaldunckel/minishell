/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haguerni <haguerni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 17:30:17 by haguerni          #+#    #+#             */
/*   Updated: 2020/02/20 18:44:02 by haguerni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(void *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	ft_strdel(&tmp->cmd);
	free(cmd);
}

char	*replace_env(char *str, int i)
{
	int		k;
	int		j;
	char	*tmp;
	char	*new;

	k = ft_quotelen(str, 4);
	if (!(new = (char *)ft_calloc(1, k + 1)))
		exit (1);
	j = 0;
	while (str[i] && j < k)
	{
		if (str[i] == '$' && !is_escaped(str, i - 1))
		{
			tmp = replace_env2(str, &i);
			j = ft_strlcat(new, tmp, k);
			free(tmp);
			continue ;
		}
		if ((str[i] != '\\' || is_escaped(str, i - 1)) && j < k)
			new[j++] = str[i];
		i++;
	}
	free(str);
	return (new);
}

void	process_args(t_minishell *minishell, t_cmd *cmd)
{
	t_token	*tmp;

	(void)minishell;
	if (cmd->cmd)
		cmd->cmd = handle_quotes(cmd->cmd);
	tmp = cmd->args;
	while (tmp)
	{
		tmp->word = handle_quotes(tmp->word);
		tmp = tmp->next;
	}
}

int		in_bracket(char *s, int pos)
{
	int	bracket1;
	int	bracket2;
	int	i;

	bracket1 = 0;
	bracket2 = 0;
	i = 0;
	while (i <= pos)
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

int		is_char_str(char c, char *str)
{
	if (ft_is_in_stri(c, str) >= 0)
		return (1);
	return (0);
}
