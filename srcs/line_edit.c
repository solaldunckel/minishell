/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haguerni <haguerni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 17:22:38 by haguerni          #+#    #+#             */
/*   Updated: 2020/01/24 17:33:09 by haguerni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_term()
{
	int ret;
	char *term_type = getenv("TERM");

	if (term_type == NULL)
	{
		ft_dprintf(2, "TERM must be set (see 'env').\n");
		return (-1);
	}
	ret = tgetent(NULL, term_type);
	if (ret == -1)
	{
		ft_dprintf(2, "Could not access to the termcap database..\n");
		return (-1);
	}
	else if (ret == 0)
	{
		fprintf(stderr, "Terminal type '%s' is not defined in termcap database("
		"or have too few informations).\n", term_type);
		return (-1);
	}
	return (0);
}

int	term_edit(t_minishell *minishell)
{
	int	ret = setupterm(NULL, 0, NULL)
	/* Termcap */
	int column_count = tgetnum("co");
	int line_count = tgetnum("li");

	/* Terminfo */
	int column_count = tigetnum("cols");
	int line_count = tigetnum("lines");
}
