/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 12:42:28 by mastie            #+#    #+#             */
/*   Updated: 2023/11/06 18:20:49 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/syscall.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <errno.h>
# include <stdbool.h>

# ifndef _GNU_SOURCE
#  define _GNU_SOURCE
# endif

/*	ls -la "args"	(		)		&&	||	<	 <<		>		>>		|
	 WORD, 			LBRAC, RBRAC, AND, OR, LESS, DLESS, GREAT, DGREAT, PIPE
		0			1		2		3	4	5		6	7		8		9

	INPUT LINES FOR TEST

		!! LEAK SEGFAULT !!

		make && valgrind ./minishell

		Quotes

		Parentheses

		Parser

		Builtins

		Redirections

*/

typedef enum e_token_id
{
	WORD = 0,
	PAREN,
	RPAREN,
	AND,
	OR,
	LESS,
	DLESS,
	GREAT,
	DGREAT,
	PIPE,
}			t_token_id;

typedef struct s_token
{
	char		*verbose;
	t_token_id	id;

}				t_token;

typedef struct s_exec
{
	char	*cmd;
	char	**args;
	char	**executables;
	char	*cmd_path;

}			t_execs;

typedef struct s_outfiles
{
	char	*filename;
	int		open_flag;
}				t_outfiles;

typedef struct s_std_fds
{
	int		original_stdin;
	int		original_stdout;
	int		new_stdin;
	int		new_stdout;
}				t_std_fds;

typedef struct s_redirections
{
	t_list		*infiles;
	t_list		*outfiles;
}				t_redirections;

typedef struct s_content
{
	t_list			*arguments;
	t_redirections	*redirections;
	t_std_fds		*std_fds;
}				t_content;

typedef struct s_cmd
{
	t_content		*data;
	struct s_cmd	*and;
	struct s_cmd	*or;
	struct s_cmd	*pipes;
	struct s_cmd	*parenthesis;

}				t_cmd;

typedef struct s_parenthe
{
	int			added_in_position;
	int			position;

}				t_parenthes;

typedef struct s_parenthesis
{
	int			lparen;
	int			rparen;

}				t_parenthesis;

typedef struct s_wildcards
{
	int			position;

}				t_wildcards;

typedef struct s_booleans
{
	bool	hidden_files;
	bool	star_at_the_end;
	bool	star_at_the_start;
}			t_booleans;

typedef struct s_wldcard
{
	t_booleans	booleans;
	t_list		*files_lst;
	char		*pattern;

}			t_wldcard;

typedef struct s_pipe
{
	t_content	*data;
	pid_t		fork_id;
	int			exit_status;

}			t_pipes;

typedef struct s_char_and_tlist
{
	char	*str;
	t_list	**tlst;

}			t_char_and_tlist;

typedef struct s_tmp_tlist
{
	t_list	*current;
	t_list	*previous;
	t_list	*next;
	t_list	*files_from_wildcard;
	t_list	*wildcard_index;

}			t_tmp_tlist;

typedef struct s_core
{
	char		**env;
	char		*input;
	int			exit_status;
	int			heredoc_counter;
	int			arg_has_quotes;
	int			empty_str_removed;

	t_list		*token_list;
	t_cmd		*head;
	t_cmd		*current;
	t_content	*current_data;
	t_list		*current_parenthesis;
	t_cmd		*parenthesis_parent;
	t_list		*rparenthesis;
	t_list		*lparenthesis;
	t_token		**token_operator;

}				t_core;

extern int		g_exit_status;

/* STRUCT PARTS */
t_cmd			*new_t_cmd(void);
t_content		*new_t_content(void);
t_outfiles		*new_t_outfiles(t_token_id id, char *verbose, t_core *core);
t_outfiles		*new_heredoc_t_outfiles(char *verbose);
t_redirections	*new_t_redirections(void);
t_parenthes		*new_t_parenthes(int input_position, int position);
t_parenthesis	*new_t_parenthesis(int lparenthesis, int rparenthesis);
t_wildcards		*new_t_wildcards(int position);

/* INIT PARTS */
void			tty_ready(void);
void			init_token_operator(t_core *core);
void			init_globals(t_core *core);

