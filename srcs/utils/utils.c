/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 13:25:43 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/17 18:11:00 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**join_args(t_cmd *cmd)
{
	char	**args;
	t_token	*tmp;
	int		i;

	i = 1;
	if (!(args = (char **)ft_calloc(1, sizeof(char *) *
		(token_list_size(&cmd->args) + 2))))
		exit_cmd(g_minishell);
	args[0] = cmd->cmd;
	tmp = cmd->args;
	while (tmp)
	{
		args[i] = tmp->word;
		tmp = tmp->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

char	*handle_quotes(char *src)
{
	int		i;
	int		j;
	char	*dest;

	if (src == NULL || (ft_is_in_stri('\"', src) == -1 &&
		ft_is_in_stri('\'', src) == -1 && ft_is_in_stri('\\', src) == -1))
		return (src);
	i = 0;
	!bracket_odd(src, 0) && (src[0] == '\"' || src[0] == '\'') ? i = 1 : 0;
	j = 0;
	if (!(dest = (char *)ft_calloc(1, ft_strlen(src) + 2)))
		exit_cmd(g_minishell);
	while (src[i])
	{
		if (src[i] != '\\' || src[0] == '\'')
			dest[j++] = src[i];
		else
			dest[j++] = src[++i];
		i++;
	}
	!bracket_odd(src, 0) && (dest[j - 1] == '\"' || dest[j - 1] == '\'') ?
		dest[j - 1] = '\0' : 0;
	dest[j] = '\0';
	return (dest);
}

char	*supp_newline(char *src)
{
	int		i;
	int		j;
	char	*dest;

	if (!src)
		return (NULL);
	if (ft_is_in_stri('\n', src) == -1)
		return (src);
	i = 0;
	j = 0;
	if (!(dest = (char *)ft_calloc(1, ft_strlen(src))))
		exit_cmd(g_minishell);
	while (src[i])
	{
		if (src[i] != '\n')
		{
			dest[j] = src[i];
			j++;
		}
		i++;
	}
	dest[j] = '\0';
	return (dest);
}

void	nothing(void *cmd)
{
	(void)cmd;
}
