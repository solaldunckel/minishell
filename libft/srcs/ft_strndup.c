/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 10:03:14 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/03 10:03:20 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, int n)
{
	char	*str;
	int		i;
	int		to_malloc;
	int		len;

	i = 0;
	to_malloc = n;
	len = ft_strlen(s1);
	if (len < n)
		to_malloc = len;
	if (!(str = (char*)malloc(sizeof(char) * to_malloc + 1)))
		return (NULL);
	while (s1[i] && i < n)
	{
		str[i] = (char)s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