/*	SIGNAL PARTS */
void			signal_activation(void);
void			signal_activation_heredoc(void);
void			signal_activation_child(void);
void			signal_ignore(void);
void			signal_default(void);

/* INPUT CONTROL */
void			input_control(t_core *core);
void			reset(t_core *core);

/*QUOTES AND DQUOTES CHECKER */
int				quotes_and_dquotes(t_core *core);

/* PARENTHESIS CHERCKER */
int				parenthesis(t_core *core);
void			checking_parenthesis(t_core *core);

/* LEXER PARTS */
void			lexer(t_core *core);
int				go_to_char(int i, t_core *core);
char			**ft_split_words(char const *s);
int				go_to_char_split(const char *s, int i);
char			*extract_line_token(char const *s, int start);
int				quotes_removal(t_token *current);
int				replace_dollars(t_token *current);
int				dollar_checker(char *str);
void			check_replace_remove(t_list *current, t_list **wildcard_index,
					t_core *core);
int				check_replace_remove_redirections(t_outfiles *current,
					t_list **wildcard_index, t_core *core);
int				check(char *str);
int				replace(char *str);
void			add_position_to_wildcards(char *str, t_list **tmp,
					t_list **wildcard_index);
int				move_to_words(int i, t_core *core);
int				not_words(int i, t_core *core);
int				is_space(char c);
int				is_spaced(char c);

/*	TOKEN CMP PARTS */
int				struct_to_ast(t_token *last_added, t_token *current,
					t_core *core);
int				or(t_token *last_added, t_token *current, t_core *core);
int				and(t_token *last_added, t_token *current, t_core *core);
int				pipes(t_token *last_added, t_token *current, t_core *core);
int				dless(t_token *last_added, t_token *current, t_core *core);
int				dgreat(t_token *last_added, t_token *current, t_core *core);
int				great(t_token *last_added, t_token *current, t_core *core);
int				less(t_token *last_added, t_token *current, t_core *core);
int				lparen(t_token *last_added, t_token *current, t_core *core);
int				rparen(t_token *last_added, t_token *current, t_core *core);
int				words(t_token *last_added, t_token *current, t_core *core);

/* QUOTES PARTS */
int				remove_q(char *str);
int				remove_quote_dquotes(t_char_and_tlist tmp, t_list **wildcards,
					t_core *core);
void			adjust_tmp(int i, char *str, t_list **tmp_str, t_core *core);

/* DOLLARS PARTS */
int				replace_dollar(t_char_and_tlist tmp, t_list **wildcards,
					t_core *core);
int				replace_dollar_at(t_char_and_tlist tmp, int i, int in_q,
					t_core *core);
int				remove_replace_dollar(t_char_and_tlist tmp, int i,
					t_core *core);
char			*extract_name(char *str, int start, int lenght);
int				sep_dollar(char c, char *ref);
int				dollar_name_length(char *str, int i);
int				heredoc_strncmp(const char *s1, const char *s2, size_t n);
char			*expand_var_in_heredoc(char *line, t_core *core);
int				get_length_expanded_line(char *line, t_core *core);
char			*get_var_name(char *line, int length, t_core *core);
int				check_replace_dollar_space(t_list *current, t_list *expand);
void			replace_space_by_args(t_list *current,
					t_list *expand, t_core *core);

/*	PARSE PARTS */
int				parser(t_core *core);

/* AST PARTS */
int				struct_to_ast_by_words(t_token *last_added, t_token *current,
					t_core *core);
int				struct_to_ast_by_redirections(t_core *core);
int				struct_to_ast_by_and_or(t_token *current, t_core *core);
int				struct_to_ast_by_pipe(t_core *core);
int				struct_to_ast_by_lparen(t_core *core);
int				struct_to_ast_by_rparen(t_core *core);

/* AST PRINTER */
void			ast_printer(t_core *core);

