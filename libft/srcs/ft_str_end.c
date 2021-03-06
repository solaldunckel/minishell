/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_end.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 17:40:29 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/24 12:13:12 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_str_end(char *str, char *end)
{
	int		i;
	int		j;

	if (!str)
		return (0);
	i = ft_strlen(str) - 1;
	j = ft_strlen(end) - 1;
	if (i < j)
		return (0);
	while (str[i] && end[j])
	{
		if (str[i] != end[j])
			return (0);
		j--;
		i--;
	}
	return (1);
}
