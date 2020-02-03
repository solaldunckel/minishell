/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 10:00:22 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/03 10:06:29 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_split(char ***split)
{
	int		i;

	i = 0;
	while (*split[i])
	{
		ft_strdel(&(*split[i]));
		i++;
	}
	free(*split);
	*split = NULL;
}
