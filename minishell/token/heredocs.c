/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:15:13 by mmalhada          #+#    #+#             */
/*   Updated: 2023/11/04 19:17:31 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_input_in_tmpfile(char *line, int tmpfile_fd, t_core *core)
{
	char	*expanded_line;

	expanded_line = expand_var_in_heredoc(line, core);
	if (!expanded_line)
		ft_putstr_fd(line, tmpfile_fd);
	else
	{
		ft_putstr_fd(expanded_line, tmpfile_fd);
		free(expanded_line);
	}
	ft_putstr_fd("\n", tmpfile_fd);
	free(line);
}

int	get_heredoc_input(int tmpfile_fd, char *eof_keyword, t_core *core)
{
	char	*line_from_stdin;
	int		stdin_saved;
	int		heredoc_stdin;

	heredoc_stdin = 2;
	stdin_saved = dup(STDIN_FILENO);
	if (dup2(heredoc_stdin, STDIN_FILENO) == -1)
		ft_perror_exit("Minishell ", errno, core);
	signal_activation_heredoc();
	line_from_stdin = readline(">");
	while (line_from_stdin
		&& heredoc_strncmp(line_from_stdin, eof_keyword,
			ft_strlen(eof_keyword)))
	{
		print_input_in_tmpfile(line_from_stdin, tmpfile_fd, core);
		line_from_stdin = readline(">");
	}
	free(line_from_stdin);
	if (dup2(stdin_saved, STDIN_FILENO) == -1)
		ft_perror_exit("Minishell ", errno, core);
	if (close(stdin_saved) == -1)
		ft_perror_exit("Minishell ", errno, core);
	return (0);
}

char	*create_heredoc_tmpfile(char *heredoc_counter_char, t_core *core)
{
	char	*tmpfile_name;

	tmpfile_name = ft_strjoin("/tmp/heredoc_tmpfile", heredoc_counter_char);
	if (!tmpfile_name)
	{
		free(heredoc_counter_char);
		ft_perror_exit("Minishell : ", errno, core);
	}
	free(heredoc_counter_char);
	return (tmpfile_name);
}

int	check_empty_eof(char *eof_keyword)
{
	if (ft_strncmp("\"\"", eof_keyword, 1) == 0
		|| ft_strncmp("\'\'", eof_keyword, 1) == 0)
		return (1);
	else
		return (0);
}

char	*get_heredoc_tmp_filename(char *eof_keyword, t_core *core)
{
	int		heredoc_tmpfile_fd;
	char	*heredoc_tmp_filename;
	char	*heredoc_counter_char;

	heredoc_counter_char = ft_itoa(core->heredoc_counter);
	if (!heredoc_counter_char)
		ft_perror_exit("Minishell : ", errno, core);
	heredoc_tmp_filename = create_heredoc_tmpfile(heredoc_counter_char, core);
	if (check_empty_eof(eof_keyword))
		eof_keyword = "";
	heredoc_tmpfile_fd = open(heredoc_tmp_filename,
			O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (heredoc_tmpfile_fd == -1)
		ft_perror_exit("Minishell : ", errno, core);
	core->exit_status = g_exit_status;
	g_exit_status = 0;
	get_heredoc_input(heredoc_tmpfile_fd, eof_keyword, core);
	if (close(heredoc_tmpfile_fd) == -1)
		ft_perror_exit("Minishell : ", errno, core);
	core->heredoc_counter++;
	return (heredoc_tmp_filename);
}
