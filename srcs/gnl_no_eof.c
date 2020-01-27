/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_no_eof.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haguerni <haguerni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 19:38:21 by haguerni          #+#    #+#             */
/*   Updated: 2020/01/27 17:52:31 by haguerni         ###   ########.fr       */
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
	return (SUCCESS);
}

int				ctrl_d_exit(void)
{
	write(1, " exit\n", 6);
	return (0);
}

int				get_next_line_no_eof(int fd, char **line, int *b)
{
	static char		*s[2];
	char			buf[2];
	int				ret;
	char			*tmp;

	if (fd < 0 || !line || BUFFER_SIZE < 1 || read(fd, buf, 0) < 0
	|| (!s[fd] && !(s[fd] = ft_calloc(1, sizeof(char *)))))
		return (ERROR);
	while ((ft_is_in_stri('\n', s[fd]) < 0 &&
		(ret = read(fd, buf, 1)) >= 0))
	{
		signal(SIGINT, sighandler);
		if ((buf[ret] = '\0') == 0 && ret == 0 && ft_strlen(s[fd]) == 0 && !*b)
			exit(ctrl_d_exit());
		g_minishell->quit == 1 ? free(s[fd]) : 0;
		if (g_minishell->quit == 1 && (g_minishell->quit = 0) == 0)
			s[fd] = ft_calloc(1, sizeof(char *));
		tmp = s[fd];
		s[fd] = ft_strjoin(s[fd], buf);
		free(tmp);
	}
	s[fd] ? *line = ft_substr(s[fd], 0, ft_strlen_c(s[fd], '\n')) : 0;
	if (!handle_line(s, fd))
		return (FINISH);
	return (SUCCESS);
}
