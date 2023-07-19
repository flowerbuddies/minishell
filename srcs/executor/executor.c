/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:23:44 by hunam             #+#    #+#             */
/*   Updated: 2023/07/19 17:55:17 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include <unistd.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "builtin.h"

int	execute(t_node *ast, int io[2], bool redir_in_needed, bool redir_out_needed)
{
	if (!ast)
		return (g_shell.exit_status);
	if (ast->type == PIPE)
		return (execute_pipe(ast, io));
	if (ast->type == REDIR_OUT || ast->type == REDIR_OUT_APPEND)
		return (execute_redir_out(ast, io, redir_out_needed));
	if (ast->type == REDIR_IN || ast->type == HEREDOC)
		return (execute_redir_in(ast, io, redir_out_needed));
	return (execute_command(ast->token, io, redir_in_needed, redir_out_needed));
}

int	execute_command(
		t_token *cmd, int io[2], bool redir_in_needed, bool redir_out_needed)
{
	t_child	child;

	ft_memcpy(child.io, io, sizeof(int [2]));
	child.cmd = cmd;
	child.redir_out_needed = redir_out_needed;
	child.redir_in_needed = redir_in_needed;
	child.path = get_command_path(cmd->data);
	if (g_shell.stop_child || !child.path)
		return (g_shell.exit_status);
	g_shell.child_pid = fork();
	if (g_shell.child_pid == -1)
		action_failed("fork");
	if (g_shell.child_pid == 0)
		return (child_main(&child), 0);
	free(child.path);
	g_shell.is_child_running = true;
	waitpid(g_shell.child_pid, &child.status_code, 0);
	g_shell.is_child_running = false;
	if (redir_in_needed && close(io[0]) == -1)
		action_failed("close");
	if (redir_out_needed && close(io[1]) == -1)
		action_failed("close");
	if (WIFSIGNALED(child.status_code))
		return (signal_base + WTERMSIG(child.status_code));
	return (WEXITSTATUS(child.status_code));
}

int	execute_pipe(t_node *node, int io[2])
{
	if (pipe(io) == -1)
		action_failed("pipe");
	execute(node->left, io, false, true);
	if (dup2(io[0], STDIN_FILENO) == -1)
		action_failed("dup2");
	if (close(io[0]) == -1)
		action_failed("close");
	return (execute(node->right, io, false, false));
}

void	print_error(char *msg, char *file_name)
{
	printf("\e[31;1mError:\e[0m ");
	printf(msg, file_name);
	printf("\n");
}

void	child_main(t_child *child)
{
	if (child->redir_in_needed)
	{
		if (dup2(child->io[0], STDIN_FILENO) == -1)
			action_failed("dup2");
		if (close(child->io[0]) == -1)
			action_failed("close");
	}
	if (child->redir_out_needed)
	{
		if (dup2(child->io[1], STDOUT_FILENO) == -1)
			action_failed("dup2");
		if (close(child->io[1]) == -1)
			action_failed("close");
	}
	if (child->path[0] == '\0')
	{
		free(child->path);
		exit(execute_builtin(child->cmd));
	}
	if (execve(child->path, get_argv(child->cmd), get_envp(g_shell.vars)) == -1)
		action_failed("execve");
}
