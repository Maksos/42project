# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mastie <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/29 12:23:07 by mastie            #+#    #+#              #
#    Updated: 2022/10/19 17:25:43 by mastie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS = ft_atoi.c\
			ft_bzero.c\
			ft_calloc.c\
			ft_isalnum.c\
			ft_isalpha.c\
			ft_isascii.c\
			ft_isdigit.c\
			ft_isprint.c\
			ft_isprint.c\
			ft_itoa.c\
			ft_memchr.c\
			ft_memcmp.c\
			ft_memcpy.c\
			ft_memmove.c\
			ft_memset.c\
			ft_putchar_fd.c\
			ft_putendl_fd.c\
			ft_putnbr_fd.c\
			ft_putstr_fd.c\
			ft_split.c\
			ft_strchr.c\
			ft_strdup.c\
			ft_striteri.c\
			ft_strjoin.c\
			ft_strlcat.c\
			ft_strlcpy.c\
			ft_strlen.c\
			ft_strmapi.c\
			ft_strncmp.c\
			ft_strnstr.c\
			ft_strrchr.c\
			ft_strtrim.c\
			ft_substr.c\
			ft_tolower.c\
			ft_toupper.c\
			ft_lstnew.c\
	   		ft_lstadd_front.c\
	   		ft_lstsize.c\
	   		ft_lstlast.c\
	   		ft_lstadd_back.c\
	   		ft_lstdelone.c\
	   		ft_lstclear.c\
	  	 	ft_lstiter.c\
	   		ft_lstmap.c\
			get_next_line.c\
			get_next_line_utils.c

CFLAGS = -Wall -Werror -Wextra

OBJS = ${SRCS:.c=.o}

CC = cc

CL = ar rcs

NAME = libft.a

RM = rm -f

RN = ranlib

INC = libft.h

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): ${OBJS} ${INC}
	$(CL) $(NAME) $(OBJS)
	$(RN) $(NAME)

all: ${NAME}

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
