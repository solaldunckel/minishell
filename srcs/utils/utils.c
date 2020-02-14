/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 13:25:43 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/14 17:31:01 by haguerni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
