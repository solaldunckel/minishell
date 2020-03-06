# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/07 12:02:19 by sdunckel          #+#    #+#              #
#    Updated: 2020/03/06 16:04:23 by sdunckel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

SRCS_LIST		= \
					main.c \
					\
					env/env_utils.c \
					env/env_utils2.c \
					\
					parsing/token.c \
					parsing/token2.c \
					parsing/cmds.c \
					parsing/bin_path.c \
					parsing/parsing_token.c \
					parsing/parsing_cmds.c \
					\
					commands/echo.c \
					commands/cd.c \
					commands/exit.c \
					commands/env.c \
					commands/pwd.c \
					commands/unset.c \
					commands/export.c \
					\
					utils/redirect.c \
					utils/command_process.c \
					utils/command_process2.c \
					utils/free_utils.c \
					utils/utils.c \
					utils/utils2.c \
					utils/quotes.c \
					utils/gnl_no_eof.c\
					utils/exec.c \
					utils/signals.c \
					utils/errors.c \

SRCS_LIST_BONUS	= \
					main_bonus.c \
					\
					env/env_utils.c \
					env/env_utils2.c \
					\
					parsing/token.c \
					parsing/token2.c \
					parsing/cmds.c \
					parsing/bin_path.c \
					parsing/parsing_token_bonus.c \
					parsing/parsing_cmds_bonus.c \
					\
					commands/echo.c \
					commands/cd.c \
					commands/exit.c \
					commands/env.c \
					commands/pwd.c \
					commands/unset.c \
					commands/export.c \
					\
					parsing/wildcard_bonus.c \
					\
					utils/redirect_bonus.c \
					utils/command_process.c \
					utils/command_process2_bonus.c \
					utils/free_utils.c \
					utils/utils.c \
					utils/utils2.c \
					utils/quotes.c \
					utils/gnl_no_eof.c\
					utils/exec.c \
					utils/signals_bonus.c \
					utils/errors.c \
					utils/subshell_bonus.c \
					utils/wait_commmand_bonus.c \
					\
					termcaps/cursor.c \
					termcaps/move_word.c \
					termcaps/move_line.c \
					termcaps/history.c \
					termcaps/init.c \
					termcaps/loop.c \
					termcaps/utils.c \
					termcaps/string_manip.c

SRCS_FOLDER		= srcs

SRCS			= $(addprefix ${SRCS_FOLDER}/, ${SRCS_LIST})
OBJS			= ${SRCS:.c=.o}

SRCS_BONUS		= $(addprefix ${SRCS_FOLDER}/, ${SRCS_LIST_BONUS})
OBJS_BONUS		= ${SRCS_BONUS:.c=.o}

HEADER			= includes

LIBFT 			= libft

CC				= gcc
CFLAGS 			= -Wall -Wextra -Werror
LFLAGS			= -L libft -lft -lncurses

RM				= rm -f

all:			$(NAME)

$(NAME):		$(OBJS)
				@make -s -j -C $(LIBFT)
				@$(CC) $(CFLAGS) $(LFLAGS) -I $(HEADER) $(OBJS) -o $(NAME)

%.o: %.c
				@$(CC) $(CFLAGS) -I $(HEADER) -o $@ -c $<

bonus:			$(OBJS_BONUS)
				@make -s -j -C $(LIBFT)
				@$(CC) $(CFLAGS) $(LFLAGS) -I $(HEADER) $(OBJS_BONUS) -o $(NAME)

clean:
				@$(RM) $(OBJS) $(OBJS_BONUS)
				@make clean -C $(LIBFT)

fclean:			clean
				@$(RM) $(NAME)
				@make fclean -C $(LIBFT)

re:				fclean
				@make -j

.PHONY: 		all fclean clean re bonus
