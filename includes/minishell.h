/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 11:17:02 by sdunckel          #+#    #+#             */
/*   Updated: 2020/01/03 10:33:42 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdarg.h>
# include <string.h>
# include <stdio.h>

# include <curses.h>
# include <term.h>
# include <errno.h>

# define ECHO_CMD "echo"
# define EXIT_CMD "exit"
# define CD_CMD "cd"
# define PWD_CMD "pwd"
# define ENV_CMD "env"
# define EXPORT_CMD "export"
# define UNSET_CMD "unset"

typedef struct	s_minishell
{
	char	*name;
	char 	*curdir;
	char	*line;
	char	**split;
	t_list	*env_list;
}				t_minishell;

void	echo_cmd(t_minishell *minishell);
void	cd_cmd(t_minishell *minishell);
void	pwd_cmd(t_minishell *minishell);
void	exec_prog(t_minishell *minishell);
char	*get_env(t_minishell *minishell, char *env);

#endif
