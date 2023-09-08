/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 19:42:29 by marmulle          #+#    #+#             */
/*   Updated: 2023/09/08 18:52:14 by hunam            ###   ########.fr       */
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

// for this special case: `cat << end < test.c`
// when a redir_in is chained after a heredoc
static t_type	get_type(t_node *current)
{
	if (current->parent->type == HEREDOC)
		return (HEREDOC);
	return (current->type);
}

void	execute_redir_out(t_node *node)
{
	t_node	*current;
	int		fd;
	bool	is_first;

	current = node;
	fd = -2;
	is_first = true;
	//error
	if (fork() == 0)
	{
		while (current && (current->type == REDIR_OUT
				|| current->type == REDIR_OUT_APPEND))
		{
			if (!is_first && current->left->type == STRING)
				fd = open_file(fd, current->type, current->left->token->data);
			if (fd == -1)
				return ;
			if (current->right->type == STRING)
				fd = open_file(fd, current->type, current->right->token->data);
			if (fd == -1)
				return ;
			is_first = false;
			current = current->right;
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
		execute_command(node->left->token);
		exit(0);
	}
	int exit_status;
	wait(&exit_status);
}

void	execute_redir_in(t_node *node)
{
	t_node	*current;
	int		fd;
	bool	is_first;

	current = node;
	fd = -2;
	is_first = true;
	if (fork() == 0)
	{
		while (current && (current->type == REDIR_IN
				|| current->type == HEREDOC))
		{
			if (!is_first && current->left->type == STRING)
				fd = open_file(fd, get_type(current), current->left->token->data);
			if (fd == -1)
				return ;
			if (current->right->type == STRING)
				fd = open_file(fd, current->type, current->right->token->data);
			if (fd == -1)
				return ;
			is_first = false;
			current = current->right;
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
		execute_command(node->left->token);
		exit(0);
	}
	int exit_status;
	wait(&exit_status);
}
