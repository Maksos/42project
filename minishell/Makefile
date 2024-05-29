# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/29 12:23:07 by mastie            #+#    #+#              #
#    Updated: 2023/11/06 18:21:20 by mmalhada         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Werror -Wextra

WILDCARDS = wildcards/checks.c\
			wildcards/copy_files_matching.c\
			wildcards/wildcards.c\
			wildcards/wildcards2.c\

LEXER = lexer/lexer.c\
		lexer/lexer_tools.c\
		lexer/split_words_token.c\
		lexer/split_words_token_tools.c\
		lexer/quotes.c\
		lexer/check_replace_remove.c\
		lexer/check_replace_remove_redirections.c\

DOLLAR = dollar/dollar.c\
			dollar/dollar_in_heredocs.c\
			dollar/dollar_tools.c\
			dollar/space_in_expanded_dollar.c\

PARENTHESIS = parenthesis/parenthesis.c\
				parenthesis/parenthesis_tools.c\

PARSER = parser/parser.c\
			parser/struct.c\
			parser/struct_parenthesis.c\
			parser/struct_to_ast.c\
			parser/struct_to_ast_by_words.c\
			parser/struct_to_ast_by_parenthesis.c\
			parser/struct_to_ast_by_operators.c\
			parser/struct_to_ast_by_redirections.c\

BUILTINS = builtins/cd.c\
			builtins/cd_tools.c\
			builtins/get_env.c\
			builtins/echo.c\
			builtins/env.c\
			builtins/export.c\
			builtins/ft_export_working.c\
			builtins/export_tools.c\
			builtins/unset.c\
			builtins/pwd.c\
			builtins/exit.c\
			builtins/builtins_tools.c\

TOKEN = token/token.c\
		token/heredocs.c\
		token/heredocs_utils.c\
		token/token_redirection.c\
		token/token_operator.c\
		token/token_parenthesis.c\

SIGNAL = signal/signal.c\
			signal/signal_heredoc.c\

FREE = free/free.c\
		free/free_others.c\

INIT = init/main.c\
		init/init.c\
		init/init_tools.c\

EXEC = exec/exec.c\
		exec/exec_cmd.c\
		exec/exec_cmd2.c\
		exec/exec_pipe.c\
		exec/exec_and.c\
		exec/redirections.c\
		exec/redirections2.c\
		exec/exec_utils.c\
		exec/exec_builtins.c\
		exec/expand_ast_node.c\
		exec/expand_arguments.c\
		exec/free_in_exec.c\

ERROR = error/error.c\
			error/mem_alloc_check.c\

SRC = $(INIT)\
	$(SIGNAL)\
	$(TOKEN)\
	$(DOLLAR)\
	$(PARENTHESIS)\
	$(LEXER)\
	$(PARSER)\
	$(EXEC)\
	$(BUILTINS)\
	$(FREE)\
	$(WILDCARDS)\
	$(ERROR)

OBJ = ${SRC:.c=.o}

LIB = libft/libft.a

CC = cc

RM = rm -f

NAME = minishell

LIBFT = $(MAKE) -sC libft

MAKEFLAGS += --no-print-directory

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJ)
	$(LIBFT)
	${CC} ${CFLAGS} ${OBJ} -Llibft -lreadline libft/libft.a -o $(NAME)

all: $(NAME)

clean:
	$(MAKE) -sC libft clean
	$(RM) $(OBJ)

fclean: clean
	$(MAKE) -sC libft fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
