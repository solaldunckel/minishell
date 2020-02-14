/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 13:25:43 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/12 19:29:18 by haguerni         ###   ########.fr       */
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

void	nothing(void *cmd)
{
	(void)cmd;
}

int		is_char_str(char c, char *str)
{
	if (ft_is_in_stri(c, str) >= 0)
		return (1);
	return (0);
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
	!bracket_odd(src) && (src[0] == '\"' || src[0] == '\'') ? i = 1 : 0;
	j = 0;
	if (!(dest = (char *)malloc(ft_strlen(src) + 2)))
		return (NULL);
	while (src[i])
	{
		if (src[i] != '\\' || src[0] == '\'')
			dest[j++] = src[i];
		else
			dest[j++] = src[++i];
		i++;
	}
	!bracket_odd(src) && (dest[j - 1] == '\"' || dest[j - 1] == '\'') ?
		dest[j - 1] = '\0' : 0;
	dest[j] = '\0';
	return (dest);
}

char	*supp_newline(char *src)
{
	int		i;
	int		j;
	char	*dest;

	if (ft_is_in_stri('\n', src) == -1 || src == NULL)
		return (src);
	i = 0;
	j = 0;
	if (!(dest = (char *)malloc(ft_strlen(src))))
		return (NULL);
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
	free(src);
	src = NULL;
	return (dest);
}
