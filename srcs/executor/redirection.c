/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 19:42:29 by marmulle          #+#    #+#             */
/*   Updated: 2023/07/17 17:40:22 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include "tokenizer.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "libft.h"

int	execute_pipe(t_node *node, int io[2])
{
	if (pipe(io) == -1)
		action_failed("pipe");
	execute(node->left, io, true, false);
	execute(node->right, io, false, false);
	return (0); // TODO: rm
}

static void	print_error(char *msg, char *file_name)
{
	printf("\e[31;1mError:\e[0m ");
	printf(msg, file_name);
	printf("\n");
}

static int	get_heredoc_fd(char *content)
{
	int	tmp_pipe[2];

	if (pipe(tmp_pipe) == -1)
		action_failed("pipe");
	write(tmp_pipe[1], content, ft_strlen(content));
	close(tmp_pipe[1]);
	return (tmp_pipe[0]);
}

static int	open_file(int fd2close, t_type type, char *file_name)
{
	int	flags;
	int	permissions;
	int	fd;

	close(fd2close);
	if (type == HEREDOC)
		return (get_heredoc_fd(file_name));
	flags = O_CREAT | O_WRONLY | O_TRUNC;
	if (type == REDIR_OUT_APPEND)
		flags = O_CREAT | O_WRONLY | O_APPEND;
	else if (type == REDIR_IN)
		flags = O_RDONLY;
	permissions = DEFAULT_FILE_PERMISSIONS;
	if (type == REDIR_IN)
		permissions = READ_ONLY_PERMISSIONS; //TODO: check that this is correct
	if (type == REDIR_IN && access(file_name, F_OK) == -1)
		return (print_error("file %s doesn't exist", file_name), -1);
	if (type == REDIR_IN && access(file_name, R_OK) == -1)
		return (print_error("can't read the file %s", file_name), -1);
	fd = open(file_name, flags, permissions);
	if (fd == -1)
		return (print_error("cannot open or create the file %s", file_name),
			-1);
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

int	execute_redir_out(t_node *node, int io[2])
{
	t_node	*current;
	int		fd;
	bool	is_first;

	current = node;
	fd = -2;
	is_first = true;
	while (current
		&& (current->type == REDIR_OUT || current->type == REDIR_OUT_APPEND))
	{
		if (!is_first && current->left->type == STRING)
			fd = open_file(fd, current->type, current->left->token->data);
		if (fd == -1)
			return (failure);
		if (current->right->type == STRING)
			fd = open_file(fd, current->type, current->right->token->data);
		if (fd == -1)
			return (failure);
		is_first = false;
		current = current->right;
	}
	return (execute_command(node->left->token, (int []){io[0], fd}, true, false)
		);
}

int	execute_redir_in(t_node *node, int io[2])
{
	t_node	*current;
	int		fd;
	bool	is_first;

	current = node;
	fd = -2;
	is_first = true;
	while (current
		&& (current->type == REDIR_IN || current->type == HEREDOC))
	{
		if (!is_first && current->left->type == STRING)
			fd = open_file(fd, get_type(current), current->left->token->data);
		if (fd == -1)
			return (failure);
		if (current->right->type == STRING)
			fd = open_file(fd, current->type, current->right->token->data);
		if (fd == -1)
			return (failure);
		is_first = false;
		current = current->right;
	}
	return (execute_command(node->left->token, (int []){fd, io[1]}, false, true)
		);
}
