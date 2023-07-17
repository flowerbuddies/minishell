/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:23:44 by hunam             #+#    #+#             */
/*   Updated: 2023/07/17 19:30:08 by hunam            ###   ########.fr       */
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
		execute_pipe(ast, io);
	else if (ast->type == REDIR_OUT || ast->type == REDIR_OUT_APPEND)
		execute_redir_out(ast, io);
	else if (ast->type == REDIR_IN || ast->type == HEREDOC)
		execute_redir_in(ast, io);
	else if (ast->type == STRING)
		execute_command(ast->token, io, redir_out_needed, redir_in_needed);
	return (0); // TODO: return code
}

int	execute_command(
		t_token *cmd, int io[2], bool redir_in_needed, bool redir_out_needed)
{
	int		status_code;
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
	waitpid(g_shell.child_pid, &status_code, 0);
	g_shell.is_child_running = false;
	if (redir_out_needed && (dup2(io[0], STDIN_FILENO) == -1
			|| close(io[0]) == -1 || close(io[1]) == -1))
		action_failed("dup2 or close1");
	if (WIFSIGNALED(status_code))
		return (signal_base + WTERMSIG(status_code));
	return (WEXITSTATUS(status_code));
}

void	child_main(t_child *child)
{
	if (child->redir_out_needed && (dup2(child->io[1], STDOUT_FILENO) == -1
			|| close(child->io[0]) == -1 || close(child->io[1]) == -1))
		action_failed("dup2 or close2");
	if (child->redir_in_needed && (dup2(child->io[0], STDIN_FILENO) == -1
			|| close(child->io[0]) == -1))
		action_failed("dup2 or close3");
	if (child->path[0] == '\0')
	{
		free(child->path);
		exit(execute_builtin(child->cmd));
	}
	if (execve(child->path, get_argv(child->cmd), get_envp(g_shell.vars)) == -1)
		action_failed("execve");
}
