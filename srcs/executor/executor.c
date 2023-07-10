/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:23:44 by hunam             #+#    #+#             */
/*   Updated: 2023/07/10 19:38:02 by hunam            ###   ########.fr       */
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

int	execute(t_node *ast)
{
	return (execute_command(ast->data));
}

int	execute_command(t_token *cmd)
{
	int		status_code;
	int		comm[2];
	char	*path;

	if (is_builtin(cmd->data))
		return (execute_builtin(cmd));
	path = get_command_path(cmd->data);
	if (g_shell.stop_child || !path)
		return (g_shell.exit_status);
	if (pipe(comm) == -1)
		action_failed("pipe");
	g_shell.child_pid = fork();
	if (g_shell.child_pid == -1)
		action_failed("fork");
	if (g_shell.child_pid == 0)
		return (child_main(comm), 0);
	encode(comm[1], (char *) path, cmd);
	g_shell.is_child_running = true;
	free((char *) path);
	waitpid(g_shell.child_pid, &status_code, 0);
	g_shell.is_child_running = false;
	if (WIFSIGNALED(status_code))
		return (signal_base + WTERMSIG(status_code));
	return (WEXITSTATUS(status_code));
}

void	child_main(int comm[2])
{
	if (execve(decode_string(comm[0]), decode_array(comm[0]),
			decode_array(comm[0])) == -1)
		action_failed("execve");
}
