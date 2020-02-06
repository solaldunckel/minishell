/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 18:33:36 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/06 01:56:23 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (ft_strlen(args->word) && args->next)
			ft_putchar(' ');
		args = args->next;
	}
	if (endl)
		ft_putchar('\n');
}
