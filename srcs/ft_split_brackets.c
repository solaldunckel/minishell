/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_brackets.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 10:52:21 by sdunckel          #+#    #+#             */
/*   Updated: 2020/01/17 11:18:07 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int		in_bracket(char const *s, int pos)
{
	int		bracket1;
	int		bracket2;

	bracket1 = 0;
	bracket2 = 0;
	while (pos > 0)
	{
		if (s[pos] == 34)
			bracket1++;
		if (s[pos] == 39)
			bracket2++;
		pos--;
	}
	if (bracket1 % 2 != 0 || bracket2 % 2 != 0)
		return (1);
	return (0);
}

static size_t	count_words(char const *s, char *set)
{
	int		i;
	int		count;
	int		is_word;

	i = 0;
	is_word = 0;
	count = 0;
	while (s[i])
	{
		if (in_s(s[i], set) && !in_bracket(s, i))
			is_word = 0;
		else if (is_word == 0)
		{
			is_word = 1;
			count++;
		}
		i++;
	}
	return (count);
}

static size_t	w_s(char const *s, int pos, char *set)
{
	size_t	len;

	len = 0;
	while (s[pos])
	{
		if (in_s(s[pos], set) && !in_bracket(s, pos))
			return (len);
		len++;
		pos++;
	}
	return (len);
}

char			**ft_split_brackets(char const *s, char *set)
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
		if (!in_s(s[i], set) || (in_s(s[i], set) && in_bracket(s, i)))
		{
			if (k == 0)
				if (!(tab[j] = malloc(sizeof(char) * w_s(s, i, set) + 1)))
					return (NULL);
			tab[j][k] = s[i];
			tab[j][++k] = '\0';
		}
		if ((in_s(s[i], set) && !in_bracket(s, i) && !in_s(s[i + 1], set) && k > 0) && (k = 0) == 0)
			j++;
	}
	tab[count_words(s, set)] = NULL;
	return (tab);
}
