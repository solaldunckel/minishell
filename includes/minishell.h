/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 11:17:02 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/03 13:43:02 by sdunckel         ###   ########.fr       */
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
# include <dirent.h>
# include <signal.h>

# include <curses.h>
# ifdef NCURSES
#  include <term.h>
# endif
# include <errno.h>

# define ECHO_CMD "echo"
# define EXIT_CMD "exit"
# define CD_CMD "cd"
# define PWD_CMD "pwd"
# define ENV_CMD "env"
# define EXPORT_CMD "export"
# define UNSET_CMD "unset"

# define NORMAL 0
# define PIPE 1

# define T_WORD 1
# define T_PIPE 2

typedef struct		s_minishell
{
	char			*name;
	char			*curdir;
	int				exit;
	char			*line;
	char			**split;
	int				fd_out;
	int				fd_in;
	int				in;
	int				out;
	int				quit;
	char			*tmp;
	int				buf_count;
	char			buf[256];
	t_list			*cmd_list;
	t_list			*env_list;
	struct s_token	*token_list;
	char			**env_array;
	char			**bin;
}					t_minishell;

typedef struct		s_env
{
	char	*name;
	char	*value;
}					t_env;

typedef struct		s_cmd
{
	char			*cmd;
	char			**args;
	int				pipe[2];
	int				in;
	int				out;
	int				type;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}					t_cmd;

typedef struct		s_token
{
	char				*word;
	struct s_token		*next;
}					t_token;

t_minishell			*g_minishell;

// ENV
void				env_init(t_minishell *minishell, char **env);
t_env				*create_env(t_minishell *minishell, char **split);
char				*get_env(t_minishell *minishell, char *env);
char				*replace_env(t_minishell *minishell, char *line);
char				**env_to_array(t_minishell *minishell);

// BIN
void				parse_bin(t_minishell *minishell);
char				*get_bin(t_minishell *minishell, char *cmd);

// PARSING
void				start_parse(t_minishell *minishell, char *str);


// BRACKET

int					bracket_odd(char *s);
void				next_bracket(t_minishell *minishell);

// TOKEN
t_token				*create_token(t_minishell *minishell);
void				clear_token_list(t_token **begin, void (*del)(void *));
void				add_token_list(t_token **begin, t_token *new);

// UTILS
char				*ft_strndup(const char *s1, int n);
char				**ft_split_brackets(char const *s, char *set);
void				free_cmd(void *cmd);
char				**free_split(char **split);
int					count_split(char **split);
char				*ft_strjoin_free(char const *s1, char const *s2);
int					get_next_line_no_eof(int fd, char **line, int b);
void				sighandler(int sig_num);

#endif
