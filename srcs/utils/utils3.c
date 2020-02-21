/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 18:41:55 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/21 18:17:17 by haguerni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_env2(char *str, int *i)
{
	int		count;
	char	buf[4096];
	char	*new;

	new = ft_strdup("");
	count = 0;
	(*i)++;
	ft_bzero(buf, sizeof(buf));
	while (str[*i] && !is_char_str(str[*i], "$ \'\"\n="))
	{
		buf[count] = str[*i];
		*i = *i + 1;
		count++;
	}
	new = ft_strjoin_free(new, get_env(g_minishell, buf));
	return (new);
}

void	free_env2(void *lst)
{
	t_env	*env;

	env = lst;
	ft_strdel(&env->name);
	ft_strdel(&env->value);
	free(env);
}

int		is_only_digit(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_sort_list(t_list **begin_list, int (*cmp)())
{
	t_list	*ptr;
	t_list	*ptr2;
	t_list	*next;

	ptr = *begin_list;
	while (ptr)
	{
		ptr2 = *begin_list;
		while (ptr2->next)
		{
			if ((*cmp)(((t_env*)(ptr2->content))->name,
				((t_env*)(ptr2->next->content))->name) > 0)
			{
				next = ptr2->content;
				ptr2->content = ptr2->next->content;
				ptr2->next->content = next;
			}
			ptr2 = ptr2->next;
		}
		ptr = ptr->next;
	}
}
