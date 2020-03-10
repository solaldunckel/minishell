/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 13:25:43 by sdunckel          #+#    #+#             */
/*   Updated: 2020/03/09 18:16:13 by haguerni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**join_args(t_cmd *cmd)
{
	char	**args;
	t_token	*tmp;
	int		i;

	i = 1;
	if (!cmd->cmd)
		return (NULL);
	if (!(args = (char **)ft_calloc(1, sizeof(char *) *
		(token_list_size(&cmd->args) + 2))))
		exit_cmd(g_minishell);
	args[0] = ft_strdup(cmd->cmd);
	tmp = cmd->args;
	while (tmp)
	{
		args[i] = ft_strdup(tmp->word);
		tmp = tmp->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

char	*handle_quotes(char *src, int env)
{
	int		i;
	char	*dest;

	if (src == NULL)
		return (src);
	i = 0;
	dest = ft_strdup("");
	while (src[i])
	{
		if (src[i] == '\'' && !is_escaped(src, i - 1))
			dest = ft_strjoin_double_free(dest, simple_quotes(src, &i));
		else if (src[i] == '\"' && !is_escaped(src, i - 1))
		{
			i++;
			dest = ft_strjoin_double_free(dest, double_quotes(src, &i, 0, env));
		}
		else
		{
			dest = ft_strjoin_double_free(dest, no_quotes(src, &i, 0, env));
			continue ;
		}
		src[i] ? i++ : 0;
	}
	ft_strdel(&src);
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

void	ft_sort_list(t_list **begin_list, int (*cmp)())
{
	t_list	*ptr;
	t_list	*ptr2;
	t_list	*next;

	ptr = *begin_list;
	while (ptr)
	{
		ptr2 = *begin_list;
		while (ptr2->next)
		{
			if ((*cmp)(((t_env*)(ptr2->content))->name,
				((t_env*)(ptr2->next->content))->name) > 0)
			{
				next = ptr2->content;
				ptr2->content = ptr2->next->content;
				ptr2->next->content = next;
			}
			ptr2 = ptr2->next;
		}
		ptr = ptr->next;
	}
}

int		is_only_ascii(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isascii(str[i]))
			return (0);
		i++;
	}
	return (1);
}
