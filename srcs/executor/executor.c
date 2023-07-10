/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:23:44 by hunam             #+#    #+#             */
/*   Updated: 2023/07/10 18:17:48 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include <unistd.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include "libft.h"

void	execute(t_node *ast)
{
	execute_command(ast->data);
}

void	execute_command(t_token *cmd)
{
	int			status_code;
	int			comm[2];
	const char	*path = get_command_path(cmd);

	if (g_shell.stop_child || !path)
		return ;
	if (pipe(comm) == -1)
		action_failed("pipe");
	g_shell.child_pid = fork();
	if (g_shell.child_pid == -1)
		action_failed("fork");
	if (g_shell.child_pid == 0)
		child_main(comm);
	else
	{
		encode(comm[1], (char *) path, cmd);
		g_shell.is_child_running = true;
		free((char *) path);
		waitpid(g_shell.child_pid, &status_code, 0);
		g_shell.is_child_running = false;
		if (WIFSIGNALED(status_code))
			g_shell.exit_status = signal_base + WEXITSTATUS(status_code);
	}
}

void	child_main(int comm[2])
{
	if (execve(decode_string(comm[0]), decode_array(comm[0]),
			decode_array(comm[0])) == -1)
		action_failed("execve");
}
