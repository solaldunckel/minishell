# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/07 12:02:19 by sdunckel          #+#    #+#              #
#    Updated: 2020/02/05 17:20:33 by sdunckel         ###   ########.fr        #
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
					parsing/parsing.c \
					parsing/bin_path.c \
					\
					utils/utils.c \
					utils/quotes.c \
					utils/gnl_no_eof.c

SRCS_FOLDER		= srcs
SRCS			= $(addprefix ${SRCS_FOLDER}/, ${SRCS_LIST})
OBJS			= ${SRCS:.c=.o}

HEADER			= includes

LIBFT 			= libft

CC				= gcc
CFLAGS 			= # -Wall -Wextra -Werror
LFLAGS			= -L libft -lft

RM				= rm -f

all:			$(NAME)

$(NAME):		$(OBJS)
				@make -s -C $(LIBFT)
				@$(CC) $(CFLAGS) $(LFLAGS) -I $(HEADER) $(OBJS) -o $(NAME)

%.o: %.c
				@$(CC) $(CFLAGS) -I $(HEADER) -o $@ -c $<

clean:
				@$(RM) $(OBJS)
				@make clean -C $(LIBFT)

fclean:			clean
				@$(RM) $(NAME)
				@make fclean -C $(LIBFT)

re:				fclean all

.PHONY: 		all fclean clean re
