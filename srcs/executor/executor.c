/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:23:44 by hunam             #+#    #+#             */
/*   Updated: 2023/07/03 18:45:04 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include <unistd.h>

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
	pid_t		pid;

	if (first_child)
		first_child = false;
	else
	{
		pid = fork();
		if (pid == -1)
			action_failed("fork");
	}
	encode(g_shell.pipe_ends[1], command);
}

void	child_main(void)
{
	char	**argv;
	char	**envp;

	argv = decode(g_shell.pipe_ends[0]);
	envp = decode(g_shell.pipe_ends[0]);
	execve(argv[0], argv, envp);
	// TODO: free?
}
