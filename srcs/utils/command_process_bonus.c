/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haguerni <haguerni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 17:37:03 by haguerni          #+#    #+#             */
/*   Updated: 2020/02/21 18:17:45 by haguerni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_envlen(char *src, int i)
{
	int		count;
	char	buf[4096];

	count = 0;
	ft_bzero(buf, sizeof(buf));
	i++;
	while (src[i] && !is_char_str(src[i], "$ \'\"\n="))
	{
		buf[count] = src[i];
		i = i + 1;
		count++;
	}
	if (get_env(g_minishell, buf))
		count = ft_strlen(get_env(g_minishell, buf));
	return (count);
}

int		ft_quotelen(char *src, int type)
{
	int	i;
	int	j;
	int	esc;

	i = 0;
	j = 0;
	esc = 0;
	while (src[i])
	{
		if (!esc && src[i] == '\'' && type == 2)
			return (i);
		if (!esc && src[i] == '\'' && type == 0)
			return (i + j);
		if (!esc && src[i] == '$' && (type == 0 || type == 1 || type == 4))
			j += ft_envlen(src, i);
		if (!esc && src[i] == '\"' && (type == 0 || type == 1))
			return (i + j);
		esc = 0;
		src[i] == '\\' && type != 2 ? esc = 1 : 0;
		i++;
	}
	return (i + j);
}

char	*simple_quotes(char *src, int *i)
{
	char	*dest;
	int		j;

	(*i)++;
	j = ft_quotelen(src + *i, 2);
	if (!(dest = (char *)ft_calloc(1, j + 1)))
		exit_cmd(g_minishell);
	j = 0;
	while (src[*i] && src[*i] != '\'')
	{
		dest[j] = src[*i];
		*i = *i + 1;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

char	*no_quotes(char *src, int *i, int j)
{
	char	*dest;
	char	*tmp;
	int		k;

	k = ft_quotelen(src + *i, 0);
	if (!(dest = (char *)ft_calloc(1, k + 5)))
		exit_cmd(g_minishell);
	while (src[*i] && j < k)
	{
		if ((src[*i] == '\'' || src[*i] == '\"') && !is_escaped(src, *i - 1))
			break ;
		if (src[*i] == '$' && !is_escaped(src, *i - 1))
		{
			tmp = replace_env2(src, i);
			j = ft_strlcat(dest, tmp, k);
			free(tmp);
			continue ;
		}
		if ((src[*i] != '\\' || is_escaped(src, *i - 1)) && j < k)
			dest[j++] = src[*i];
		(*i)++;
	}
	dest[j] = '\0';
	return (dest);
}

char	*double_quotes(char *src, int *i, int j)
{
	char	*dest;
	char	*tmp;
	int		k;

	(*i)++;
	k = ft_quotelen(src + *i, 1);
	if (!(dest = (char *)ft_calloc(1, k + 1)))
		exit_cmd(g_minishell);
	while (src[*i] && j < k)
	{
		if (src[*i] == '\"' && !is_escaped(src, *i - 1))
			break ;
		if (src[*i] == '$' && !is_escaped(src, *i - 1))
		{
			tmp = replace_env2(src, i);
			j = ft_strlcat(dest, tmp, k);
			free(tmp);
			continue ;
		}
		if ((src[*i] != '\\' || is_escaped(src, *i - 1)) && j < k)
			dest[j++] = src[*i];
		(*i)++;
	}
	dest[j] = '\0';
	return (dest);
}