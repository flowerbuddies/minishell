/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:23:44 by hunam             #+#    #+#             */
/*   Updated: 2023/07/17 17:06:23 by hunam            ###   ########.fr       */
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

int		execute(t_node *ast, int io[2], bool has_pipe, bool has_redir_in) // local scope io, recursive
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
		execute_command(ast->token, io, has_pipe, has_redir_in);
	return (0); // TODO: return code
}

int	execute_command(t_token *cmd, int io[2], bool has_pipe, bool has_redir_in)
{
	int		status_code;
	char	*path;

	if (is_builtin(cmd->data))
		return (execute_builtin(cmd)); // TODO: when to call?
	path = get_command_path(cmd->data);
	if (g_shell.stop_child || !path)
		return (g_shell.exit_status);
	g_shell.child_pid = fork();
	if (g_shell.child_pid == -1)
		action_failed("fork");
	if (g_shell.child_pid == 0)
		return (child_main(path, get_argv(cmd), get_envp(g_shell.vars), io, has_pipe, has_redir_in), 0);
	free(path);
	g_shell.is_child_running = true;
	waitpid(g_shell.child_pid, &status_code, 0);
	g_shell.is_child_running = false;
	if (has_pipe && (dup2(io[0], STDIN_FILENO) == -1 || close(io[0]) == -1 || close(io[1]) == -1))
		action_failed("dup2 or close");
	if (WIFSIGNALED(status_code))
		return (signal_base + WTERMSIG(status_code));
	return (WEXITSTATUS(status_code));
}

void	child_main(char *path, char **argv, char **envp, int io[2], bool has_pipe, bool has_redir_in)
{
	if (has_pipe && (dup2(io[1], STDOUT_FILENO) == -1 || close(io[0]) == -1 || close(io[1]) == -1))
		action_failed("dup2 or close");
	if (has_redir_in && (dup2(io[0], STDIN_FILENO) == -1 || close(io[0]) == -1))
		action_failed("dup2 or close");
	if (execve(path, argv, envp) == -1)
		action_failed("execve");
}
