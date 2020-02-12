/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 13:25:43 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/12 16:35:05 by haguerni         ###   ########.fr       */
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
	int		bracket1;
	int		bracket2;

	bracket1 = 0;
	bracket2 = 0;
	while (pos >= 0)
	{
		if (s[pos] == 34 && (pos == 0 || !is_escaped(s, pos - 1)))
			bracket1++;
		if (s[pos] == 39)
			bracket2++;
		pos--;
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
