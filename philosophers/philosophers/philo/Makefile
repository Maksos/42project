# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mastie <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/29 12:23:07 by mastie            #+#    #+#              #
#    Updated: 2022/11/23 17:19:48 by mastie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Werror -Wextra -fsanitize=thread -g3

SRC = main.c\
	control.c\
	simulation.c\
	thread.c\
	status.c\
	lock.c\
	eat.c\
	sleep.c\
	think.c\
	time.c\
	free.c

OBJ = ${SRC:.c=.o}

LIB = ft_printf/libftprintf.a

CC = cc

RM = rm -f

NAME = philo

PRINTF = $(MAKE) -sC ft_printf

MAKEFLAGS += --no-print-directory

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJ)
	$(PRINTF)
	${CC} ${CFLAGS} ${OBJ} -Lft_printf -pthread ft_printf/libftprintf.a -o $(NAME)

all: $(NAME)

clean:
	$(MAKE) -sC ft_printf clean
	$(RM) $(OBJ)

fclean: clean
	$(MAKE) -sC ft_printf fclean
	$(RM) $(NAME)

re_sub:
	$(MAKE) -sC ft_printf re

re: fclean re_sub all

.PHONY: all clean fclean re re_sub
