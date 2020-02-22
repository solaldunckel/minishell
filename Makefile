# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/07 12:02:19 by sdunckel          #+#    #+#              #
#    Updated: 2020/02/22 04:34:45 by sdunckel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

SRCS_LIST		= \
					main.c \
					\
					env/env_utils.c \
					\
					parsing/token.c \
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
					utils/exec.c\
					utils/errors.c\

SRCS_FOLDER		= srcs
SRCS			= $(addprefix ${SRCS_FOLDER}/, ${SRCS_LIST})
OBJS			= ${SRCS:.c=.o}

HEADER			= includes

LIBFT 			= libft

CC				= gcc
CFLAGS 			= -Wall -Wextra -Werror
LFLAGS			= -L libft -lft

RM				= rm -f

BONUS			= 0

all:			$(NAME)

$(NAME):		$(OBJS)
				@make -s -C $(LIBFT)
				@$(CC) $(CFLAGS) $(LFLAGS) -I $(HEADER) $(OBJS) -o $(NAME)

%.o: %.c
				@$(CC) $(CFLAGS) -D BONUS=$(BONUS) -I $(HEADER) -o $@ -c $<

bonus:
				@$(RM) $(OBJS)
				@make BONUS=1

clean:
				@$(RM) $(OBJS)
				@make clean -C $(LIBFT)

fclean:			clean
				@$(RM) $(NAME)
				@make fclean -C $(LIBFT)

re:				fclean all

real:			re
				./minishell

.PHONY: 		all fclean clean re bonus
