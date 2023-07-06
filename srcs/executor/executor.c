/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:23:44 by hunam             #+#    #+#             */
/*   Updated: 2023/07/05 17:24:25 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h> //TODO: rm
#include <signal.h> //TODO: rm

	// if (ast->type == PIPE)
	// {
	// 	execute(ast->left);
	// 	execute(ast->right);
	// }
	// if (ast->type == STRING)
	// 	printf("->%s\n", ast->data->data);
void	execute(t_node *ast)
{
	execute_command(ast->data);
}

void	execute_command(t_token *command)
{
	static bool	first_child = true;
	int			status_code;

	//TODO: here
	// if starts with /, check existence and permissions, and exec
	// else if it's a builtin, and exec
	// else check in the PATH dirs, check permissions, and exec
	// TODO: for PATH looking, is it the first match found or the last match?
	if (first_child)
		first_child = false;
	else
	{
		printf("child init in execute_command\n");
		g_shell.child_pid = fork();
		if (g_shell.child_pid == -1)
			action_failed("fork");
	}
	encode(g_shell.pipe_ends[1], command);
	waitpid(g_shell.child_pid, &status_code, WUNTRACED); //TODO: make sure WUNTRACED is necessary, see man waitpid for maybe interesting macros
	printf("status id: %d ->%d ->%d ->%d\n", status_code, WIFEXITED(status_code), WIFSIGNALED(status_code), WIFSTOPPED(status_code));
	// printf("signal: %d\n", WTERMSIG(status_code));
}

void	child_main(void)
{
	char	**argv;
	char	**envp;

	argv = decode(g_shell.pipe_ends[0]);
	envp = decode(g_shell.pipe_ends[0]);
	if (execve(argv[0], argv, envp) == -1)
		action_failed("execve");
	// TODO: free?
}
