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

CFLAGS = -Wall -Werror -Wextra

SRC = main.c\
	parser.c\
	insert.c\
	rotate.c\
	solver.c\
	solver_3.c\
	solver_5.c\
	sequence_of_solver.c\
	operations.c\
	sequence_of_operations.c\
	rrr_rr.c\
	free.c

OBJ = ${SRC:.c=.o}

LIB = ft_printf/libftprintf.a

CC = cc

RM = rm -f

NAME = push_swap

PRINTF = $(MAKE) -sC ft_printf

MAKEFLAGS += --no-print-directory

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJ)
	$(PRINTF)
	${CC} ${CFLAGS} ${OBJ} -Lft_printf ft_printf/libftprintf.a -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(MAKE) -sC ft_printf fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
