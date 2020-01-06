# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/07 12:02:19 by sdunckel          #+#    #+#              #
#    Updated: 2019/11/23 17:41:30 by sdunckel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

SRCS_LIST	= \
				ft_atoi.c \
				ft_atof.c \
				ft_atoi_base.c \
				ft_bzero.c \
				ft_calloc.c \
				ft_check_base.c \
				ft_convert_base.c \
				ft_intlen.c \
				ft_intlen_base.c \
				ft_is_in_stri.c \
				ft_is_space.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_itoa.c \
				ft_itoa_base.c \
				ft_lstadd_back.c \
				ft_lstadd_front.c \
				ft_lstclear.c \
				ft_lstdelone.c \
				ft_lstiter.c \
				ft_lstlast.c \
				ft_lstmap.c \
				ft_lstnew.c \
				ft_lstsize.c \
				ft_memalloc.c \
				ft_memccpy.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memdel.c \
				ft_memmove.c \
				ft_memset.c \
				ft_putchar.c \
				ft_putchar_fd.c \
				ft_putendl.c \
				ft_putendl_fd.c \
				ft_putnbr.c \
				ft_putnbr_fd.c \
				ft_putstr.c \
				ft_putstr_fd.c \
				ft_split.c \
				ft_strcat.c \
				ft_strchr.c \
				ft_strcmp.c \
				ft_strcpy.c \
				ft_strdel.c \
				ft_strdup.c \
				ft_strjoin.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strmapi.c \
				ft_strncat.c \
				ft_strncmp.c \
				ft_strncpy.c \
				ft_strnew.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strstr.c \
				ft_strtrim.c \
				ft_substr.c \
				ft_tolower.c \
				ft_c_to_str.c \
				ft_toupper.c \
				ft_uitoa.c \
				ft_uintlen.c \
				get_next_line.c \
				ft_strequ.c \
				ft_ssplit.c \
				ft_str_c_count.c \
				ft_str_isdigit.c \
				ft_str_end.c \
				ft_strlen_c.c
SRCS		= $(addprefix ${FOLDER}/, ${SRCS_LIST})
OBJS		= ${SRCS:.c=.o}

HEADER		= includes
FOLDER		= srcs

FT_PRINTF 	= $(FOLDER)/ft_printf

CC			= gcc
CFLAGS 		= -Wall -Wextra -Werror
RM			= rm -f

$(NAME):	${OBJS}
			@make -C $(FT_PRINTF)
			@cp $(FT_PRINTF)/libftprintf.a ./$(NAME)
			@ar -rcs ${NAME} ${OBJS}

%.o: %.c
			@${CC} -c ${CFLAGS} -o $@ $< -I ${HEADER}

all:		${NAME}

clean:
			@${RM} ${OBJS}
			@make clean -C $(FT_PRINTF)

fclean:		clean
			@${RM} ${NAME}
			@make fclean -C $(FT_PRINTF)

re:			fclean all

.PHONY: 	all fclean clean re
