/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 13:25:43 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/21 18:17:23 by haguerni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**join_args(t_cmd *cmd)
{
	char	**args;
	t_token	*tmp;
	int		i;

	i = 1;
	if (!(args = (char **)ft_calloc(1, sizeof(char *) *
		(token_list_size(&cmd->args) + 2))))
		exit_cmd(g_minishell);
	args[0] = cmd->cmd;
	tmp = cmd->args;
	while (tmp)
	{
		args[i] = tmp->word;
		tmp = tmp->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

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

char	*handle_quotes(char *src)
{
	int		i;
	char	*dest;

	if (src == NULL)
		return (src);
	i = 0;
	dest = ft_strdup("");
	while (src[i])
	{
		if (src[i] == '\'' && !is_escaped(src, i - 1))
			dest = ft_strjoin_double_free(dest, simple_quotes(src, &i));
		else if (src[i] == '\"' && !is_escaped(src, i - 1))
			dest = ft_strjoin_double_free(dest, double_quotes(src, &i, 0));
		else
		{
			dest = ft_strjoin_double_free(dest, no_quotes(src, &i, 0));
			continue ;
		}
		src[i] ? i++ : 0;
	}
	return (dest);
}

char	*supp_newline(char *src)
{
	int		i;
	int		j;
	char	*dest;

	if (!src)
		return (NULL);
	if (ft_is_in_stri('\n', src) == -1)
		return (src);
	i = 0;
	j = 0;
	if (!(dest = (char *)ft_calloc(1, ft_strlen(src))))
		exit_cmd(g_minishell);
	while (src[i])
	{
		if (src[i] != '\n')
		{
			dest[j] = src[i];
			j++;
		}
		i++;
	}
	dest[j] = '\0';
	return (dest);
}

void	nothing(void *cmd)
{
	(void)cmd;
}
