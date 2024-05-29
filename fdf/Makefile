# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mastie <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/29 12:23:07 by mastie            #+#    #+#              #
#    Updated: 2022/12/06 22:44:12 by mastie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Werror -Wextra

SRC = main.c\
	parser.c\
	parser_int_color.c\
	parser_int_color_utils.c\
	draw.c\
	draw_utils.c\
	rotate_perimeter.c\
	hook.c\
	keys_arrows.c\
	keys_views.c\
	keys_less.c\
	keys_plus.c\
	rotation.c\
	free.c\
	utils.c

SRCB = main_bonus.c\
	parser_bonus.c\
	parser_int_color_bonus.c\
	parser_int_color_utils_bonus.c\
	draw_bonus.c\
	draw_utils_bonus.c\
	rotate_perimeter_bonus.c\
	hook_bonus.c\
	keys_arrows_bonus.c\
	keys_views_bonus.c\
	keys_less_bonus.c\
	keys_plus_bonus.c\
	rotation_bonus.c\
	free_bonus.c\
	utils_bonus.c

OBJ = ${SRC:.c=.o}

OBJB = ${SRCB:.c=.o}

CC = gcc

RM = rm -f

INC = fdf.h

INCB = fdf_bonus.h

NAME = fdf

PRINTF = $(MAKE) -sC ft_printf

MINILIBX = $(MAKE) -sC mlx

LIBS = -Lft_printf -Lmlx -lmlx -Imlx -lXext -lX11 -lm -lz mlx/libmlx_Linux.a ft_printf/libftprintf.a

MAKEFLAGS += --no-print-directory --quiet

BONUS = fdf_bonus

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJ)
	$(MINILIBX)
	$(PRINTF)
	${CC} ${OBJ} ${INC} ${CFLAGS} ${LIBS} -o $(NAME)

$(BONUS): $(OBJB)
	$(MINILIBX)
	$(PRINTF)
	${CC} ${OBJB} ${INCB} ${CFLAGS} ${LIBS} -o $(BONUS)

all: $(NAME)

bonus: $(BONUS)

bclean:
	$(RM) $(OBJB)

bfclean: bclean
	$(MAKE) -sC ft_printf fclean
	$(MAKE) -sC mlx clean
	$(RM) $(BONUS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(MAKE) -sC ft_printf fclean
	$(MAKE) -sC mlx clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus bclean bfclean
