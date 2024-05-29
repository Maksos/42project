# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mastie <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/07 16:22:38 by mastie            #+#    #+#              #
#    Updated: 2022/02/15 18:15:46 by mastie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_printf.c\
      ft_printf_utils.c\
      ft_unsigned.c\
      ft_hexadecimal.c\
      ft_uintptr.c\
      ft_putnbr_fd.c\

INC = ft_printf.h\
      libft/libft.h


OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Werror -Wextra

CC = gcc

CL = ar rcs

PRELIB = printf.a

NAME = libftprintf.a

RN = ranlib

RM = rm -f

LIB = libft/libft.a

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJ) $(INC)
	$(MAKE) -C libft bonus
	cp libft/libft.a $(NAME)
	$(CL) $(NAME) $(OBJ)
	$(RN) $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJ)

re: fclean all

fclean: clean
	$(MAKE) -C libft fclean
	$(RM) $(NAME)

.PHONY: all clean fclean re