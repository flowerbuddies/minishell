/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 19:42:29 by marmulle          #+#    #+#             */
/*   Updated: 2023/07/13 20:41:03 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include "tokenizer.h"
#include <unistd.h>
#include <fcntl.h>

#include "libft.h" // TODO: remove

int	execute_pipe(t_node *node, int io[2])
{
	if (pipe(io) == -1)
		action_failed("pipe");
	execute(node->left, io, true);
	execute(node->right, io, false);
	return (0); // TODO: rm
}

int	execute_redir_out(t_node *node, int io[2])
{
	t_node	*start;
	int		fd;

	start = node;
	node = node->right;
	while (node && (node->type == REDIR_OUT || node->type == REDIR_OUT_APPEND))
	{
		if (node->type == REDIR_OUT)
			fd = open(node->left->token->data,
					O_CREAT | O_WRONLY | O_TRUNC, FILE_PERMISSION);
		else if (node->type == REDIR_OUT_APPEND)
			fd = open(node->left->token->data,
					O_CREAT | O_WRONLY | O_APPEND, FILE_PERMISSION);
		if (fd == -1)
			action_failed("open");
		node = node->right;
	}
	if (node->parent->type == REDIR_OUT)
		fd = open(node->token->data,
						O_CREAT | O_WRONLY | O_TRUNC, FILE_PERMISSION);
	else
		fd = open(node->token->data,
						O_CREAT | O_WRONLY | O_APPEND, FILE_PERMISSION);
	if (fd == -1)
		action_failed("open"); // TODO: error function
	return (execute_command(start->left->token, (int []){io[0], fd}, true, false));
}

int	execute_redir_in(t_node *node, int io[2])
{
	t_node	*start;
	int		fd;

	start = node;
	node = node->right;
	while (node->type == REDIR_IN)
	{
		if (access(node->left->token->data, F_OK) == -1)
			action_failed("[FILENAME]: No such file or directory"); // TODO: error function that doesnt exit
		if (access(node->left->token->data, R_OK) == -1)
			action_failed("[FILENAME]: Permission denied"); // TODO: error function that doesnt exit
		node = node->right;
	}
	if (access(node->token->data, F_OK) == -1)
		action_failed("[FILENAME]: No such file or directory"); // TODO: error function that doesnt exit
	if (access(node->token->data, R_OK) == -1)
		action_failed("[FILENAME]: Permission denied"); // TODO: error function that doesnt exit
	fd = open(node->token->data, O_RDONLY, READONLY_PERMISSION);
	if (fd == -1)
		action_failed("open"); // TODO: error function
	return (execute_command(start->left->token, (int []){fd, io[1]}, false, true));
}
