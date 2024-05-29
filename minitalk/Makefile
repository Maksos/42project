# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mastie <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/29 12:23:07 by mastie            #+#    #+#              #
#    Updated: 2022/10/22 19:13:30 by mastie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Werror -Wextra

SERVERSRC = server.c\

CLIENTSRC = client.c\
		input.c

SERVERSRCB = server_bonus.c\

CLIENTSRCB = client_bonus.c\
		input_bonus.c

INC = minitalk.h

OBJS = ${SERVERSRC:.c=.o}

OBJC = ${CLIENTSRC:.c=.o}

OBJSB = ${SERVERSRCB:.c=.o}

OBJCB = ${CLIENTSRCB:.c=.o}

LIB = ft_printf/libftprintf.a

CC = gcc 

RM = rm -f

NAME = name

MAKEFLAGS += --no-print-directory

name: server client

bonus: serverb clientb

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

server: ${OBJS} 
		$(MAKE) -sC ft_printf
		${CC} ${CFLAGS} ${OBJS} -Lft_printf ${LIB} -o server

client: ${OBJC}
		$(MAKE) -sC ft_printf
		${CC} ${CFLAGS} ${OBJC} -Lft_printf ${LIB} -o client

serverb: ${OBJSB}
		$(MAKE) -sC ft_printf
		${CC} ${CFLAGS} ${OBJSB} -Lft_printf ${LIB} -o serverb

clientb: ${OBJCB}
		$(MAKE) -sC ft_printf
		${CC} ${CFLAGS} ${OBJCB} -Lft_printf ${LIB} -o clientb

all: $(NAME)

clean:
	$(RM) $(OBJS) $(OBJC)

cleanb:
	$(RM) $(OBJSB) $(OBJCB)

fclean: clean
	$(MAKE) -sC ft_printf fclean
	$(RM) server
	${RM} client

fcleanb: cleanb
	$(MAKE) -sC ft_printf fclean
	$(RM) serverb
	$(RM) clientb

re: fclean all


.PHONY: all clean fclean re bonus name
