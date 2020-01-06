/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 18:11:10 by sdunckel          #+#    #+#             */
/*   Updated: 2019/10/09 10:59:58 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*sd;
	char	*sr;

	sd = dst;
	sr = (void*)src;
	i = 0;
	if (sr < sd)
	{
		i++;
		while (i <= len)
		{
			sd[len - i] = sr[len - i];
			i++;
		}
	}
	else
	{
		while (i < len)
		{
			sd[i] = sr[i];
			i++;
		}
	}
	return (dst);
}
