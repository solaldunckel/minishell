/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_n.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 04:20:42 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/22 04:21:03 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c, int n)
{
	int		count;
	int		is_word;

	is_word = 0;
	count = 0;
	while (*s)
	{
		if (*s == c)
			is_word = 0;
		else if (is_word == 0)
		{
			is_word = 1;
			if (count <= n)
				count++;
		}
		s++;
	}
	return (count);
}

static size_t	w_s(char const *s, int pos, char c, int n)
{
	size_t	len;

	len = 0;
	while (s[pos])
	{
		if (s[pos] == c && !n)
			return (len);
		len++;
		pos++;
	}
	return (len);
}

char			**ft_split_n(char const *s, char c, int n)
{
	char	**tab;
	int		i;
	int		j;
	int		k;

	i = -1;
	j = 0;
	k = 0;
	if (!(tab = malloc(sizeof(char*) * (count_words(s, c, n) + 1))))
		return (NULL);
	while (s[++i])
	{
		if (s[i] != c || j == n)
		{
			if (k == 0 && j <= n)
				if (!(tab[j] = malloc(sizeof(char) * w_s(s, i, c, j % n) + 1)))
					return (NULL);
			tab[j][k] = s[i];
			tab[j][++k] = '\0';
		}
		if (s[i] == c && k > 0 && j < n && (k = 0) == 0)
			j++;
	}
	tab[count_words(s, c, n)] = NULL;
	return (tab);
}
