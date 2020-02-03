/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 10:01:47 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/03 10:02:27 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char const *s1, char const *s2)
{
	char	*str;

	if (!(str = (char*)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)
		+ 1))))
		return (NULL);
	ft_strcpy(str, s1);
	free((void*)s1);
	ft_strcat(str, s2);
	return (str);
}
