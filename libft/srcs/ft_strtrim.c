/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 09:40:41 by sdunckel          #+#    #+#             */
/*   Updated: 2019/10/16 22:02:19 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;

	start = 0;
	end = ft_strlen(s1);
	while (ft_is_in_stri(s1[start], (char*)set) >= 0)
		start++;
	if ((end - start) <= 0)
		return (ft_substr(s1, 0, 0));
	while (ft_is_in_stri(s1[end - 1], (char*)set) >= 0)
		end--;
	return (ft_substr(s1, start, end - start));
}
