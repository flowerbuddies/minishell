/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 17:56:08 by hunam             #+#    #+#             */
/*   Updated: 2023/07/24 19:50:34 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include <sys/wait.h>
#include <stdio.h>

int	wait_pipe(t_node *ast)
{
	wait_commands(ast->left, false, true);
	return (wait_commands(ast->right, false, false));
}

int	wait_redir_in(t_node *ast, bool redir_out_needed)
{
	return (wait_commands(ast->left, true, redir_out_needed));
}

int	wait_redir_out(t_node *ast)
{
	return (wait_commands(ast->left, false, true));
}
int	wait_command(t_token *cmd, bool redir_in_needed, bool redir_out_needed)
{
	int	status;

	if (waitpid(cmd->pid, &status, WUNTRACED) == -1)
		action_failed("waitpid");
	printf("cmd->io[0]: %d\n", cmd->io[0]);
	printf("cmd->io[1]: %d\n", cmd->io[1]);
	if (redir_in_needed && close(cmd->io[0]) == -1)
		action_failed("close");
	if (redir_out_needed && close(cmd->io[1]) == -1)
		action_failed("close");
	if (WIFSIGNALED(status))
		return (signal_base + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

int	wait_commands(t_node *ast, bool redir_in_needed, bool redir_out_needed)
{
	int i = -1;

	int	status;

	while (++i <= g_shell.pids_idx)
	{
		printf("waiting for %d\n", g_shell.pids[i]);
		if (waitpid(g_shell.pids[i], &status, WUNTRACED) == -1)
			action_failed("waitpid");
		if (WIFSIGNALED(status))
			return (signal_base + WTERMSIG(status));
		return (WEXITSTATUS(status));
	}
	// if (!ast)
	// 	return (g_shell.exit_status);
	// if (ast->type == PIPE)
	// 	return (wait_pipe(ast));
	// if (ast->type == REDIR_OUT || ast->type == REDIR_OUT_APPEND)
	// 	return (wait_redir_out(ast));
	// if (ast->type == REDIR_IN || ast->type == HEREDOC)
	// 	return (wait_redir_in(ast, redir_out_needed));
	// return (wait_command(ast->token, redir_in_needed, redir_out_needed));
}

