/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 10:51:06 by sdunckel          #+#    #+#             */
/*   Updated: 2020/01/14 15:06:20 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_cmd(t_minishell *minishell)
{
	int		i;
	int		endl;

	i = 1;
	endl = 1;
	while (ft_strequ(minishell->split[i], "-n"))
	{
		endl = 0;
		i++;
	}
	while (minishell->split[i])
	{
		ft_putstr(minishell->split[i]);
		if (ft_strlen(minishell->split[i]) && minishell->split[i + 1])
			ft_putchar(' ');
		i++;
	}
	if (endl)
		ft_putchar('\n');
}
