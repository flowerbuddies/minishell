/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:23:44 by hunam             #+#    #+#             */
/*   Updated: 2023/07/14 18:57:03 by hunam            ###   ########.fr       */
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

int		execute(t_node *ast, int io[2], bool has_pipe) // local scope io, recursive
{
	if (!ast)
		return (g_shell.exit_status);
	if (ast->type == PIPE)
		execute_pipe(ast, io);
	else if (ast->type == REDIR_OUT || ast->type == REDIR_OUT_APPEND)
		execute_redir_out(ast, io);
	else if (ast->type == REDIR_IN)
		execute_redir_in(ast, io);
	if (ast->type == STRING)
		execute_command(ast->token, io, has_pipe, false);
	ft_printf("END OF EXECUTE\n");
	return (0); // TODO: return code
}

int	execute_command(t_token *cmd, int io[2], bool has_pipe, bool has_redir_in)
{
	int		status_code;
	char	*path;

	if (is_builtin(cmd->data))
		return (execute_builtin(cmd));
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
	ft_printf("PARENT>has_pipe is %d_____io[0] is %d\n", has_pipe, io[0]);
	if (has_pipe && (dup2(io[0], STDIN_FILENO) == -1 || close(io[0]) == -1 || close(io[1]) == -1))
		action_failed("dup2 or close");
	if (WIFSIGNALED(status_code))
		return (signal_base + WTERMSIG(status_code));
	ft_printf("END OF EXECUTE COMMAND\n");
	return (WEXITSTATUS(status_code));
}

void	child_main(char *path, char **argv, char **envp, int io[2], bool has_pipe, bool has_redir_in)
{
	ft_printf("has_pipe is %d_____fd is %d\n", has_pipe, io[1]);
	if (has_pipe && (dup2(io[1], STDOUT_FILENO) == -1 || close(io[0]) == -1 || close(io[1]) == -1))
		action_failed("dup2 or close");
	// ft_printf("has_redir_in is %d____fd is %d\n", has_redir_in, io[0]);
	// if (has_redir_in && (dup2(io[0], STDIN_FILENO) == -1 || close(io[0]) == -1 || close(io[1]) == -1))
	// 	action_failed("dup2 or close");
	if (execve(path, argv, envp) == -1)
		action_failed("execve");
}