/* EXEC PARTS */
void			exec(t_core *core);
int				recursive_exec(t_cmd *current, t_core *core);
int				exec_node_pipe(t_cmd *current, t_core *core);
void			exec_node_and(t_cmd *current, t_core *core);
void			exec_node_or(t_cmd *current, t_core *core);
void			exec_cmd(t_content *data, t_core *core);
int				exec_ast_node(t_content *data, t_core *core);
void			ft_close_fds(int fd_pipe[2]);
int				ambiguous_redirection(t_outfiles *outfile);
void			check_exec_error(char *cmd_path);
int				is_cmd_absolute_path(char *executable);
char			**extract_path(char **env);
char			**extract_args(t_list *cmd_args);
int				get_cmd_args_and_path(t_list *cmd_args, t_execs *exec,
					t_core *core);
void			expand_arguments(t_content *data, t_core *core);
int				expand_ast_node(t_content *data, t_core *core);
void			init_t_exec(t_execs *exec);
int				redirections_error_handler(t_core *core, t_execs exec);
int				execve_error_handler(t_core *core, t_execs exec);
void			free_exec(t_execs exec);

/* WILDCARDS PARTS */
bool			is_star_interpreted(int index, t_list *wildcard_index);
bool			check_hidden_files(char *pattern);
bool			check_star_at_the_start(char *pattern, t_list *wildcard_index);
bool			check_star_at_the_end(char *pattern, t_list *wildcard_index);
t_list			*search_files_matching_pattern(t_wldcard wildcard_core,
					t_list *wildcard_index, t_core *core);
t_list			*copy_files_matching(t_list *files_lst, t_list *patterns_lst,
					t_booleans booleans);
t_list			*get_files_with_wildcard(char *pattern, char *path_dir,
					t_list *wildcard_index, t_core *core);
void			print_lst(t_list *files_lst);

/*	REDIRECTIONS PARTS */
int				handle_redirections(t_content *data, t_core *core);
int				handle_redirections_and_store_standard_fds(t_content *data,
					t_core *core);
char			*get_heredoc_tmp_filename(char *eof_keyword, t_core *core);
void			flush_fds(t_std_fds *std_fds, t_core *core);
int				redirecting(t_content *data, t_core *core);

/*	BUILTINS PARTS */
int				ft_cd(t_content *data, t_core *core);
int				ft_env(t_content *data, t_core *core);
int				ft_pwd(t_content *data, t_core *core);
int				ft_echo(t_content *data);
int				ft_export(t_content *data, t_core *core);
int				ft_unset(t_content *data, t_core *core);
void			ft_exit(t_content *data, t_core *core);

/* BUILTIN TOOLS */
int				set_pwd(t_core *core);
int				str_cmp(char *haystack, char *needle);
int				exist_in_env(char *str, t_core *core);
char			**t_list_to_strings(t_list *tmp_env);
int				is_a_builtin(char *cmd);
int				builtins_call(t_content *data, t_core *core);
char			*get_env(char *str, t_core *core);
int				go_to_new_path(char	*path_to_go, t_core *core);
int				add_new_path_in_env(char *str, t_core *core, int f);

/* BUILTIN EXPORT TOOLS */
int				free_replace_check(char *str, int i, t_core *core);
int				valid_input_export(t_list *from);
int				option_error(char *str);
void			error_print(char *str);
int				sequence_check_equal(char *str, char *check);
char			*extract_name_for_export(char *str);
char			*crop_plus_in_str(char *str);
char			*join_and_add(char *p1, char *p2, char *p3);
char			*rest_from_plus_export(char *str);
int				print_env_export(t_core *core);

/* MEM CHECK PARTS */
void			mem_list_chars(t_list **list, void *content, t_core *core);
void			mem_list_wildcards(t_list **list, t_list *content,
					t_core *core);

/* 	FREE PARTS */
void			free_cmd(t_cmd *command);
void			free_chars(char **chars);
void			free_t_list(t_list *list, int free_content);
void			free_token(void *content);
void			free_arguments(void *content);
void			free_token_operator(t_core *core);
void			free_content(t_content *data);
void			free_redirections(t_content *data);

/* ERRORS HANDLING */
void			ft_error_exit(char *to_print, int exiting, t_core *core);
void			ft_perror_exit(char *to_print, int exiting, t_core *core);

#endif
