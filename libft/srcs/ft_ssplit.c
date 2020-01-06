/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 16:23:19 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/15 18:32:15 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		in_s(char c, char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	count_words(char const *s, char *set)
{
	int		count;
	int		is_word;

	is_word = 0;
	count = 0;
	while (*s)
	{
		if (in_s(*s, set))
			is_word = 0;
		else if (is_word == 0)
		{
			is_word = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static size_t	w_s(char const *s, int pos, char *set)
{
	size_t	len;

	len = 0;
	while (s[pos])
	{
		if (in_s(s[pos], set))
			return (len);
		len++;
		pos++;
	}
	return (len);
}

char			**ft_ssplit(char const *s, char *set)
{
	char	**tab;
	int		i;
	int		j;
	int		k;

	i = -1;
	j = 0;
	k = 0;
	if (!(tab = malloc(sizeof(char*) * (count_words(s, set) + 1))))
		return (NULL);
	while (s[++i])
	{
		if (!in_s(s[i], set))
		{
			if (k == 0)
				if (!(tab[j] = malloc(sizeof(char) * w_s(s, i, set) + 1)))
					return (NULL);
			tab[j][k] = s[i];
			tab[j][++k] = '\0';
		}
		if ((in_s(s[i], set) && !in_s(s[i + 1], set) && k > 0) && (k = 0) == 0)
			j++;
	}
	tab[count_words(s, set)] = NULL;
	return (tab);
}
