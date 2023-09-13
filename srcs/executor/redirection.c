/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 19:42:29 by marmulle          #+#    #+#             */
/*   Updated: 2023/09/13 16:36:19 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include "tokenizer.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "libft.h"

static int	get_heredoc_fd(char *content)
{
	int	tmp_pipe[2];

	if (pipe(tmp_pipe) == -1)
		action_failed("pipe");
	write(tmp_pipe[1], content, ft_strlen(content));
	close(tmp_pipe[1]);
	return (tmp_pipe[0]);
}

int	open_file(int fd_to_close, t_type type, char *file_name)
{
	int	flags;
	int	fd;

	if (fd_to_close != -2)
		close(fd_to_close);
	if (type == HEREDOC)
		return (get_heredoc_fd(file_name));
	flags = O_CREAT | O_WRONLY | O_TRUNC;
	if (type == REDIR_OUT_APPEND)
		flags = O_CREAT | O_WRONLY | O_APPEND;
	else if (type == REDIR_IN)
		flags = O_RDONLY;
	if (type == REDIR_IN && access(file_name, F_OK) == -1)
		return (print_error("file `%s` doesn't exist", file_name), -1);
	if (type == REDIR_IN && access(file_name, R_OK) == -1)
		return (print_error("can't read the file `%s`", file_name), -1);
	fd = open(file_name, flags, DEFAULT_FILE_PERMISSIONS);
	if (fd == -1)
	{
		print_error("cannot open or create the file `%s`", file_name);
		g_shell.exit_status = failure;
	}
	return (fd);
}

void	execute_redir(t_node *current)
{
	int		fd;
	bool	is_redir_in;

	if (!current)
		return ;
	is_redir_in = (current->type == REDIR_IN || current->type == HEREDOC);
	fd = -2;
	while (current)
	{
		fd = open_file(fd, current->type, current->token->data);
		if (fd == -1)
			return ;
		if (is_redir_in)
			current = current->redir_in;
		else
			current = current->redir_out;
	}
	if (is_redir_in)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
}
