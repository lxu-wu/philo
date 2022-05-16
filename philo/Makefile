# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/12 19:27:48 by lxu-wu            #+#    #+#              #
#    Updated: 2022/05/12 19:27:48 by lxu-wu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = action.c free.c main.c utils.c init.c

OBJS = ${SRCS:.c=.o}

CC = gcc

RM = rm -rf

CFLAGS = -Werror -Wextra -Wall

all:	${NAME}

$(NAME): ${OBJS}
		${CC} ${CFLAGS} ${OBJS} -o ${NAME}
		${clean}

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}

re:		fclean all

.PHONY:	all clean fclean re bonus