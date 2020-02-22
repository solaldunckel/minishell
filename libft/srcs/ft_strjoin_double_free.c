/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_double_free.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 04:22:58 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/22 04:23:03 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_double_free(char const *s1, char const *s2)
{
	char	*str;

	if (!s2)
	{
		str = ft_strdup(s1);
		free((void*)s1);
		return (str);
	}
	if (!(str = (char*)ft_calloc(1, sizeof(char)
		* (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	ft_strcpy(str, s1);
	free((void*)s1);
	ft_strcat(str, s2);
	free((void*)s2);
	return (str);
}
