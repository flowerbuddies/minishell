/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 19:42:29 by marmulle          #+#    #+#             */
/*   Updated: 2023/09/15 15:55:46 by marmulle         ###   ########.fr       */
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

static bool	check_access(t_type type, char *file_name)
{
	if (type == REDIR_IN && access(file_name, F_OK) == -1)
	{
		print_error("this file doesn't exist", file_name);
		get_shell()->exit_status = failure;
		return (true);
	}
	if (type == REDIR_IN && access(file_name, R_OK) == -1)
	{
		print_error("this file is not working", file_name);
		get_shell()->exit_status = failure;
		return (true);
	}
	return (false);
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
	if (check_access(type, file_name))
		return (-1);
	fd = open(file_name, flags, DEFAULT_FILE_PERMISSIONS);
	if (fd == -1)
	{
		print_error("this file cannot be opened or created", file_name);
		get_shell()->exit_status = failure;
	}
	return (fd);
}

bool	execute_redir(t_token *current)
{
	int	fd_in;
	int	fd_out;

	if (!current)
		return (true);
	fd_in = -2;
	fd_out = -2;
	while (current)
	{
		if (current->type == REDIR_IN || current->type == HEREDOC)
			fd_in = open_file(fd_in, current->type, current->data);
		else
			fd_out = open_file(fd_out, current->type, current->data);
		if (fd_in == -1 || fd_out == -1)
			return (false);
		if (!current->next)
			break ;
		current = current->next;
	}
	if (fd_in != -2)
		(dup2(fd_in, STDIN_FILENO), close(fd_in));
	if (fd_out != -2)
		(dup2(fd_out, STDOUT_FILENO), close(fd_out));
	return (true);
}
