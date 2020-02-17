/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haguerni <haguerni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 17:30:17 by haguerni          #+#    #+#             */
/*   Updated: 2020/02/17 16:37:59 by haguerni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(void *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	free(tmp->cmd);
	free(cmd);
}

char	*replace_env(t_minishell *minishell, char *str)
{
	int		i;
	int		count;
	char	buf[4096];
	char	*new;

	new = ft_strdup("");
	i = 0;
	count = 0;
	ft_bzero(buf, sizeof(buf));
	while (str[i])
	{
		while (str[i] && str[i] == '$')
		{
			new = ft_strjoin_free(new, buf);
			ft_bzero(buf, count);
			count = 0;
			i++;
			while (str[i] && !is_char_str(str[i], "$ \'\"\n"))
			{
				buf[count] = str[i];
				i++;
				count++;
			}
			new = ft_strjoin_free(new, get_env(minishell, buf));
			ft_bzero(buf, count);
			count = 0;
		}
		buf[count] = str[i];
		count++;
		i++;
	}
	new = ft_strjoin_free(new, buf);
	return (new);
}

void	process_args(t_minishell *minishell, t_cmd *cmd)
{
	t_token	*tmp;
	char	*to_free;

	if (ft_is_in_stri('$', cmd->cmd) >= 0)
		cmd->cmd = replace_env(minishell, cmd->cmd);
	tmp = cmd->args;
	while (tmp)
	{
		if (ft_is_in_stri('$', tmp->word) >= 0)
			tmp->word = replace_env(minishell, tmp->word);
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
