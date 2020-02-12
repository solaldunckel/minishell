/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 11:17:02 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/11 15:44:16 by haguerni         ###   ########.fr       */
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
# define T_REDIRECT 2
# define T_PIPE 3
# define T_SEP 4
# define T_NEWLINE 5

typedef struct		s_minishell
{
	char			*name;
	char			*curdir;
	int				exit;
	char			*line;
	int				quit;
	int				count;
	int				out;
	int				in;
	struct s_cmd	*cmd_list;
	t_list			*env_list;
	t_list			*sort_env_list;
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

	struct s_token	*args;
	char			**args_array;
	int				pipe[2];
	int				pipeprev[2];
	int				in;
	int				out;
	int				type;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}					t_cmd;

typedef struct		s_token
{
	char				*word;
	int					type;
	struct s_token		*prev;
	struct s_token		*next;
}					t_token;

t_minishell			*g_minishell;

// ENV
void				env_init(t_minishell *minishell, char **env);
t_env				*create_env(char **split);
char				*get_env(t_minishell *minishell, char *env);
char				*replace_env(t_minishell *minishell, char *line);
char				**env_to_array(t_minishell *minishell);

// BIN
void				parse_bin(t_minishell *minishell);
char				*get_bin(t_minishell *minishell, char *cmd);

// BUILTIN

void				echo_cmd(t_minishell *minishell, t_cmd *cmd);
void				cd_cmd(t_minishell *minishell, t_cmd *cmd);
void				exit_cmd(void);
void				env_cmd(t_list **begin);
void				pwd_cmd(t_minishell *minishell);
void				export_cmd(t_minishell *minishell, t_cmd *cmd);
void				unset_cmd(t_minishell *minishell, t_cmd *cmd);

// PARSING
void				start_parse(t_minishell *minishell, char *str);
char				*supp_newline(char *src);

// BRACKET

int					bracket_odd(char *s);
void				next_bracket(t_minishell *minishell);

// TOKEN
t_token				*create_token(t_minishell *minishell, int i);
t_token				*create_arg_token(char *word);
void				token_remove_last(t_token **begin_list);
void				clear_token_list(t_token **begin, void (*del)(void *));
void				add_token_list(t_token **begin, t_token *new);
int					size_token_list(t_token **begin);

// CMD
void				add_cmd_list(t_cmd **begin, t_cmd *new);
void				clear_cmd_list(t_cmd **begin, void (*del)(void *));

// UTILS
char				*ft_strndup(const char *s1, int n);
char				**ft_split_brackets(char const *s, char *set);
void				free_cmd(void *cmd);
char				**free_split(char **split);
int					count_split(char **split);
char				*ft_strjoin_free(char const *s1, char const *s2);
int					get_next_line_no_eof(int fd, char **line, int b);
void				sighandler(int sig_num);
int					is_escaped(char *s, int pos);
void				exec_prog(t_minishell *minishell, t_cmd *tmp, int f_pipe[2],
					int f_pipe2[2]);
void				handle_errors(t_minishell *minishell, char *cmd, int type);
void				handle_errno(t_minishell *minishell, char *cmd, int type);

#endif
