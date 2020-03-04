/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 18:33:36 by sdunckel          #+#    #+#             */
/*   Updated: 2020/03/04 17:19:19 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_strlen_s(char *s)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != ' ')
			count++;
		i++;
	}
	return (count);
}

void	echo_cmd(t_minishell *minishell, t_cmd *cmd)
{
	t_token		*args;
	int			endl;

	args = cmd->args;
	endl = 1;
	while (args && ft_strequ(args->word, "-n"))
	{
		endl = 0;
		args = args->next;
	}
	while (args)
	{
		ft_putstr(args->word);
		if (args->next)
			ft_putchar(' ');
		args = args->next;
	}
	if (endl)
		ft_putchar('\n');
	minishell->exit = 0;
}
