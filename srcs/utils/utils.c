/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 13:25:43 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/08 19:19:27 by haguerni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(void *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	free(tmp->cmd);
	//ft_free_split(&tmp->args);
	free(cmd);
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
	//free(src);
	src = NULL;
	return (dest);
}
