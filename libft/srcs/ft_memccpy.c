/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 18:01:11 by sdunckel          #+#    #+#             */
/*   Updated: 2019/10/08 17:36:53 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	char			*sd;
	char			*sr;
	unsigned char	uc;

	sd = dst;
	sr = (void*)src;
	uc = c;
	i = 0;
	while (i < n)
	{
		sd[i] = sr[i];
		i++;
		if (sr[i - 1] == uc)
			return (dst + i);
	}
	return (NULL);
}
