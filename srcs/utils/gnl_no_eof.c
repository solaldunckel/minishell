/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_no_eof.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haguerni <haguerni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 19:38:21 by haguerni          #+#    #+#             */
/*   Updated: 2020/03/10 18:06:05 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		handle_line(char *s[], int fd)
{
	char	*tmp;

	if (ft_is_in_stri('\n', s[fd]) >= 0)
	{
		tmp = s[fd];
		s[fd] = ft_substr(s[fd], ft_is_in_stri('\n', s[fd]) + 1,
			ft_strlen(s[fd]));
		free(tmp);
	}
	else if (ft_strlen(s[fd]) > 0)
		ft_strdel(&s[fd]);
	else
	{
		ft_strdel(&s[fd]);
		return (FINISH);
	}
	ft_strdel(&s[fd]);
	return (SUCCESS);
}

int				ctrl_d_exit(int b, char *s)
{
	if (b == 1)
	{
		ft_dprintf(2, " %s: unexpected EOF while looking for matching"
			" `\"\'\n%s: syntax error: unexpected end of file\n",
			g_minishell->name, g_minishell->name);
		g_minishell->quit = 1;
		g_minishell->quit2 = 1;
	}
	if (b == 2)
	{
		g_minishell->quit = 2;
		g_minishell->quit2 = 1;
	}
	if (!b)
	{
		ft_strdel(&s);
		exit_cmd4(g_minishell);
	}
	return (0);
}

void			set_quit(char **str, int *b)
{
	if (g_minishell->quit == 1)
	{
		ft_strdel(str);
		if (!(*str = ft_calloc(1, sizeof(char *))))
			exit_cmd(g_minishell);
		if (*b == 1)
			*b = 0;
	}
}

int				get_next_line_no_eof(int fd, char **line, int b)
{
	static char		*s[2];
	char			buf[2];
	int				ret;
	char			*tmp;

	if (fd < 0 || !line || BUFFER_SIZE < 1 || read(fd, buf, 0) < 0
		|| (!s[fd] && !(s[fd] = ft_calloc(1, sizeof(char *)))))
		return (ERROR);
	while ((ft_is_in_stri('\n', s[fd]) < 0 && (ret = read(fd, buf, 1)) >= 0))
	{
		set_quit(&s[fd], &b);
		if ((buf[ret] = '\0') == 0 && ret == 0 && ft_strlen(s[fd]) == 0
			&& g_minishell->quit != 4)
			ctrl_d_exit(b, s[fd]);
		ft_dprintf(2, "  \b\b");
		tmp = s[fd];
		s[fd] = ft_strjoin(s[fd], buf);
		free(tmp);
		if (g_minishell->quit != 0 && (g_minishell->quit = 2) == 2)
			return (0);
	}
	s[fd] ? *line = ft_substr(s[fd], 0, ft_strlen_c(s[fd], '\n')) : 0;
	if (!handle_line(s, fd))
		return (FINISH);
	return (SUCCESS);
}
