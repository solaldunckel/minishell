/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 03:50:22 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/28 00:47:33 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMCAPS_H
# define TERMCAPS_H

# include "minishell.h"
# include <curses.h>
# include <term.h>
# include <sys/ioctl.h>
# include <termios.h>

# define BACKSPACE 127
# define EOF_KEY 4
# define LEFT_ARROW 4479771
# define RIGHT_ARROW 4414235
# define UP_ARROW 4283163
# define DOWN_ARROW 4348699

# define HOME 4741915
# define END 4610843

# define ALT_X 8948194
# define ALT_C 42947
# define ALT_V 10127586

# define CTRL_LEFT 74995417045787
# define CTRL_RIGHT 73895905418011
# define CTRL_UP 71696882162459
# define CTRL_DOWN 72796393790235

typedef struct		s_hist
{
	char			*cmd;
	struct s_hist	*prev;
	struct s_hist	*next;
}					t_hist;

typedef struct		s_termcap
{
	struct termios	term;
	struct termios	term_backup;
	t_hist			*history;
	t_hist			*cur_history;
	char			*backup_cmd;
	char			*copy_cmd;
	int				cur_col;
	int				cur_row;
	int				start_row;
	int				col;
	int				row;
	int				plen;
	int				cur_pos;
	int				currow;
	int				lenlen;
	int				rowoffset;
	int				curcol;
	int				mod_offset;
	int				endcol;
	int				endrow;
	char			*dc; // delete char
	char			*cm; // cursor move
	char			*ce; // clear end
	char			*cd; // clear line full
	char			*kb; // backspace
	char			*kl; // left
	char			*kr; // right
	char			*ku; // up
	char			*kd; // down
}					t_termcap;

t_termcap			*g_tc;

void	add_cmd_to_history(char *cmd);
void	add_history_list(t_hist **begin, t_hist *new);

int		putchar_tc(int tc);

void	move_cursor_left(void);
void	move_cursor_right(void);
void	move_cursor_begin(void);
void	move_cursor_end(void);

void	move_prev_word(void);
void	move_next_word(void);

void	move_prev_line(void);
void	move_next_line(void);

void	up_history(void);
void	down_history(void);

void	cut_line(void);
void	copy_line(void);
void	paste_line(void);

/*
** UTILS
*/

int       		 	termcaps_loop(void);
void				init_term();
void				init_tc();
void     			cursor_win();
void				get_cursor_position(int *col, int *rows);
char				*ft_strjoin_middle(char *s1, const char *s2, int div);

#endif
