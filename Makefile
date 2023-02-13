# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/25 16:29:22 by tbarbe            #+#    #+#              #
#    Updated: 2022/07/25 18:21:31 by tbarbe           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= synth

SRCS	= 	srcs/*.c \
			utils/pcm_utils/*.c \
			utils/list_utils/*.c \
			utils/str_utils/*.c \
			utils/gnl_utils/*.c

HEADERS	= includes

CC		= gcc

RM		= rm -f

CFLAGS	= -Wextra -Wall -Werror -lasound -lm -pthread -g

${NAME}:	${OBJS}
						gcc -o ${NAME} -I ${HEADERS} ${SRCS} ${CFLAGS}

all:		${NAME}

fclean:
						${RM} $(NAME)

re:						fclean all

.PHONY:		all fclean re
